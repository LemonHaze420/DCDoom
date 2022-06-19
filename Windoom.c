// Copyright © 1998, Bruce A. Lewis
// This code may not be re-used in a commercial product
// of any kind without express written consent from
// the author, Bruce A. Lewis.
//
/////////////////////////////////////////////////////////////////////////////////////
// Windows Includes...
/////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <time.h>
#include <maplusag.h>
#include <mapledev.h>
#include <ceddcdrm.h>
#include <segagdrm.h>
#include <perstore.h>
#include <platutil.h>
#include <vib.h>
#include <lcd.h>
#include <dbt.h>

/////////////////////////////////////////////////////////////////////////////////////
// DirectX Includes...
/////////////////////////////////////////////////////////////////////////////////////
#include <direct.h>
#include <ddraw.h>
#include <dinput.h>
//#include <dsound.h>
#include <dplay.h>
#include <d3d.h>

/////////////////////////////////////////////////////////////////////////////////////
// Application Includes...
/////////////////////////////////////////////////////////////////////////////////////
#include "resource.h"  // Required for Win32 Resources

/////////////////////////////////////////////////////////////////////////////////////
// "WinDoom" Includes...
/////////////////////////////////////////////////////////////////////////////////////
#include "doomdef.h"
#include "doomstat.h"
#include "d_event.h"
#include "d_main.h"
#include "m_argv.h"
#include "g_game.h"
#include "i_system.h"
//#include "m_music.h"
//#include "i_cd.h"
#include "i_midi.h"
#include "dxerr.h"
//#include "sounds.h"

int nDrop = 0;
DWORD g_dwTick = 0, g_dwOldTick = 0;


HANDLE	  g_hRemoveDevice = NULL;
HANDLE    g_hNewDevice = NULL;
HANDLE	  g_hGDROM = NULL;


HWND      hMainWnd;

BOOL g_bVGA = FALSE;

//#include "dconsole.h"
/////////////////////////////////////////////////////////////////////////////////////
// DirectX Defines and Data
/////////////////////////////////////////////////////////////////////////////////////

#undef RELEASE
#ifdef __cplusplus
#define RELEASE(x) if (x != NULL) {x->Release(); x = NULL;}
#else
#define RELEASE(x) if (x != NULL) {x->lpVtbl->Release(x); x = NULL;}
#endif



void DrawLoadingMessage();

/////////////////////////////////////////////////////////////////////////////////////
// Direct Input
/////////////////////////////////////////////////////////////////////////////////////

void HandleKeyStrokes(void);
void KeyboardHandler(void);
BOOL InitDirectInput(void);
void ShutdownDirectInput(void);

LPDIRECTINPUT        lpDirectInput = 0;
LPDIRECTINPUTDEVICE  lpMouse       = 0;
LPDIRECTINPUTDEVICE2 lpJoystick    = 0;
LPDIRECTINPUTDEVICE  lpKeyboard    = 0;

BOOL          bDILive = FALSE;
char          szMouseBuf[1024];
unsigned char diKeyState[256];
unsigned char diOldKeyState[256];

extern int    always_run;
extern int    mvert;
extern int    keylink;

extern boolean         gamekeydown[256]; 



/////////////////////////////////////////////////////////////////////////////////////
// Direct Draw
/////////////////////////////////////////////////////////////////////////////////////

void RenderScene(void);
void InitGlobals(void);
BOOL SetupDirectDraw(HWND);
void ShutdownDirectDraw(void);

int		dxStCount;


LPDIRECTDRAW         lpDD;          // DirectDraw Interface
LPDIRECTDRAW4        lpDD2;         // DirectDraw Interface
LPDIRECTDRAWSURFACE4 lpDDSPrimary, lpDDSBack;  // DirectDraw Surface
LPDIRECTDRAWSURFACE4 lpDDSRender, lpDDSHWRender[2];

LPDIRECTDRAWPALETTE  lpPalette = NULL; // Palette
PALETTEENTRY         rPal[768];        // Temp palette used later on

// this structure holds a RGB triple in three unsigned bytes
typedef struct RGB_color_typ
{
    unsigned char red;      // red   component of color 0-63
    unsigned char green;    // green component of color 0-63
    unsigned char blue;     // blue  component of color 0-63
}xRGB_color, *xRGB_color_ptr;

// this structure holds an entire color palette
typedef struct xRGB_palette_typ
{
    int start_reg;          // index of the starting register that is save
    int end_reg;            // index of the ending registe that is saved
    xRGB_color colors[256];  // the storage area for the palette
}xRGB_palette, *xRGB_palette_ptr;

xRGB_palette xpal;


BOOL CheckSurfaces(void);







/////////////////////////////////////////////////////////////////////////////////////
// Application Defines and Data
/////////////////////////////////////////////////////////////////////////////////////

#define KS_KEYUP        0
#define KS_KEYDOWN    128

/////////////////////////////////////////////////////////////////////////////////////
// Game states -- these are the modes in which the outer game loop can be
/////////////////////////////////////////////////////////////////////////////////////
#define GAME_START  0
#define GAME_SPLASH 1
#define GAME_MENU   2
#define GAME_PLAY   3
#define GAME_EXIT   4
#define GAME_QUIT   5
#define GAME_LIMBO  6
#define GAME_PAUSE  7

int     GameMode = GAME_START;

extern byte *screens[5];

extern int usemouse;
extern int usejoystick;


char      szMsgText[256];

DWORD     dwCurrWidth, dwCurrHeight, dwCurrBPP;


BOOL        bQuit = FALSE;

time_t clock_in, clock_out;	//work seconds for FPS 11.4.98 dlw
long framecount;			//count frames for FPS


void  GetWindowsVersion(void);
void  WriteDebug(char *);
BYTE* GetDataResource(TCHAR *psz, DWORD *pcbData);

int   WinDoomAC;
char *WinDoomAV[256];

char *YesNo[] = { "No", "Yes" };

void  ParseCommand(PTSTR szCmdLine);
void AddCommandLineOption( const char* szCmdLine );

void  GameLoop(void);

void  D_DoomMain(void);
void *W_CacheLumpName(char *, int);
void  I_SetPalette(byte *);
void  MY_DoomSetup(void);
void  MY_DoomLoop(void);
void  WinDoomExit(void);
void  HandleKeyboard(void);

extern int key_right;
extern int key_left;
extern int key_up;
extern int key_down; 
extern int key_strafeleft;
extern int key_straferight; 
extern int key_fire;
extern int key_use;
extern int key_strafe;
extern int key_speed;
extern int key_nextweapon;
extern int key_prevweapon;


extern int joybup;
extern int joybdown;
extern int joybleft;
extern int joybright;
extern int joybfire; 
extern int joybstrafe; 
extern int joybuse; 
extern int joybspeed;
extern int joybstrafeleft;
extern int joybstraferight;
extern int joybnextweapon;
extern int joybprevweapon;
extern int joybmenu;
extern int joybmenuselect;
extern int joybmenucancel;

extern int mousebnextweapon;
extern int mousebprevweapon;



extern void DoEvilHack(short* pDst, int pitch);

void EvilHack()
{
    DDSURFACEDESC2 ddsd;
    ddsd.dwSize = sizeof(ddsd);
    
    if( lpDDSRender->lpVtbl->Lock(lpDDSRender, NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) == DD_OK )
    {
        DoEvilHack( ddsd.lpSurface, (unsigned short)ddsd.lPitch );
    }
    
    lpDDSRender->lpVtbl->Unlock(lpDDSRender, NULL);
}



BOOL g_bDoorOpened = FALSE;



BOOL CheckForYButtonPress()
{
    DIJOYSTATE diJoyState;
    
    if( lpJoystick )
    {
        lpJoystick->lpVtbl->Poll(lpJoystick);
        if ( FAILED(lpJoystick->lpVtbl->GetDeviceState(lpJoystick, sizeof(DIJOYSTATE), &diJoyState) ) )
        {
            lpJoystick->lpVtbl->Acquire(lpJoystick);
            lpJoystick->lpVtbl->Poll(lpJoystick);
            if( FAILED( lpJoystick->lpVtbl->GetDeviceState(lpJoystick, sizeof(DIJOYSTATE), &diJoyState) ) ) return FALSE;
        }

        return (diJoyState.rgbButtons[7]);
    }
    else
        return FALSE;
}



int DreamcastInit()
{
    g_hGDROM = CreateFile(TEXT("\\Device\\CDROM0"), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL );
    if (g_hGDROM == INVALID_HANDLE_VALUE) return 0;
    
    g_hNewDevice = CreateEvent(NULL, FALSE, FALSE, TEXT("MAPLE_NEW_DEVICE"));
    g_hRemoveDevice = CreateEvent(NULL, FALSE, FALSE, TEXT("MAPLE_DEVICE_REMOVED"));

    return 1;
    
    
}



BOOL CALLBACK Controller_Enum( LPCDIDEVICEINSTANCE pdidi, void* pV )
{
    memcpy( pV, &pdidi->guidInstance, sizeof(pdidi->guidInstance) );
    return FALSE;
}

void Flash_FindFirstWadFile( char* pszFilename );

DWORD g_iControllerPort = 0xFF;
GUID g_flashguid;
GUID g_vibguid;
GUID g_lcdguid;

int g_nMapleDevNum = 0;

BOOL CALLBACK MapleEnumProc(LPCMAPLEDEVICEINSTANCE pmdi, LPVOID pvContext)
{
    if( pmdi->dwPort == g_iControllerPort )
    {
        g_nMapleDevNum = pmdi->dwDevNum;
        memcpy( pvContext, &pmdi->guidDevice, sizeof(GUID) );
        return FALSE;
    }
    
    return(TRUE);
}

PVIB g_pVibrationPack = NULL;
UINT g_nNumVibSources;
UINT g_nNumSimultaneousSources;
UINT g_CurSource;
VIB_INFO g_pVibInfoArray[VIB_MAX_SOURCES];
HANDLE g_hVibEvent;

BYTE g_dwVibDirection;
BYTE g_dwVibType;
BYTE g_nVibRange;


void Vibrate_Init()
{
    IUnknown *pIUnknown;
    BYTE *pAutostops = NULL;
    BYTE *pSourceIds = NULL;
    PVIB_WAVEFORM_SETTINGS pWaveform = NULL;
    UINT value;
    GUID nullguid;
    UINT index;

    memset( &nullguid, 0, sizeof(GUID) );
    if( memcmp( &g_vibguid, &nullguid, sizeof(GUID) ) == 0 ) return;

    if( FAILED( MapleCreateDevice(&g_vibguid, &pIUnknown) ) ) return;

    pIUnknown->lpVtbl->QueryInterface(pIUnknown, &IID_IVib, (void**)&g_pVibrationPack);
    pIUnknown->lpVtbl->Release(pIUnknown);

    if( g_pVibrationPack == NULL ) return;


    g_nNumVibSources = VIB_MAX_SOURCES;
    if( FAILED( g_pVibrationPack->lpVtbl->GetVibInfo(g_pVibrationPack, &g_nNumVibSources, &g_nNumSimultaneousSources, g_pVibInfoArray ) ) ) return;

    pSourceIds = malloc(g_nNumVibSources);
    pAutostops = malloc(g_nNumVibSources);
    value = g_nNumVibSources;
    
    for (index = 0; index < g_nNumVibSources; index++)
    {
        pSourceIds[index] = index + 1;
        pAutostops[index] = 10 + 10 * index;
    }
    
    g_pVibrationPack->lpVtbl->SetVibAutostopTimes(g_pVibrationPack,value, pSourceIds, pAutostops, NULL);
    
    g_pVibrationPack->lpVtbl->GetVibAutostopTimes(g_pVibrationPack,&value, pAutostops);
      
    // None of the initial vibration devices support arbitrary waveforms, so
    // this sample doesn't do anything with them. 
                  
    // Note, this event must be manual reset.  Start it signaled.
    g_hVibEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

    if (pSourceIds != NULL) free( pSourceIds );
    if (pAutostops != NULL) free( pAutostops );

    g_dwVibDirection = (g_pVibInfoArray[0].bCaps & VIBCAPS_DIRECTIONAL) ? VIB_DIRECTION_REVERSE : VIB_DIRECTION_FORWARD;
    g_dwVibType = (g_pVibInfoArray[0].bCaps & VIBCAPS_VARIABLEINTENSITY) ? /*VIB_TYPE_DIVERGENT*/VIB_TYPE_CONVERGENT : VIB_TYPE_CONSTANT;
    g_nVibRange = (g_pVibInfoArray[0].maxFrequency-g_pVibInfoArray[0].minFrequency);

    return;
}


void Vibrate_Done()
{
    RELEASE(g_pVibrationPack);
    CloseHandle(g_hVibEvent);
    g_hVibEvent = NULL;
}


void VibrateController(BYTE dwSource, BOOL fContinuousVib, BYTE dwVibType, BYTE dwInitialPower, 
                  BYTE dwDirection, BYTE dwFrequency, BYTE dwWavesPerStep)
{
    DWORD        dwWaitReturn;
    VIB_SETTINGS vibsettings;
    HRESULT hResult;

    if( g_pVibrationPack == NULL ) return;

    // There are currently no vibration devices which support multiple
    // simultaneous sources, so this sample only deals with one.  If you
    // need to support multiple simultaneous sources, then simply modify the
    // VibSettings struct to be an array, and pass that array to Vibrate().
    vibsettings.vibType        = dwVibType;
    vibsettings.sourceId       = dwSource;
    vibsettings.direction      = dwDirection;
    vibsettings.frequency      = dwFrequency;
    vibsettings.initialPower   = dwInitialPower;
    vibsettings.wavesPerStep   = dwWavesPerStep;
    vibsettings.bContinuousVib = fContinuousVib;

    // We have a manual reset event that was created in the signaled state.
    // So, the first time through here, the Wait will return immediately.
    // We pass that event to Vibrate.  Because the parameter is not NULL,
    // Vibrate will return quickly with VIBERR_PENDING.  We then go off 
    // and do other things.  When the command to the device finishes, 
    // the Api will signal our event.  So, the next time we get here 
    // that Wait will return immediately again.  If, however, we tried to
    // call the api again very quickly (before it finished the last call)
    // we'd wait here until the previous call was finished.  The calls
    // shouldn't take more than 2 frames to complete, and it's unlikely
    // that we'll tell the device to vibrate twice in that time frame (a
    // human won't be able to feel changes that quick), so this is okay.
 
    // First make sure the previous send is finished
    dwWaitReturn = WaitForSingleObject(g_hVibEvent, 32);
    ResetEvent(g_hVibEvent);

    // Start the vibration
    hResult = g_pVibrationPack->lpVtbl->Vibrate(g_pVibrationPack, 1, &vibsettings, g_hVibEvent);
    if( hResult != VIB_OK && hResult != VIBERR_PENDING )
    {
        SetEvent(g_hVibEvent);
    }
}

void Vibrate_Small()
{
    VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, VIB_DIRECTION_FORWARD, g_pVibInfoArray[0].minFrequency + ((g_pVibInfoArray[0].maxFrequency-g_pVibInfoArray[0].minFrequency)*0.2f), 0);
}

void Vibrate_Medium()
{
    VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, VIB_DIRECTION_FORWARD, g_pVibInfoArray[0].minFrequency, 1);
}

void Vibrate_Large()
{
    VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, VIB_DIRECTION_FORWARD, g_pVibInfoArray[0].minFrequency, 4);
}

void Vibrate_VeryLarge()
{
    VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, VIB_DIRECTION_FORWARD, g_pVibInfoArray[0].minFrequency, 8);
}

void Vibrate_ChainsawIdle()
{
    static int n = 0;
    if( ++n == 2 ) n = 0;
    if( n == 0 )
        VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, g_dwVibDirection, g_pVibInfoArray[0].minFrequency + g_nVibRange*0.4f, 6);
}

void Vibrate_Kickback( int weapon )
{
    switch( weapon )
    {
        case wp_fist:           VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, g_dwVibDirection, g_pVibInfoArray[0].minFrequency + g_nVibRange*0.2f, 1); break;
        case wp_pistol:         VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, g_dwVibDirection, g_pVibInfoArray[0].minFrequency + g_nVibRange*0.2f, 1); break;
        case wp_shotgun:        VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, g_dwVibDirection, g_pVibInfoArray[0].minFrequency + g_nVibRange*0.1f, 2); break;
        case wp_supershotgun:   VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, g_dwVibDirection, g_pVibInfoArray[0].minFrequency + g_nVibRange*0.0f, 1); break;
        case wp_chainsaw:       VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, g_dwVibDirection, g_pVibInfoArray[0].minFrequency + g_nVibRange*0.0f, 1); break;
        case wp_chaingun:       VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, g_dwVibDirection, g_pVibInfoArray[0].minFrequency + g_nVibRange*0.2f, 2); break;
        case wp_missile:        VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, g_dwVibDirection, g_pVibInfoArray[0].minFrequency + g_nVibRange*0.0f, 3); break;
        case wp_plasma:         VibrateController(1, FALSE, VIB_TYPE_CONSTANT, VIB_POWER_MAX, g_dwVibDirection, g_pVibInfoArray[0].minFrequency + g_nVibRange*0.3f, 3); break;
        case wp_bfg:            VibrateController(1, FALSE, g_dwVibType, VIB_POWER_MAX, g_dwVibDirection, g_pVibInfoArray[0].minFrequency, 1); break;
    }

}

PLCD g_pLCD = NULL;
HANDLE g_hLCDEvent = NULL;
int g_nLCDDevNum = 0;
PBYTE g_pbyLCDBuffer = NULL;
DWORD g_dwBufId = 0;
BOOL g_bLCDInverted = FALSE;
const BYTE   g_byPtForLCD1        = 0;
const BYTE   g_byPhaseForStdLCD   = 0;
const USHORT g_usBlockForStdLCD   = 0;
const UINT   g_uiStdLCDBufferSize = 192;
const UINT   g_uiStdLCDXPixels    = 48;
const UINT   g_uiStdLCDYPixels    = 32;
const UINT   g_uiBitsPerByte      = 8;
const UINT   g_uiStdBytesPerRow   = 48 / 8;

void LCD_Init()
{
    int nDirection = 0;
    GUID nullguid;
    IUnknown *pIUnknown;
    DIPROPDWORD dipdw;

    memset( &nullguid, 0, sizeof(GUID) );
    if( memcmp( &nullguid, &g_lcdguid, sizeof(GUID) ) == 0 ) return;

    if( FAILED( MapleCreateDevice(&g_lcdguid, &pIUnknown) ) ) return;

    pIUnknown->lpVtbl->QueryInterface(pIUnknown, &IID_ILcd, (void**)&g_pLCD);
    pIUnknown->lpVtbl->Release(pIUnknown);
    if(g_pLCD == NULL ) return;

    if( !g_pLCD->lpVtbl->IsStandardLcd(g_pLCD) )
    {
        RELEASE(g_pLCD);
        return;
    }

    if( FAILED( g_pLCD->lpVtbl->GetLcdBuffer( g_pLCD, &g_pbyLCDBuffer, &g_dwBufId, g_uiStdLCDBufferSize ) ) )
    {
        RELEASE(g_pLCD);
        return;
    }

    memset(g_pbyLCDBuffer, 0, g_uiStdLCDBufferSize);

    // Note, this event must be manually reset.
    g_hLCDEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if( SUCCEEDED(lpJoystick->lpVtbl->GetProperty(lpJoystick, DIPROP_EXPDIRECTION, &dipdw.diph)))
        nDirection = dipdw.dwData;

    g_bLCDInverted = DIPROP_EXTRACT_EXPDIRECTION( nDirection, g_nLCDDevNum );
}

void LCD_Done()
{
    if (g_dwBufId != 0)
    {
        g_pbyLCDBuffer = NULL;
        g_pLCD->lpVtbl->FreeLcdBuffer(g_pLCD, g_dwBufId);
    }

    RELEASE( g_pLCD );
    CloseHandle( g_hLCDEvent );
    g_hLCDEvent = NULL;
}

void LCD_SetBit(int nX, int nY, BOOL fSet)
{
    int  i;
    BYTE byData;
    BYTE byBit;
    BYTE byMask = 0;

    // The LCD is plugged in upside down, so we need to reverse our coordinates
    if (g_bLCDInverted)
    {
        nX = (g_uiStdLCDXPixels - 1) - nX;
        nY = (g_uiStdLCDYPixels - 1) - nY;
    }

    i = nY * g_uiStdBytesPerRow + nX / g_uiBitsPerByte;
    byBit = (g_uiBitsPerByte - 1) - nX % g_uiBitsPerByte;

    byMask = 1 << byBit;

    byData = g_pbyLCDBuffer[i];

    if (fSet)
        byData |= byMask;
    else
        byData &= (~byMask);

    g_pbyLCDBuffer[i] = byData;
}




void LCD_SetPicture()
{
    HRESULT hResult;
    int x = g_uiStdLCDXPixels, y = g_uiStdLCDYPixels;
    BYTE *pb;
    DWORD cb;
    BYTE* p;

    if( g_pLCD == NULL ) return;

    pb = GetDataResource(TEXT("LCD_PICTURE"), &cb);
    if( pb == NULL ) return;
    p = pb;

    while( y-- ) { x = g_uiStdLCDXPixels; while( x-- ) LCD_SetBit( x, y, !(*p++) ); }
    LocalFree( pb );

    hResult = g_pLCD->lpVtbl->SendLcdBuffer(g_pLCD, g_dwBufId, g_byPtForLCD1, g_byPhaseForStdLCD, g_usBlockForStdLCD, g_hLCDEvent);
    if( hResult != E_PENDING ) SetEvent(g_hLCDEvent);
}







int g_nControllers = 0;

void EnumerateAllControllers()
{
    LPDIRECTINPUTDEVICE lpJoy;
    DIPROPRANGE         diprg; 
    DIPROPDWORD         dipdw;
    GUID guid;
    HRESULT hResult;
    
    g_iControllerPort = 0xFF;   
    g_nControllers = 0;
    
    memset( &g_flashguid, 0, sizeof(GUID) );
    memset( &g_vibguid, 0, sizeof(GUID) );
    
    lpDirectInput->lpVtbl->EnumDevices( lpDirectInput, DIDEVTYPE_MOUSE, Controller_Enum, &guid, 0 );
    hResult = lpDirectInput->lpVtbl->CreateDevice(lpDirectInput, &guid, &lpMouse, NULL );
    if( hResult == DI_OK ) g_nControllers++;
    
    lpDirectInput->lpVtbl->EnumDevices( lpDirectInput, DIDEVTYPE_JOYSTICK, Controller_Enum, &guid, 0 );
    hResult = lpDirectInput->lpVtbl->CreateDevice(lpDirectInput, &guid, &lpJoy, NULL );
    if (hResult == DI_OK)
    {
        hResult = lpJoy->lpVtbl->QueryInterface(lpJoy,&IID_IDirectInputDevice2,(LPVOID *)&lpJoystick); 
        if( hResult == DI_OK ) g_nControllers++;
        RELEASE(lpJoy);
    }
    
    lpDirectInput->lpVtbl->EnumDevices( lpDirectInput, DIDEVTYPE_KEYBOARD, Controller_Enum, &guid, 0 );
    hResult = lpDirectInput->lpVtbl->CreateDevice(lpDirectInput, &guid, &lpKeyboard, NULL );
    if( hResult == DI_OK ) g_nControllers++;
    
    if( lpKeyboard )
    {
        lpKeyboard->lpVtbl->SetDataFormat(lpKeyboard, &c_dfDIKeyboard);
        lpKeyboard->lpVtbl->SetCooperativeLevel(lpKeyboard, hMainWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
        
        lpKeyboard->lpVtbl->Acquire(lpKeyboard);
    }
    
    if( lpMouse )  
    {
        lpMouse->lpVtbl->SetDataFormat(lpMouse, &c_dfDIMouse);
        lpMouse->lpVtbl->SetCooperativeLevel(lpMouse, hMainWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
        lpMouse->lpVtbl->Acquire(lpMouse);
    }
    
    if( lpJoystick )
    {
        lpJoystick->lpVtbl->SetDataFormat(lpJoystick, &c_dfDIJoystick);
        lpJoystick->lpVtbl->SetCooperativeLevel(lpJoystick, hMainWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
        
        diprg.diph.dwSize       = sizeof(diprg); 
        diprg.diph.dwHeaderSize = sizeof(diprg.diph); 
        diprg.diph.dwObj        = DIJOFS_X; 
        diprg.diph.dwHow        = DIPH_BYOFFSET; 
        diprg.lMin              = -1000; 
        diprg.lMax              = +1000; 
        lpJoystick->lpVtbl->SetProperty(lpJoystick, DIPROP_RANGE, &diprg.diph);
        diprg.diph.dwObj        = DIJOFS_Y; 
        lpJoystick->lpVtbl->SetProperty(lpJoystick, DIPROP_RANGE, &diprg.diph);
        
        dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
        dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
        dipdw.diph.dwHow        = DIPH_BYOFFSET;
        dipdw.dwData            = 1500;
        dipdw.diph.dwObj        = DIJOFS_X;
        lpJoystick->lpVtbl->SetProperty(lpJoystick, DIPROP_DEADZONE, &dipdw.diph);
        dipdw.dwData            = 1500;
        dipdw.diph.dwObj         = DIJOFS_Y;
        lpJoystick->lpVtbl->SetProperty(lpJoystick, DIPROP_DEADZONE, &dipdw.diph);
        
        lpJoystick->lpVtbl->Acquire(lpJoystick);
    }
    
    
    
    // Get the port number of the device
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj = 0;
    dipdw.diph.dwHow = DIPH_DEVICE;
    if( lpJoystick && SUCCEEDED( lpJoystick->lpVtbl->GetProperty(lpJoystick,DIPROP_PORTNUMBER, &dipdw.diph) ) )
    {
        g_iControllerPort = dipdw.dwData;
        MapleEnumerateDevices(MDT_STORAGE, MapleEnumProc, &g_flashguid, 0);
        MapleEnumerateDevices(MDT_VIBRATION, MapleEnumProc, &g_vibguid, 0);
        MapleEnumerateDevices(MDT_LCD, MapleEnumProc, &g_lcdguid, 0);
        g_nLCDDevNum = g_nMapleDevNum;

        LCD_Init();
        LCD_SetPicture();
    }
    
    WaitForSingleObject(g_hNewDevice, 0);
    WaitForSingleObject(g_hRemoveDevice, 0);

    Vibrate_Init();
}

void ReleaseAllControllers()
{
    LCD_Done();
    Vibrate_Done();
    if(lpJoystick) { lpJoystick->lpVtbl->Release(lpJoystick); lpJoystick = NULL; }
    if(lpMouse)    { lpMouse->lpVtbl->Release(lpMouse);       lpMouse = NULL; }
    if(lpKeyboard) { lpKeyboard->lpVtbl->Release(lpKeyboard); lpKeyboard = NULL; }
}





void DreamcastShutdown()
{
  
    // Release Events Handles
    if (g_hNewDevice != NULL)
    {
        CloseHandle(g_hNewDevice);
        g_hNewDevice = NULL;
    }
    
    if (g_hRemoveDevice != NULL)
    {
        CloseHandle(g_hRemoveDevice);
        g_hRemoveDevice = NULL;
    }
    
    if (g_hGDROM != NULL)
    {
        CloseHandle(g_hGDROM);
        g_hGDROM = NULL;
    }
}


void CheckNewDevices()
{
    // If WaitForSingleObject returns with WAIT_TIMEOUT, no devices were removed. 
    // Otherwise, some devices may have been removed.
    if (WaitForSingleObject( g_hRemoveDevice, 0) != WAIT_TIMEOUT)
    {
        ReleaseAllControllers();
        EnumerateAllControllers();
    }
    
    // If WaitForSingleObject returns with WAIT_TIMEOUT, there are no new devices. 
    // Otherwise, there could be new devices.
    if (WaitForSingleObject( g_hNewDevice, 0) != WAIT_TIMEOUT)
    {
        ReleaseAllControllers();
        EnumerateAllControllers();
    }
}



/////////////////////////////////////////////////////////////////////////////////////
// Windows Defines and Data
/////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR      szAppName[] = TEXT("windoom");
//char      szCfgName[] = "WinDoom.cfg"; unused
HINSTANCE hInst;
HACCEL    ghAccel;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCmdLine, int nCmdShow)
{
    MSG         msg;
    WNDCLASS  wndclass;
    HWND        hwnd;
    int         i;
    int         p;
    char szFileFromVM[16];

    
    hInst = hInstance;
    
    //    MidiInit();
    //    MidiPlay("\\CD-ROM\\MUSIC\\D_inter.mid",1);
    
    
    wndclass.style         = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc   = WndProc;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = hInstance;
    wndclass.hIcon         = NULL;
    wndclass.hCursor       = NULL;
    wndclass.hbrBackground = NULL;
    wndclass.lpszMenuName  = NULL;
    wndclass.lpszClassName = szAppName;
    
    RegisterClass(&wndclass);
    
    hwnd = CreateWindow(szAppName,NULL, WS_POPUP|WS_VISIBLE,0,0, 640, 480, NULL,NULL,hInstance, NULL);
    
    
    
    
    
    
    hMainWnd = hwnd;
    //SetupDirectSound();
    
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    
    // This is used to determine what OS we're on (Windows9X or Windows NT)
    GetWindowsVersion();
    
    ParseCommand(szCmdLine);
    
    p = M_CheckParm("-width");
    if (p && p < myargc-1)
        SCREENWIDTH = atoi(myargv[p+1]);
    else
        SCREENWIDTH = 320;
    
    p = M_CheckParm("-height");
    if (p && p < myargc-1)
        SCREENHEIGHT = atoi(myargv[p+1]);
    else
        SCREENHEIGHT = 240;
    
    //11.4.98 dlw optimize
    DOUBLESTUFF=0;
    if(SCREENWIDTH>=640 && SCREENHEIGHT>=400)
        DOUBLESTUFF=1;
    
    //11.5.98 dlw optimize
    SCREENMULT=SCREENWIDTH*SCREENHEIGHT;
    
    //11.16.98 dlw testing
    //i=midiOutGetNumDevs();
    //sprintf(szMsgText, "Number of Midi Devices=%d\n", i);
    //WriteDebug(szMsgText);
    
    DreamcastInit();
    
    // This sets the video mode to video mode described in the default video mode
    InitGlobals();
    if (!SetupDirectDraw(hwnd))
    {
        //MidiDone();
        DreamcastShutdown();
        //ShutdownDirectSound();
        exit(0);
    }
    
    DrawLoadingMessage();

    //MoveWindow(hwnd, 0,0, Mode[CurrMode].w, Mode[CurrMode].h, TRUE);
    
    bDILive = InitDirectInput();

    Flash_FindFirstWadFile(szFileFromVM);
    if( *szFileFromVM )
    {
        char szExtraFilename[16];
        szExtraFilename[0] = '$';
        strcpy( szExtraFilename + 1, szFileFromVM );
        AddCommandLineOption( "-file" );
        AddCommandLineOption( szExtraFilename );
    }

    AddCommandLineOption( "-game" );
    if( CheckForYButtonPress() )
    {
        AddCommandLineOption( "doom2" );
    }
    else
    {
        AddCommandLineOption( "doom" );
    }


/* copy file from \\PC
    {
        FILE* file = fopen( "\\PC\\inca.wad", "rb" );
        int nSize;
        void* pBuf;
        fseek( file, 0, SEEK_END );
        nSize = ftell( file );
        fseek( file, 0, SEEK_SET );
        pBuf = malloc( nSize );
        fread( pBuf, 1, nSize, file );
        fclose( file );
        
        Flash_WriteFile( "inca.wad", pBuf, nSize, "Doom wad" );
        free(pBuf);
    }*/
    


    //for(k = 0; k < 256; k++) si_Kbd[k] = KS_KEYUP;
    
    //PlayMidiFile(szMidiFile);
    
    bQuit = FALSE;
    
    //11.4.98 dlw start the FPS clock here
    //time(&clock_in);
    clock_in = GetTickCount();
    
    //    sprintf(szMsgText, "windoom Version %2d.%02d", CONSVERS/100, CONSVERS%100);
    //	WriteDebug(szMsgText);
    //	WriteDebug("\n");		// leaves sz working for dxstarttext
    
    //HACK!
    //MidiInit();
    //MidiPlay("\\CD-ROM\\MUSIC\\D_e3m8.mid",1);
    
    
    //testing foolheartedly 10.19.98 to blast some text on screen
    //for(k=0; k<400; k++)  //test loop see if we can see this
    //{
    //	dxStartText(szMsgText);
    //}
    
    D_DoomMain();
    MY_DoomSetup();
    if(gamemode != indetermined) //11.9.98 bug catcher
        GameMode = GAME_PLAY;
    
    //these are hardwired and cannot be changed. read: hack
    joybmenu = 2;               //start
    joybmenuselect = 1;         //A
    joybmenucancel = 0;         //B
    
    while(!bQuit)
    {
        //while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
            {
                bQuit = TRUE;
                break;
            }
            //else if(msg.message == WM_CLOSE)
            //{
            //	bQuit = TRUE;
            //	break;
            //}
            
            //11.8.98 Finally debugging this cuz theres no
            // accelerator to begin with
            //if(!TranslateAccelerator(msg.hwnd, hAccel, &msg))
            //{
            //sprintf(szMsgText, "Translate failed: Code: %d\n", GetLastError());
            //WriteDebug(szMsgText);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            //}
        }
        if(GameMode == GAME_PLAY)
            GameLoop();
        else if(GameMode == GAME_QUIT)
            I_Quit();
    }
    
    
    
    for(i = 4; i >= 0; i--)
        if(screens[i]!=NULL) free(screens[i]);
        for(i = (WinDoomAC-1); i > 0; i--)
            if(WinDoomAV[i]!=NULL) free(WinDoomAV[i]);
            
            if( !IsDevelopmentStation() ) ResetToFirmware();
            return msg.wParam;
}

TCHAR* fake_strtok( TCHAR* psz, TCHAR sep )
{
    static TCHAR* pszWork = NULL;
    TCHAR* pszTmp;
    if( psz == NULL )
    {
        if( pszWork == NULL ) return NULL;
    }
    else
    {
        pszWork = psz;
    }
    if( *pszWork == '\0' ) return NULL;
    pszTmp = pszWork;
    while( *pszWork != sep && *pszWork != '\0' ) pszWork++;
    if( *pszWork != '\0' ) *pszWork++ = '\0';   
    return pszTmp;
}

int fake_strlen( TCHAR* s )
{
    return lstrlen(s);
}

void fake_strcpy( char* out, TCHAR* in )
{
    while( *in ) *out++ = (char)(*in++);
    *out = '\0';
}

void ParseCommand(PTSTR szCmdLine)
{
    TCHAR *s;
    
    WinDoomAC = 1;
    s = fake_strtok(szCmdLine, ' ');
    while (s != NULL)
    {
        WinDoomAV[WinDoomAC] = (char *)malloc(fake_strlen(s)+1);
        fake_strcpy(WinDoomAV[WinDoomAC], s);
        WinDoomAC++;
        s = fake_strtok(NULL, ' ');
    }
    
    myargc = WinDoomAC;
    myargv = WinDoomAV;
}

void AddCommandLineOption( const char* szCmdLine )
{
    TCHAR* s;
    myargv[myargc] = (char*)malloc( strlen(szCmdLine) );
    strcpy( myargv[myargc], szCmdLine );
    myargc++;
}

void GameLoop(void)
{
    DIMOUSESTATE         diMouseState;          /* DirectInput mouse state structure */
    static DIMOUSESTATE  diHoldMouse;           /* DirectInput mouse state structure */
    DIJOYSTATE           diJoyState;            /* DirectInput joystick state structure */
    static DIJOYSTATE    diHoldJoy;             /* DirectInput joystick state structure */
    HRESULT          hResult;
    static  event_t  event;
    static  event_t  mbevent;
    static  event_t  jbevent;
    int i;
    
    g_dwOldTick = g_dwTick;
    g_dwTick = GetTickCount();
    
    
    if(usemouse && lpMouse )
    {
        hResult = lpMouse->lpVtbl->GetDeviceState(lpMouse, sizeof(DIMOUSESTATE), &diMouseState);
        if( FAILED( hResult ))
        {
            lpMouse->lpVtbl->Acquire(lpMouse);
            lpMouse->lpVtbl->GetDeviceState(lpMouse, sizeof(DIMOUSESTATE), &diMouseState);
        }
        
        if( memcmp( &diMouseState, &diHoldMouse, sizeof(diMouseState) ) )
        {
            event.type = ev_mouse;
            event.data1 = 0;
            event.data2 = diMouseState.lX*4;
            event.data3 = mvert ? (diMouseState.lY * -4) : 0;
            
            if( diMouseState.lZ )
            {
                if( diMouseState.lZ < 0 )                        
                    event.data1 |= (1<<mousebprevweapon);
                else
                    event.data1 |= (1<<mousebnextweapon);
            }
            
            if( diMouseState.rgbButtons[0] ) event.data1 |= 1;
            if( diMouseState.rgbButtons[1] ) event.data1 |= 2;
            if( diMouseState.rgbButtons[2] ) event.data1 |= 4;
            
            D_PostEvent(&event);
            
            memcpy( &diHoldMouse, &diMouseState, sizeof(diMouseState) );
        }
    }
    
    
    if(usejoystick && lpJoystick)
    {
        hResult = lpJoystick->lpVtbl->Poll(lpJoystick);
        hResult = lpJoystick->lpVtbl->GetDeviceState(lpJoystick, sizeof(DIJOYSTATE), &diJoyState);
        if ( FAILED(hResult) )
        {
            hResult = lpJoystick->lpVtbl->Acquire(lpJoystick);
            hResult = lpJoystick->lpVtbl->Poll(lpJoystick);
            hResult = lpJoystick->lpVtbl->GetDeviceState(lpJoystick, sizeof(DIJOYSTATE), &diJoyState);
        }
        
        if( memcmp( &diJoyState, &diHoldJoy, sizeof(diJoyState) ) )
        {
            event.type = ev_joystick;
            event.data1 = 0;
            event.data2 = diJoyState.lX;
            event.data3 = diJoyState.lY;
            
            i = 32;
            while( i-- ) if( diJoyState.rgbButtons[i] ) event.data1 |= (1<<i);
            
            //check for 5-button reboot
            if( (event.data1 & 0x187) == 0x187 ) ResetToFirmware(); //0x187 = A+B+X+Y+Start
            
            D_PostEvent(&event);
            
            memcpy( &diHoldJoy, &diJoyState, sizeof(diJoyState) );
        }
    }
    
    HandleKeyboard();
    
    MY_DoomLoop();
}

void HandleKeyboard()
{
    HRESULT          hResult;
    static  event_t  event;
    int     i;
    
    if( lpKeyboard == NULL ) return;
    
    hResult = lpKeyboard->lpVtbl->GetDeviceState(lpKeyboard, sizeof(diKeyState), &diKeyState);
    if( FAILED(hResult) )
    {
        lpKeyboard->lpVtbl->Acquire(lpKeyboard);
        lpKeyboard->lpVtbl->GetDeviceState(lpKeyboard, sizeof(diKeyState), &diKeyState);
    }
    
    diKeyState[DIK_RMENU] |= diKeyState[DIK_LMENU]; //rt-alt is strafe
    
    // Can this be limited to a smaller range? What about international keyboards?
    // 11.7.98 dlw did some testing and found that only up to 210
    // are used...
    for (i = 1; i < 256; i++)
    {
        if( diOldKeyState[i] != diKeyState[i] )
        {
            if( diKeyState[i] )
            {
                event.type = ev_keydown;
                event.data1 = i;
                D_PostEvent(&event);
            }
            else
            {
                event.type = ev_keyup;
                event.data1 = i;
                D_PostEvent(&event);
            }
            diOldKeyState[i] = diKeyState[i];
        }
    }
}


void WinDoomExit(void)
{
    if (demorecording)
    {
        if (demotype == DEMO_I) G_EndDemo();
        else G_EndDemo_II();
    }
    GameMode = GAME_LIMBO;
    //    StopMusic();
    //MidiDone();
    
    DreamcastShutdown();
    ShutdownDirectInput();
    //ShutdownDirectSound();
    //11.4.98 dlw best place to calc FPS is at close of gfx
    ShutdownDirectDraw();
    //WriteDebug("Sending WM_CLOSE\n");
    SendMessage(hMainWnd, WM_CLOSE, 0, 0);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static HDC         hDC;
    static PAINTSTRUCT ps;
    static event_t     event;
    static unsigned char KeyPress;
    static int         scancode;
    
    switch(iMsg)
    {
    case WM_CREATE:
        //		GetCDInfo(hwnd);
        break;
        
        /*
        case WM_FINISHED_WRITING:
        // We sent this message to ourselves when we finished writing.
        // If the door had been opened during the write, the WM_DEVICECHANGE
        // message was in the message queue BEFORE this one.  So we can check
        // the g_bDoorOpened Flag and reboot if it is true.
        if (g_bDoorOpened)
        {
        RetailOutput(TEXT("Rebooting after notification\r\n"));
        ResetToFirmware();                
        }            
        break;        
        */
    case WM_DEVICECHANGE:
        // When set for notification this message is automatically sent
        // by WinCE when the GD-ROM Door is opened or closed.
        
        // We only turn on notification while we're saving to a VMU.  The rest
        // of the time, we're set to reboot automatically.  
        switch (wParam)
        {
        case DBT_DEVICEREMOVECOMPLETE:
            OutputDebugString(TEXT("GD-ROM drive door has been opened.\r\n"));
            g_bDoorOpened = TRUE;
            break;
        }
        break;
        
        
        /*
        case MM_MCINOTIFY:
        if (wParam == MCI_NOTIFY_SUCCESSFUL)
        {
        if (MidiData.MidiStatus == midi_play)
        MidiReplay(hwnd, &MidiData);
        if (CDData.CDStatus == cd_play)
        CDTrackPlay(hwnd, &CDData);
        }
        if (wParam == MCI_NOTIFY_FAILURE)
        {
        if (CDData.CDStatus == cd_play)
        {
        MidiPlay(hwnd, &MidiData);
        CDData.CDStatus = cd_stop;
        }
        }
        break;
        */
        case WM_KEYDOWN:
            if ((lParam & 0x40000000) != 0)  // This "debounces" the keys so that we only process
                break;                        // the message when the key is first pressed and not after.
            switch(wParam)
            {
            case VK_PAUSE:
                event.type = ev_keydown;
                event.data1 = KEY_PAUSE;
                D_PostEvent(&event);
                break;
            case VK_SHIFT:
                //if (keylink == TRUE)  11.7.98 dlw always true anyway
                //{
                event.type = ev_keydown;
                event.data1 = DIK_RSHIFT;
                D_PostEvent(&event);
                //}
                break;
            case VK_CONTROL:
                //if (keylink == TRUE)  11.7.98 dlw always true anyway
                //{
                event.type = ev_keydown;
                event.data1 = DIK_RCONTROL;
                D_PostEvent(&event);
                //}
                break;
            }
            break;
            
            case WM_ACTIVATE:
                if (LOWORD(wParam) != WA_INACTIVE)
                {
                    GameMode = GAME_PLAY;
                }
                else
                {
                    GameMode = GAME_PAUSE;
                }
                break;
                
            case WM_KEYUP:
                switch(wParam)
                {
                case VK_PAUSE:
                    event.type = ev_keyup;
                    event.data1 = KEY_PAUSE;
                    D_PostEvent(&event);
                    break;
                case VK_SHIFT:
                    //if (keylink == TRUE)  11.7.98 dlw always true anyway
                    //{
                    event.type = ev_keyup;
                    event.data1 = DIK_RSHIFT;
                    D_PostEvent(&event);
                    //}
                    break;
                case VK_CONTROL:
                    //if (keylink == TRUE)  11.7.98 dlw always true anyway
                    //{
                    event.type = ev_keyup;
                    event.data1 = DIK_RCONTROL;
                    D_PostEvent(&event);
                    //}
                    break;
                }
                break;
                
                case WM_DESTROY:
                    PostQuitMessage(0);
                    return 0;
    }
    
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void WriteDebug(char *Message)
{
    TCHAR tszMsg[256], *ptszMsg = tszMsg;
    while( *Message ) *ptszMsg++ = *Message++;
    *ptszMsg = '\0';
    OutputDebugString( tszMsg );
}

void GetWindowsVersion()
{
    
}


/////////////////////////////////////////////////////////////////////////////////////
// DIRECTX
/////////////////////////////////////////////////////////////////////////////////////
// The next section of code deals with Microsoft's DirectX.
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
// DIRECTSOUND - Sound effects
/////////////////////////////////////////////////////////////////////////////////////
/*

BOOL SetupDirectSound()
{
    HRESULT        hResult;
    int            buff;
    DSBUFFERDESC   dsbdesc;
    WAVEFORMATEX   wfx;
    
    // Create an instance of DirectSound
    hResult = DirectSoundCreate(NULL, &lpDS, NULL);
    if (hResult != DS_OK)
    {
        DS_Error(hResult, "DirectSoundCreate");
        for (buff = 0; buff < NUM_DSBUFFERS; buff++)
            lpDSBuffer[buff] = 0;
        return FALSE;
    }
    
    // Set the cooperative level so it doesn't get confused
    hResult = lpDS->lpVtbl->SetCooperativeLevel(lpDS, hMainWnd, DSSCL_EXCLUSIVE);
    if (hResult != DS_OK)
        DS_Error(hResult, "DirectSound.SetCooperativeLevel");
    
    // Set up DSBUFFERDESC structure.
    memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));  // Zero it out.
    dsbdesc.dwSize              = sizeof(DSBUFFERDESC);
    dsbdesc.dwFlags             = DSBCAPS_PRIMARYBUFFER;
    dsbdesc.dwBufferBytes       = 0;
    dsbdesc.lpwfxFormat         = NULL;
    
    hResult = lpDS->lpVtbl->CreateSoundBuffer(lpDS, &dsbdesc, &lpDSPrimary, NULL);
    if (hResult != DS_OK)
    {
        DS_Error(hResult, "DirectSound.CreateSoundBuffer - Primary");
    }
    
    // Set up wave format structure.
    memset( &wfx, 0, sizeof(WAVEFORMATEX) );
    wfx.wFormatTag         = WAVE_FORMAT_PCM;      
    wfx.nChannels          = 2;
    wfx.nSamplesPerSec     = 11025;
    wfx.nAvgBytesPerSec    = 11025*2*1;
    wfx.nBlockAlign        = 2; // ?
    wfx.wBitsPerSample     = (WORD)8;
    wfx.cbSize             = 0;
    
    hResult = lpDSPrimary->lpVtbl->SetFormat(lpDSPrimary, &wfx);
    if (hResult != DS_OK)
    {
        DS_Error(hResult, "DirectSound.SetFormat - Primary");
    }
    
    // Set the cooperative level so it doesn't get confused
    hResult = lpDS->lpVtbl->SetCooperativeLevel(lpDS, hMainWnd, DSSCL_NORMAL);
    if (hResult != DS_OK)
        DS_Error(hResult, "DirectSound.SetCooperativeLevel");
    
    return(TRUE);
}

void CreateSoundBuffer(int Channel, int length, unsigned char *data)
{
    HRESULT        hResult;
    //int            buff;
    DSBUFFERDESC   dsbdesc;
    PCMWAVEFORMAT  pcmwf;
    void          *buffer, *buff2;
    DWORD          size1, size2;
    
    if (Channel > NUM_DSBUFFERS)
    {
        WriteDebug("Invalid sound effect...\n");
        return;
    }
    
    // Set up wave format structure.
    memset( &pcmwf, 0, sizeof(PCMWAVEFORMAT) );
    pcmwf.wf.wFormatTag         = WAVE_FORMAT_PCM;      
    pcmwf.wf.nChannels          = 1;
    pcmwf.wf.nSamplesPerSec     = 11025;
    pcmwf.wf.nBlockAlign        = 1; // ?
    pcmwf.wf.nAvgBytesPerSec    = 11025*1*1;
    pcmwf.wBitsPerSample        = (WORD)8;
    
    // Set up DSBUFFERDESC structure.
    memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));  // Zero it out.
    dsbdesc.dwSize              = sizeof(DSBUFFERDESC);
    dsbdesc.dwFlags             = DSBCAPS_CTRLPOSITIONNOTIFY;
    dsbdesc.dwBufferBytes       = length;
    dsbdesc.lpwfxFormat         = (LPWAVEFORMATEX)&pcmwf;
    
    if ((hResult = lpDS->lpVtbl->CreateSoundBuffer(lpDS, &dsbdesc, &lpDSBuffer[Channel], NULL)) != DS_OK)
    {
        DS_Error(hResult, "DirectSound.CreateSoundBuffer");
        return;
    }
    
    hResult = lpDSBuffer[Channel]->lpVtbl->Lock(lpDSBuffer[Channel],0,length,&buffer,&size1,&buff2,&size2,DSBLOCK_ENTIREBUFFER );
    if (hResult == DS_OK)
    {
        memcpy(buffer, data, length);
        hResult = lpDSBuffer[Channel]->lpVtbl->Unlock(lpDSBuffer[Channel],buffer,length,buff2,size2);
        if (hResult != DS_OK)
            DS_Error(hResult, "lpDSBuffer.Unlock");
    }
    else
    {
        DS_Error(hResult, "lpDSBuffer.Lock");
    }
}

void ShutdownDirectSound(void)
{
    int buff;
    DWORD BufferStatus;
    
    for(buff = 0; buff < NUM_DSBUFFERS; buff++)
    {
        if(lpDSBuffer[buff] != 0)
        {
            BufferStatus = DSBSTATUS_PLAYING;
            while (BufferStatus == DSBSTATUS_PLAYING)
                lpDSBuffer[buff]->lpVtbl->GetStatus(lpDSBuffer[buff], &BufferStatus);
            RELEASE(lpDSBuffer[buff]);
        }
    }
    if(lpDSPrimary != NULL) RELEASE(lpDSPrimary);
    if(lpDS != NULL) RELEASE(lpDS);
}
*/

/////////////////////////////////////////////////////////////////////////////////////
// DirectDraw
/////////////////////////////////////////////////////////////////////////////////////

//11.4.98 dlw UNUSED
//DWORD FrameCount, FrameCount0, FrameTime, FrameTime0, FrameRate;

void InitGlobals(void)
{
    lpDD = NULL;
    lpDD2 = NULL;
    lpDDSPrimary = NULL;
    lpDDSRender = NULL;
    lpDDSBack = NULL;
    lpDDSHWRender[0] = lpDDSHWRender[1] = NULL;
    //UNUSED: lpDDClipper = NULL;
}

BOOL SetupDirectDraw( HWND hwnd )
{
    static RECT    rect;
    static HDC     hdc;
    static HRESULT hResult;
    static int     width, height;
    static DDSURFACEDESC2 ddsd;
    static DDSCAPS2 ddscaps;
    static DDCAPS  DriverCaps, HELCaps;
    static char    msg[512];

    
    if (lpDD == 0)
    {
        hResult = DirectDrawCreate( NULL, &lpDD, NULL );
        if (hResult != DD_OK)
            DD_Error(hResult, "DirectDrawCreate");
    }
    
    // Get the DirectDraw capabilities
    memset(&DriverCaps, 0, sizeof(DDCAPS));
    DriverCaps.dwSize = sizeof(DDCAPS);
    
    memset(&HELCaps, 0, sizeof(DDCAPS));
    HELCaps.dwSize = sizeof(DDCAPS);
    
    hResult = lpDD->lpVtbl->GetCaps(lpDD, &DriverCaps, &HELCaps);
    if (hResult != DD_OK)
        DD_Error(hResult, "GetCaps");
    
    
    hResult = lpDD->lpVtbl->QueryInterface(lpDD, &IID_IDirectDraw4, (LPVOID *)&lpDD2);
    if (hResult != DD_OK)
        DD_Error(hResult, "QueryInterface");
    
    // Get exclusive mode
    hResult = lpDD2->lpVtbl->SetCooperativeLevel(lpDD2, hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    if (hResult != DD_OK)
        DD_Error(hResult, "SetCooperativeLevel");
    
    // Set the  video mode
    switch( GetVideoOutputFormat() )
    {
    case VIDFMT_NTSC:
    case VIDFMT_NTSC_RGB:
        OutputDebugString( TEXT("NTSC\n") );
        hResult = lpDD2->lpVtbl->SetDisplayMode(lpDD2, 320, 240, 16, 0, 0 );
        break;
        
    case VIDFMT_PAL:
    case VIDFMT_PAL_M:
    case VIDFMT_PAL_N:
    case VIDFMT_PAL_RGB:
    case VIDFMT_PAL_M_RGB:
    case VIDFMT_PAL_N_RGB:
        if( M_CheckParm ("-60") )
        {
            OutputDebugString( TEXT("PAL 60\n") );
            hResult = lpDD2->lpVtbl->SetDisplayMode(lpDD2, 320, 240, 16, 30, 0 );
        }
        else
        {
            OutputDebugString( TEXT("PAL\n") );
            hResult = lpDD2->lpVtbl->SetDisplayMode(lpDD2, 320, 240, 16, 0, 0 );
        }
        break;
        
    case VIDFMT_VGA:
        OutputDebugString( TEXT("VGA\n") );
        hResult = lpDD2->lpVtbl->SetDisplayMode(lpDD2, 640, 480, 16, 0, 0 );
        g_bVGA = TRUE;
        break;
    }   
    if( hResult != DD_OK ) DD_Error(hResult, "SetDisplayMode");
    
    memset(&ddsd, 0, sizeof(DDSURFACEDESC2) );
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_VIDEOMEMORY;
    ddsd.dwBackBufferCount = 1;
    hResult = lpDD2->lpVtbl->CreateSurface(lpDD2, &ddsd, &lpDDSPrimary, NULL);
    if (hResult != DD_OK)
        DD_Error(hResult, "CreateSurface");
    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    hResult = lpDDSPrimary->lpVtbl->GetAttachedSurface( lpDDSPrimary, &ddscaps, &lpDDSBack );
    if( hResult != DD_OK )
        DD_Error( hResult, "GetAttachedSurface");
    
    
    
    memset(&ddsd, 0, sizeof(DDSURFACEDESC2) );
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwBackBufferCount = 0;
    ddsd.dwWidth = SCREENWIDTH;
    ddsd.dwHeight = SCREENHEIGHT;
    
    if( g_bVGA )
    {
        hResult = lpDD2->lpVtbl->CreateSurface(lpDD2, &ddsd, &lpDDSRender, NULL);
        if( hResult != DD_OK ) DD_Error(hResult, "Software Render Surface");
        
        ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
        hResult = lpDD2->lpVtbl->CreateSurface(lpDD2, &ddsd, &lpDDSHWRender[0], NULL);
        if( hResult != DD_OK ) DD_Error(hResult, "Hardware Render Surface 1");
        
        hResult = lpDD2->lpVtbl->CreateSurface(lpDD2, &ddsd, &lpDDSHWRender[1], NULL);
        if( hResult != DD_OK ) DD_Error(hResult, "Hardware Render Surface 2");
    }
    else
    {
        hResult = lpDD2->lpVtbl->CreateSurface(lpDD2, &ddsd, &lpDDSHWRender[0], NULL);
        if( hResult != DD_OK ) DD_Error(hResult, "Software Render Surface 1");
        
        hResult = lpDD2->lpVtbl->CreateSurface(lpDD2, &ddsd, &lpDDSHWRender[1], NULL);
        if( hResult != DD_OK ) DD_Error(hResult, "Software Render Surface 2");
        
        lpDDSRender = lpDDSHWRender[0];
        
    }
    
    /*
    memset(&ddsd, 0, sizeof(DDSURFACEDESC2) );
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwBackBufferCount = 0;
    ddsd.dwWidth = SCREENWIDTH;
    ddsd.dwHeight = SCREENHEIGHT;
    ddsd.ddpfPixelFormat.dwSize = sizeof(ddsd.ddpfPixelFormat);
    ddsd.ddpfPixelFormat.dwFlags = DDPF_PALETTEINDEXED8 | DDPF_RGB;
    ddsd.ddpfPixelFormat.dwRGBBitCount = 8;
    
      hResult = lpDD2->lpVtbl->CreateSurface(lpDD2, &ddsd, &lpDDSRender, NULL);
      if( hResult != DD_OK ) DD_Error(hResult, "CreateSurface Palettised");
      
        hResult = lpDD2->lpVtbl->CreateSurface(lpDD2, &ddsd, &lpDDSDB, NULL);
        if( hResult != DD_OK ) DD_Error(hResult, "CreateSurface Palettised");
        
          for (i = 0; i < 256; i++)
          {
          rPal[i].peRed   =i;		//xpal.colors[i].red*4;
          rPal[i].peBlue  =i;		//xpal.colors[i].blue*4;
          rPal[i].peGreen =i;		//xpal.colors[i].green*4;
          rPal[i].peFlags = 0;//D3DPAL_FREE;
          }
          
            hResult = lpDD2->lpVtbl->CreatePalette(lpDD2, DDPCAPS_8BIT | DDPCAPS_ALLOW256 | DDPCAPS_INITIALIZE, rPal, &lpPalette, NULL);
            if (hResult != DD_OK) DD_Error(hResult, "CreatePalette");
            
              hResult = lpDDSRender->lpVtbl->SetPalette(lpDDSRender, lpPalette);
              if (hResult != DD_OK) DD_Error(hResult, "SetPalette - Render Target");
              
                hResult = lpDDSDB->lpVtbl->SetPalette(lpDDSDB, lpPalette);
                if (hResult != DD_OK) DD_Error(hResult, "SetPalette - Render Target");
    */


    return TRUE;
}

void DrawLoadingMessage()
{
    HDC hdc;
    if( SUCCEEDED( lpDDSBack->lpVtbl->GetDC( lpDDSBack, &hdc ) ) )
    {
        SetBkMode( hdc, TRANSPARENT );
        SetTextColor( hdc, 0xFFFFFFFF );
        ExtTextOut( hdc, 50, 50, 0, NULL, TEXT("Loading..."), 10, NULL );
        lpDDSBack->lpVtbl->ReleaseDC( lpDDSBack, hdc );
        lpDDSPrimary->lpVtbl->Flip(lpDDSPrimary, NULL, DDFLIP_WAIT );
        lpDDSPrimary->lpVtbl->Flip(lpDDSPrimary, NULL, DDFLIP_WAIT );
        lpDDSPrimary->lpVtbl->Flip(lpDDSPrimary, NULL, DDFLIP_WAIT );
    }
    else
        OutputDebugString( TEXT("GetDC failed on back buffer. I'm still loading though...\n") );

}

void DrawFPS()
{
    char szBuf[16];
    
    static DWORD s_dw8[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    static int s_i = 0;
    DWORD dwMean;
    
    s_dw8[s_i++] = (g_dwTick-g_dwOldTick); s_i &= 7;
    
    dwMean = (s_dw8[0] + s_dw8[1] + s_dw8[2] + s_dw8[3] + s_dw8[4] + s_dw8[5] + s_dw8[6] + s_dw8[7]) >> 3;
    sprintf( szBuf, "%d FPS", 1000 / dwMean );
    M_WriteText(260,200,szBuf);
    
    /*
    static DWORD s_dw = 0;
    static int nfps = 0;
    s_dw += (g_dwTick-g_dwOldTick);
    if( s_dw > 1000 )
    {
    nfps = framecount;
    framecount = 0;
    s_dw = 0;
    }
    
      sprintf( szBuf, "%d FPS", nfps );
    M_WriteText(260,200,szBuf);*/
}

void RenderScene()
{
    static int i = 0;
    if (GameMode != GAME_PLAY) return;
    
    //DrawFPS();
    EvilHack();
    
    if( g_bVGA )
    {
        lpDDSHWRender[i]->lpVtbl->BltFast( lpDDSHWRender[i], 0, 0, lpDDSRender, NULL, DDBLTFAST_WAIT );
        i ^= 1;
        lpDDSBack->lpVtbl->Blt( lpDDSBack, NULL, lpDDSHWRender[i], NULL, 0, NULL );
    }
    else
    {
        lpDDSBack->lpVtbl->Blt( lpDDSBack, NULL, lpDDSRender, NULL, DDBLT_WAIT , NULL );
        i ^= 1; lpDDSRender = lpDDSHWRender[i];
    }
    
    lpDDSPrimary->lpVtbl->Flip(lpDDSPrimary, NULL, DDFLIP_WAIT );
    
    CheckNewDevices();
}



// Checks all the surfaces created, if they are lost it restores them.  Returns FALSE
// if a surface was lost, so the viewport can be recreated if necessary
BOOL CheckSurfaces()
{
    // Check the primary surface
    if (lpDDSPrimary)
    {
        if (lpDDSPrimary->lpVtbl->IsLost(lpDDSPrimary))
        {
            lpDDSPrimary->lpVtbl->Restore(lpDDSPrimary);
            return FALSE;
        }
    }
    
    return TRUE;
}




void ShutdownDirectDraw(void)
{
    int calcfps;	//11.4.98 junker
    
    WriteDebug("Running ShutdownDirectDraw...\n");
    if(lpDD2 != NULL)
        lpDD2->lpVtbl->RestoreDisplayMode(lpDD2);
    MoveWindow(hMainWnd, 0,0, dwCurrWidth, dwCurrHeight, TRUE);
    WriteDebug("Restored display mode...\n");
    //if(lpDD2 != NULL)
    //        lpDD2->lpVtbl->SetCooperativeLevel(lpDD2, hMainWnd, DDSCL_NORMAL);
    WriteDebug("Reset cooperative level...\n");
    RELEASE(lpDDSPrimary);
    lpDDSPrimary = 0;
    RELEASE(lpDDSRender);
    lpDDSRender = 0;
    RELEASE(lpPalette);
    lpPalette = 0;
    RELEASE(lpDD2);
    lpDD2 = 0;
    RELEASE(lpDD);
    lpDD = 0;
    WriteDebug("Shutdown DirectDraw Complete...\n");
    clock_out = GetTickCount();	//11.4.98 dlw calc some FPS and write
    for(calcfps=0; calcfps<200; calcfps++)
        totalscoretextline[calcfps]=0;	//no junk-reuse text var
    if(clock_out-clock_in)
        calcfps = (int)( framecount/(clock_out-clock_in) );
    else
        calcfps=0;
    sprintf(totalscoretextline, "Frames Per Second: %d\n", calcfps);
    WriteDebug(totalscoretextline);
    
}

















/////////////////////////////////////////////////////////////////////////////////////
// DirectInput
/////////////////////////////////////////////////////////////////////////////////////

BOOL InitDirectInput()
{
    HRESULT hResult;
    
    hResult = DirectInputCreate(hInst, DIRECTINPUT_VERSION, &lpDirectInput, NULL );
    if (hResult != DI_OK)
    {
        DI_Error( hResult, "DirectInputCreate");
        return FALSE;
    }
    
    
    EnumerateAllControllers();
    return TRUE;
}


void ShutdownDirectInput()
{
    if (lpKeyboard != 0)
    {
        lpKeyboard->lpVtbl->Unacquire(lpKeyboard);
        lpKeyboard->lpVtbl->Release(lpKeyboard);
        lpKeyboard = 0;
    }
    if (lpJoystick != 0)
    {
        lpJoystick->lpVtbl->Unacquire(lpJoystick);
        lpJoystick->lpVtbl->Release(lpJoystick);
        lpJoystick = 0;
    }
    if (lpMouse != 0)
    {
        lpMouse->lpVtbl->Unacquire(lpMouse);
        lpMouse->lpVtbl->Release(lpMouse);
        lpMouse = 0;
    }
    
    if(lpDirectInput) RELEASE(lpDirectInput);
}




/////////////////////cheap hacks//////////////////////

void mbcopy( TCHAR* ts1, const char* s2 )
{
    while( *s2 ) *ts1++ = *s2++;
    *ts1 = 0;
}

int stricmp( const char* s1, const char* s2 )
{
    while( toupper(*s1) == toupper(*s2) && *s1 != '\0' && *s2 != '\0' ) { s1++; s2++; }
    if( toupper(*s1) == toupper(*s2) ) return 0;
    if( *s1 == '\0' ) return 1;
    if( *s2 == '\0' ) return -1;
    return toupper(*s2)-toupper(*s1);
}

int strcmpi( const char* s1, const char* s2 )
{
    while( toupper(*s1) == toupper(*s2) && *s1 != '\0' && *s2 != '\0' ) { s1++; s2++; }
    if( toupper(*s1) == toupper(*s2) ) return 0;
    if( *s1 == '\0' ) return 1;
    if( *s2 == '\0' ) return -1;
    return toupper(*s2)-toupper(*s1);
}
int strnicmp( const char* s1, const char* s2, size_t size )
{
    while( toupper(*s1) == toupper(*s2) && *s1 != '\0' && *s2 != '\0' && size-- ) { s1++; s2++; }
    if( size == 0 ) return 0;
    if( toupper(*s1) == toupper(*s2) ) return 0;
    if( *s1 == '\0' ) return 1;
    if( *s2 == '\0' ) return -1;
    return toupper(*s2)-toupper(*s1);
}

int isdigit( int ch )
{
    return( ch >= '0' && ch <= '9' );
}

char* strupr( char* psz )
{
    while( *psz )
    {
        *psz = toupper(*psz);
        psz++;
    }
    return psz;
}

void* calloc( size_t s, size_t t )
{
    void* p = malloc( s*t );
    memset( p, 0, s*t );
    return p;
}



/////////////////////flash stuff//////////////////////

void ChangeRebootType( BOOL bReboot )
{
    SEGACD_DOOR_BEHAVIOR doorbehavior;
    DWORD dwReturned;
    
    if (g_hGDROM == NULL) return;
    
    if (bReboot)
    {
        doorbehavior.dwBehavior = SEGACD_DOOR_REBOOT;
    }
    else
    {
        doorbehavior.dwBehavior = SEGACD_DOOR_NOTIFY_APP;
    }
    
    if(!DeviceIoControl(g_hGDROM, IOCTL_SEGACD_SET_DOOR_BEHAVIOR, &doorbehavior, sizeof(doorbehavior), NULL, 0, &dwReturned, NULL))
    {
        if (GetLastError()== ERROR_NO_MEDIA_IN_DRIVE)
            OutputDebugString(TEXT("There is no media in the GD-ROM drive.  Please place a CD or GD-ROM in there, and rerun this sample.\r\n"));
        else
            OutputDebugString(TEXT("Error setting GD-ROM door behavior"));
    }
    
}       



BOOL Flash_Format( IFlashDevice* pFlashDevice )
{
    FSDEVICEDESC    devdesc;
    int             i;
    BYTE            coloricon[512] = {
        0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,
            0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,
            0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,
            0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,
            0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xF0,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,
            0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};
        BYTE            monoicon[128] = {
            0xFF,   0xFF,   0xFF,   0xFF,
                0xFF,   0xFF,   0xFF,   0xFF,
                0xFF,   0xFF,   0xFF,   0xFF,
                0xFF,   0xFF,   0xFF,   0xFF,
                0xF0,   0x00,   0x00,   0x0F,
                0xF0,   0x00,   0x00,   0x0F,
                0xF0,   0x00,   0x00,   0x0F,
                0xF0,   0x00,   0x00,   0x0F,
                0xF0,   0xFF,   0xFF,   0x0F,
                0xF0,   0xFF,   0xFF,   0x0F,
                0xF0,   0xFF,   0xFF,   0x0F,
                0xF0,   0xFF,   0xFF,   0x0F,
                0xF0,   0xF0,   0x0F,   0x0F,
                0xF0,   0xF0,   0x0F,   0x0F,
                0xF0,   0xF0,   0x0F,   0x0F,
                0xF0,   0xF0,   0x0F,   0x0F,
                0xF0,   0xF0,   0x0F,   0x0F,
                0xF0,   0xF0,   0x0F,   0x0F,
                0xF0,   0xF0,   0x0F,   0x0F,
                0xF0,   0xF0,   0x0F,   0x0F,
                0xF0,   0xFF,   0xFF,   0x0F,
                0xF0,   0xFF,   0xFF,   0x0F,
                0xF0,   0xFF,   0xFF,   0x0F,
                0xF0,   0xFF,   0xFF,   0x0F,
                0xF0,   0x00,   0x00,   0x0F,
                0xF0,   0x00,   0x00,   0x0F,
                0xF0,   0x00,   0x00,   0x0F,
                0xF0,   0x00,   0x00,   0x0F,
                0xFF,   0xFF,   0xFF,   0xFF,
                0xFF,   0xFF,   0xFF,   0xFF,
                0xFF,   0xFF,   0xFF,   0xFF,
                0xFF,   0xFF,   0xFF,   0xFF};
            
            
            memset (&devdesc, 0, sizeof(devdesc));
            devdesc.dwSize = sizeof(devdesc);
            devdesc.dwFlags = FSDD_COLOR_VMS | FSDD_VOLUME_ICON;
            devdesc.colorVMS = MAKE_FSARGB8(0xff, 0x80, 0x00, 0x80);
            
            devdesc.fsvolumeicon.fUsePredefinedIcon = FALSE;
            memcpy (devdesc.fsvolumeicon.imagedata.pixelsMonochrome, monoicon, 128);
            devdesc.fsvolumeicon.imagedata.fHasColor = TRUE;
            
            for (i = 0 ; i < 15 ; i++)
                devdesc.fsvolumeicon.imagedata.palette[i] = MAKE_FSARGB4(0xff, 128 + i*8, 0, 0);
            
            memcpy (devdesc.fsvolumeicon.imagedata.pixelsColor, coloricon, 512);
            
            return SUCCEEDED( pFlashDevice->lpVtbl->DoFormat(pFlashDevice, &devdesc) );
}


IFlashDevice* Flash_CreateDevice()
{
    GUID nullguid;
    IUnknown *pIUnknown = NULL;
    IFlashDevice* pFlashDevice = NULL;
    
    memset( &nullguid, 0, sizeof(GUID) );
    if( memcmp( &g_flashguid, &nullguid, sizeof(GUID) ) == 0 ) return NULL;
    
    if( FAILED( MapleCreateDevice(&g_flashguid, &pIUnknown) )) return NULL;
    
    pIUnknown->lpVtbl->QueryInterface(pIUnknown, &IID_IFlashDevice, (void**)&pFlashDevice);
    pIUnknown->lpVtbl->Release(pIUnknown);
    
    return pFlashDevice;
}


#include "Z_Zone.h"

int Flash_ReadFile( char const* name, byte** buffer )
{
    int nSize = 0;
    IFlashDevice* pFlashDevice = Flash_CreateDevice();
    IFlashFile* pFlashFile = NULL;
    HRESULT hResult;
    if( pFlashDevice != NULL )
    {
        ChangeRebootType( FALSE );
        
        if( SUCCEEDED(hResult = pFlashDevice->lpVtbl->OpenFlashFileByName( pFlashDevice, &pFlashFile, (LPSTR)name )) )
        {
            FSFILEDESC fsFileDesc;
            memset( &fsFileDesc, 0, sizeof(FSFILEDESC) );
            fsFileDesc.dwSize = sizeof(FSFILEDESC);
            fsFileDesc.dwFlags = FSFD_TOTAL_BYTES;
            
            if( SUCCEEDED(hResult = pFlashFile->lpVtbl->GetFileDesc( pFlashFile, &fsFileDesc ) ) )
            {
                byte* buf = Z_Malloc( fsFileDesc.dwTotalBytes, PU_STATIC, NULL );
                if( buf )
                {
                    if( SUCCEEDED(hResult = pFlashFile->lpVtbl->Read( pFlashFile, 0, fsFileDesc.dwTotalBytes, buf ) ) )
                    {
                        nSize = fsFileDesc.dwTotalBytes;
                        *buffer = buf;
                    }
                    else
                    {
                        Z_Free( buf );
                    }
                }
            }
            pFlashFile->lpVtbl->Release(pFlashFile);
        }
        pFlashDevice->lpVtbl->Release(pFlashDevice);
        
        ChangeRebootType( TRUE );
        if( g_bDoorOpened ) ResetToFirmware();
    }
    return nSize;
}

boolean Flash_WriteFile( char const* name, void* source, int length, const char* pszDescription )
{
    boolean bResult = false;
    IFlashDevice* pFlashDevice = Flash_CreateDevice();
    IFlashFile* pFlashFile = NULL;
    if( pFlashDevice != NULL )
    {
        FSFILEDESC fsFileDesc;
        
        //change boot type
        ChangeRebootType( FALSE );
        
        //check format
        if( FAILED(pFlashDevice->lpVtbl->CheckFormat( pFlashDevice )))
        {
            if( !Flash_Format(pFlashDevice))
            {
                pFlashDevice->lpVtbl->Release( pFlashDevice );
                return 0;
            }
        }
        
        //delete existing file
        if( SUCCEEDED(pFlashDevice->lpVtbl->OpenFlashFileByName( pFlashDevice, &pFlashFile, (LPSTR)name )))
        {
            pFlashFile->lpVtbl->Delete(pFlashFile);
            pFlashFile->lpVtbl->Release(pFlashFile);
            pFlashFile = NULL;
        }
        
        //prepare file desc
        memset( &fsFileDesc, 0, sizeof(FSFILEDESC) );
        fsFileDesc.dwSize = sizeof(FSFILEDESC);
        fsFileDesc.dwFlags = FSFD_FILE_NAME|FSFD_BYTES_REQUIRED|FSFD_VMS_COMMENT|FSFD_BOOT_ROM_COMMENT|FSFD_GAME_NAME|FSFD_STATUS|FSFD_COPY/*|FSFD_FILEICON*/;
        strcpy( fsFileDesc.szFileName, name );
        strcpy( fsFileDesc.szVMSComment, pszDescription );
        strcpy( fsFileDesc.szBootROMComment, pszDescription );
        strcpy( fsFileDesc.szGameName, "Doom" );
        fsFileDesc.dwBytesRequired = length;
        fsFileDesc.bStatus = FS_STATUS_DATA_FILE;
        fsFileDesc.bCopy = FS_COPY_ENABLED;
        /*
        fsFileDesc.fsFileIcon...
        */
        
        
        
        //save new one
        if( SUCCEEDED(pFlashDevice->lpVtbl->CreateFlashFile( pFlashDevice, &pFlashFile, &fsFileDesc )))
        {
            if( SUCCEEDED( pFlashFile->lpVtbl->Write( pFlashFile, 0, length, source ) ) )
            {
                pFlashFile->lpVtbl->Flush( pFlashFile );
                bResult = 1;
            }
            else
            {
                pFlashFile->lpVtbl->Delete(pFlashFile);
            }
            pFlashFile->lpVtbl->Release( pFlashFile );
        }
        pFlashDevice->lpVtbl->Release( pFlashDevice );
        
        //change boot type and check door
        ChangeRebootType( TRUE );
        if( g_bDoorOpened ) ResetToFirmware();
    }
    return bResult;
}


struct flashfinddata_t { const char* pszFilename; int nFound; };
BOOL CALLBACK Flash_CallbackFindFiles( IFlashDevice* pFlashDevice, FSFILEID fsFileId, LPCFSFILEDESC lpcfsFileDesc, struct flashfinddata_t* pFindData )
{
    if( stricmp( pFindData->pszFilename, lpcfsFileDesc->szFileName ) == 0 )
    {
        pFindData->nFound = 1;
        return FALSE;
    }
    return TRUE;
}

int Flash_FileExists( const char* pszFilename )
{
    IFlashDevice* pFlashDevice = Flash_CreateDevice();
    if( pFlashDevice )
    {
        struct flashfinddata_t flashfinddata = { pszFilename, 0 };
        pFlashDevice->lpVtbl->FastEnumFlashFiles( pFlashDevice, (LPFSENUMFILESCALLBACK)Flash_CallbackFindFiles, &flashfinddata );
        pFlashDevice->lpVtbl->Release( pFlashDevice );
        return flashfinddata.nFound;
    }
    
    return 0;
    
}


BOOL CALLBACK Flash_CallbackFindFirstWad( IFlashDevice* pFlashDevice, FSFILEID fsFileId, LPCFSFILEDESC lpcfsFileDesc, char* pszResult )
{
    const char* pszExtension = &lpcfsFileDesc->szFileName[strlen(lpcfsFileDesc->szFileName)];
    while( *pszExtension != '.' && pszExtension != lpcfsFileDesc->szFileName ) pszExtension--;
    if( *pszExtension == '.' )
        if( strnicmp( pszExtension, ".wad", 4 ) == 0 )
        {
            strcpy( pszResult, lpcfsFileDesc->szFileName );
            return FALSE;
        }
    return TRUE;
}

void Flash_FindFirstWadFile( char* pszFilename )
{
    IFlashDevice* pFlashDevice = Flash_CreateDevice();
    if( pFlashDevice )
    {
        *pszFilename = '\0';
        pFlashDevice->lpVtbl->FastEnumFlashFiles( pFlashDevice, (LPFSENUMFILESCALLBACK)Flash_CallbackFindFirstWad, pszFilename );
        pFlashDevice->lpVtbl->Release( pFlashDevice );
    }
}


///////////// tonebank stuff //////////////////////////////////



BYTE* GetDataResource(TCHAR *psz, DWORD *pcbData)
{
    HRSRC   hrsrc;
    HGLOBAL hglobal;
    BYTE    *pbRet = NULL;

    // This series of statements is simply the standard Windows sequence for obtaining a 
    // pointer to a memory block that contains the data found in a resource included in the EXE
    hrsrc = FindResource(hInst, psz, RT_RCDATA);
    if (hrsrc == NULL)
        return NULL;

    *pcbData = SizeofResource(hInst, hrsrc);
    if (*pcbData == 0)
        return NULL;

    hglobal = LoadResource(hInst, hrsrc);
    if (hglobal == NULL)
        return NULL;

    return (BYTE*)LockResource(hglobal);
}


BOOL LoadTonebank(TCHAR *tszName, MIDIHDR *pmh)
{
    BYTE *pbTonebank;
    DWORD cbTonebank;

    // Get the data
    pbTonebank = GetDataResource(tszName, &cbTonebank);
    if (pbTonebank == NULL)
        return FALSE;

    // Initialize the MIDIHDR
    pmh->lpData = (char*)pbTonebank;
    pmh->dwBufferLength = cbTonebank;

    return TRUE;
}
