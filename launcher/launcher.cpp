
#include <windows.h>
#include <ddraw.h>
#include <dinput.h>
#include <maplusag.h>
#include <mapledev.h>
#include <ceddcdrm.h>
#include <segagdrm.h>
#include <perstore.h>
#include <platutil.h>
#include <dbt.h>
#include "launcher.h"
#include "resource.h"

//main globals
extern HWND g_hWnd;
extern LPDIRECTDRAW4 g_pDD;
extern LPDIRECTDRAWSURFACE4 g_pDDSPrimary;
extern LPDIRECTDRAWSURFACE4 g_pDDSBack;
extern LPDIRECTINPUT        g_pDI;
extern LPDIRECTINPUTDEVICE  g_pDIDMouse;
extern LPDIRECTINPUTDEVICE2 g_pDIDJoystick;
extern LPDIRECTINPUTDEVICE  g_pDIDKeyboard;

extern DIJOYSTATE g_diJoyState;
extern DIMOUSESTATE g_diMouseState;
extern BYTE g_diKbdState[256];

extern HANDLE g_hRemoveDevice;
extern HANDLE g_hNewDevice;
extern HANDLE g_hGDROM;
extern BOOL g_bDoorOpened;

extern int g_iControllerPort;
extern int g_nControllers;
extern GUID g_guidFlash;

extern BOOL g_b60Hz;

//navigation keys
extern BOOL g_bAccept;
extern BOOL g_bCancel;
extern BOOL g_bUp;
extern BOOL g_bDown;
extern BOOL g_bButtonPressNew;


int PickItem( const char* pszCaption, const char** pszOptions, int nOptions );
void DrawString( int x, int y, const char* pszString, int nMaxWidth = 640, int nMaxHeight = 480 );

void MenuAcceptSoundEffect();
void MenuCancelSoundEffect();
void MenuMoveSoundEffect();


BOOL CreateDisplay();
void DestroyDisplay();
void ClearDisplay();

void DrawStringLarge( int x, int y, const char* pszString, bool bWhite, int nMaxWidth = 640, int nMaxHeight = 480 );

void DisplayMessage( const char* pszCaption, const char* pszMessage );



void mbcopy( TCHAR* ts1, const char* s2 );
int stricmp( const char* s1, const char* s2 );
int strcmpi( const char* s1, const char* s2 );
int strnicmp( const char* s1, const char* s2, size_t size );
int isdigit( int ch );
char* strupr( char* psz );
BOOL Flash_Format( IFlashDevice* pFlashDevice );
IFlashDevice* Flash_CreateDevice();
int Flash_ReadFile( char const* name, byte** buffer );
boolean Flash_WriteFile( char const* name, void* source, int length, const char* pszDescription );
struct flashfinddata_t { const char* pszFilename; int nFound; };
BOOL CALLBACK Flash_CallbackFindFiles( IFlashDevice* pFlashDevice, FSFILEID fsFileId, LPCFSFILEDESC lpcfsFileDesc, struct flashfinddata_t* pFindData );
int Flash_FileExists( const char* pszFilename );
BOOL Update();

















/////////////////////////////////////////////////////////////////////////////////////////

void Do60HzCheck()
{
    //see if we need to offer a 60Hz option
    switch( GetVideoOutputFormat() )
    {
        default:
        case VIDFMT_VGA:
        case VIDFMT_NTSC:
        case VIDFMT_NTSC_RGB:
            return;
        
        case VIDFMT_PAL:
        case VIDFMT_PAL_M:
        case VIDFMT_PAL_N:
        case VIDFMT_PAL_RGB:
        case VIDFMT_PAL_M_RGB:
        case VIDFMT_PAL_N_RGB:
            break;
    }

    char* pszOptions[] = { "50 Hz", "60 Hz", "60 Hz Test" };

    while(1)
    {
        //display refresh rate selection screen
        int iOption = PickItem( "Refresh Rate", (const char**)pszOptions, 3 );
        switch( iOption )
        {
            case 0: return;
            case 1: g_b60Hz = TRUE; ClearDisplay(); DestroyDisplay(); CreateDisplay(); return;
        }

        //show warning
        DisplayMessage( "60 Hz Test Mode", "The screen will now go into 60Hz mode for 5 seconds. If the screen is stable and flicker-free, your television supports 60Hz refresh rate. If the screen is not stable or flicker-free, your television does not support a 60Hz refresh rate." );


        //do 60hz text
        g_b60Hz = TRUE;
        ClearDisplay(); DestroyDisplay(); CreateDisplay(); 

        DWORD dwStart = GetTickCount();
        DWORD dwEnd = GetTickCount() + 5000;

        while(dwEnd > dwStart)
        {
            if(!Update()) return;
        
            DrawStringLarge( 100, 100, "THE SCREEN IS NOW IN 60HZ MODE", FALSE );
            char szBuf[3];  sprintf( szBuf, "%d", 1+(dwEnd-dwStart)/1000 );
            DrawStringLarge( 310, 240, szBuf, TRUE );
            dwStart = GetTickCount();
        }

        g_b60Hz = FALSE;
        ClearDisplay(); DestroyDisplay(); CreateDisplay(); 
    }
}

void MainLoop()
{
    Do60HzCheck();




    //fixme: hang until start btn
    while(Update());
}