
#include <windows.h>
#include <ddraw.h>
#include <dinput.h>
#include <dsound.h>
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
HWND g_hWnd = NULL;
LPDIRECTDRAW4 g_pDD = NULL;
LPDIRECTDRAWSURFACE4 g_pDDSPrimary = NULL;
LPDIRECTDRAWSURFACE4 g_pDDSBack = NULL;
LPDIRECTINPUT        g_pDI = NULL;
LPDIRECTINPUTDEVICE  g_pDIDMouse = NULL;
LPDIRECTINPUTDEVICE2 g_pDIDJoystick = NULL;
LPDIRECTINPUTDEVICE  g_pDIDKeyboard = NULL;
LPDIRECTDRAWPALETTE  g_pDDPal = NULL;
LPDIRECTSOUND	     g_pDS = NULL;


DIJOYSTATE g_diJoyState;
DIMOUSESTATE g_diMouseState;
BYTE g_diKbdState[256];

HANDLE g_hRemoveDevice = NULL;
HANDLE g_hNewDevice = NULL;
HANDLE g_hGDROM = NULL;
BOOL g_bDoorOpened = FALSE;

int g_iControllerPort = 0;
int g_nControllers = 0;
GUID g_guidFlash;

BOOL g_b60Hz = FALSE;

//macros
#define SAFE_RELEASE(p) if(p) { p->Release(); p = NULL; }


//navigation keys
BOOL g_bAccept = FALSE;
BOOL g_bCancel = FALSE;
BOOL g_bUp = FALSE;
BOOL g_bDown = FALSE;
BOOL g_bStart = FALSE;
BOOL g_bButtonPressNew = FALSE;

//sounds
LPDIRECTSOUNDBUFFER g_pDSBMove = NULL;
LPDIRECTSOUNDBUFFER g_pDSBAccept = NULL;
LPDIRECTSOUNDBUFFER g_pDSBCancel = NULL;



BOOL ParseWaveFile(void *pvWaveFile, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pcbWaveSize)
{
    DWORD *pdw, *pdwEnd, dwRiff, dwType, dwLength;
    if (ppWaveHeader) *ppWaveHeader = NULL;
    if (ppbWaveData) *ppbWaveData = NULL;
    if (pcbWaveSize) *pcbWaveSize = 0;
    pdw = (DWORD *)pvWaveFile;
    dwRiff   = *pdw++;
    dwLength = *pdw++;
    dwType   = *pdw++;
    if (dwType != mmioFOURCC('W', 'A', 'V', 'E')) return FALSE;
    if (dwRiff != mmioFOURCC('R', 'I', 'F', 'F')) return FALSE;
    pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);
    while (pdw < pdwEnd)
    {
        dwType = *pdw++;
        dwLength = *pdw++;

        switch (dwType)
        {
        case mmioFOURCC('f', 'm', 't', ' '):
            if (ppWaveHeader && !*ppWaveHeader)
            {
                if (dwLength < sizeof(WAVEFORMAT)) return FALSE;
                *ppWaveHeader = (WAVEFORMATEX *)pdw;
                if ((!ppbWaveData || *ppbWaveData) && (!pcbWaveSize || *pcbWaveSize)) return TRUE;
            }
            break;
        case mmioFOURCC('d', 'a', 't', 'a'):
            if ((ppbWaveData && !*ppbWaveData) || (pcbWaveSize && !*pcbWaveSize))
            {
                if (ppbWaveData) *ppbWaveData = (LPBYTE)pdw;
                if (pcbWaveSize) *pcbWaveSize = dwLength;
                if (!ppWaveHeader || *ppWaveHeader) return TRUE;
            }
            break;
        }
        pdw = (DWORD *)((BYTE *)pdw + ((dwLength+1)&~1));
    }

    return FALSE;
}

BOOL GetWaveResource(LPCTSTR tszName, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pcbWaveSize)
{
    HRSRC hResInfo = FindResource(GetModuleHandle(NULL), tszName, TEXT("WAVE"));   if (hResInfo == NULL) return FALSE;
    HGLOBAL hResData = LoadResource(GetModuleHandle(NULL), hResInfo);   if (hResData == NULL) return FALSE;
    void* pvRes = LockResource(hResData);    if( pvRes == NULL ) return FALSE;
    return (ParseWaveFile(pvRes, ppWaveHeader, ppbWaveData, pcbWaveSize) != NULL);
}

BOOL FillSoundBuffer(IDirectSoundBuffer *pdsb, BYTE *pbWaveData, DWORD dwWaveSize)
{
    LPVOID pMem1, pMem2;  DWORD  dwSize1, dwSize2;
    if (!pdsb || !pbWaveData || !dwWaveSize) return FALSE;
    if( FAILED( pdsb->Lock(0, dwWaveSize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0) ) ) return FALSE;
    memcpy(pMem1, pbWaveData, dwSize1);
    if (dwSize2 != 0) memcpy(pMem2, pbWaveData+dwSize1, dwSize2);
    pdsb->Unlock(pMem1, dwSize1, pMem2, dwSize2);
    return TRUE;
}

LPDIRECTSOUNDBUFFER LoadSoundBuffer(LPCTSTR tszName)
{
    LPDIRECTSOUNDBUFFER pdsb = NULL;
    DSBUFFERDESC dsbd = {0};
    BYTE *pbWaveData;

    if( GetWaveResource(tszName, &dsbd.lpwfxFormat, &pbWaveData, &dsbd.dwBufferBytes))
    {
        dsbd.dwSize = sizeof(dsbd);
        dsbd.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLDEFAULT | DSBCAPS_GETCURRENTPOSITION2;

        if (SUCCEEDED(g_pDS->CreateSoundBuffer(&dsbd, &pdsb, NULL)))
        {
            if (!FillSoundBuffer(pdsb, pbWaveData, dsbd.dwBufferBytes)) SAFE_RELEASE( pdsb );
        }
        else
            pdsb = NULL;
    }

    return pdsb;
}





unsigned char DoomPalette[768] = { /*r,g,b,*/
	0x00,0x00,0x00, 0x1f,0x17,0x0b, 0x17,0x0f,0x07, 0x4b,0x4b,0x4b, 0xff,0xff,0xff, 0x1b,0x1b,0x1b, 0x13,0x13,0x13, 0x0b,0x0b,0x0b, 
	0x07,0x07,0x07, 0x2f,0x37,0x1f, 0x23,0x2b,0x0f, 0x17,0x1f,0x07, 0x0f,0x17,0x00, 0x4f,0x3b,0x2b, 0x47,0x33,0x23, 0x3f,0x2b,0x1b, 
	0xff,0xb7,0xb7, 0xf7,0xab,0xab, 0xf3,0xa3,0xa3, 0xeb,0x97,0x97, 0xe7,0x8f,0x8f, 0xdf,0x87,0x87, 0xdb,0x7b,0x7b, 0xd3,0x73,0x73, 
	0xcb,0x6b,0x6b, 0xc7,0x63,0x63, 0xbf,0x5b,0x5b, 0xbb,0x57,0x57, 0xb3,0x4f,0x4f, 0xaf,0x47,0x47, 0xa7,0x3f,0x3f, 0xa3,0x3b,0x3b, 
	0x9b,0x33,0x33, 0x97,0x2f,0x2f, 0x8f,0x2b,0x2b, 0x8b,0x23,0x23, 0x83,0x1f,0x1f, 0x7f,0x1b,0x1b, 0x77,0x17,0x17, 0x73,0x13,0x13, 
	0x6b,0x0f,0x0f, 0x67,0x0b,0x0b, 0x5f,0x07,0x07, 0x5b,0x07,0x07, 0x53,0x07,0x07, 0x4f,0x00,0x00, 0x47,0x00,0x00, 0x43,0x00,0x00, 
	0xff,0xeb,0xdf, 0xff,0xe3,0xd3, 0xff,0xdb,0xc7, 0xff,0xd3,0xbb, 0xff,0xcf,0xb3, 0xff,0xc7,0xa7, 0xff,0xbf,0x9b, 0xff,0xbb,0x93, 
	0xff,0xb3,0x83, 0xf7,0xab,0x7b, 0xef,0xa3,0x73, 0xe7,0x9b,0x6b, 0xdf,0x93,0x63, 0xd7,0x8b,0x5b, 0xcf,0x83,0x53, 0xcb,0x7f,0x4f, 
	0xbf,0x7b,0x4b, 0xb3,0x73,0x47, 0xab,0x6f,0x43, 0xa3,0x6b,0x3f, 0x9b,0x63,0x3b, 0x8f,0x5f,0x37, 0x87,0x57,0x33, 0x7f,0x53,0x2f, 
	0x77,0x4f,0x2b, 0x6b,0x47,0x27, 0x5f,0x43,0x23, 0x53,0x3f,0x1f, 0x4b,0x37,0x1b, 0x3f,0x2f,0x17, 0x33,0x2b,0x13, 0x2b,0x23,0x0f, 
	0xef,0xef,0xef, 0xe7,0xe7,0xe7, 0xdf,0xdf,0xdf, 0xdb,0xdb,0xdb, 0xd3,0xd3,0xd3, 0xcb,0xcb,0xcb, 0xc7,0xc7,0xc7, 0xbf,0xbf,0xbf, 
	0xb7,0xb7,0xb7, 0xb3,0xb3,0xb3, 0xab,0xab,0xab, 0xa7,0xa7,0xa7, 0x9f,0x9f,0x9f, 0x97,0x97,0x97, 0x93,0x93,0x93, 0x8b,0x8b,0x8b, 
	0x83,0x83,0x83, 0x7f,0x7f,0x7f, 0x77,0x77,0x77, 0x6f,0x6f,0x6f, 0x6b,0x6b,0x6b, 0x63,0x63,0x63, 0x5b,0x5b,0x5b, 0x57,0x57,0x57, 
	0x4f,0x4f,0x4f, 0x47,0x47,0x47, 0x43,0x43,0x43, 0x3b,0x3b,0x3b, 0x37,0x37,0x37, 0x2f,0x2f,0x2f, 0x27,0x27,0x27, 0x23,0x23,0x23, 
	0x77,0xff,0x6f, 0x6f,0xef,0x67, 0x67,0xdf,0x5f, 0x5f,0xcf,0x57, 0x5b,0xbf,0x4f, 0x53,0xaf,0x47, 0x4b,0x9f,0x3f, 0x43,0x93,0x37, 
	0x3f,0x83,0x2f, 0x37,0x73,0x2b, 0x2f,0x63,0x23, 0x27,0x53,0x1b, 0x1f,0x43,0x17, 0x17,0x33,0x0f, 0x13,0x23,0x0b, 0x0b,0x17,0x07, 
	0xbf,0xa7,0x8f, 0xb7,0x9f,0x87, 0xaf,0x97,0x7f, 0xa7,0x8f,0x77, 0x9f,0x87,0x6f, 0x9b,0x7f,0x6b, 0x93,0x7b,0x63, 0x8b,0x73,0x5b, 
	0x83,0x6b,0x57, 0x7b,0x63,0x4f, 0x77,0x5f,0x4b, 0x6f,0x57,0x43, 0x67,0x53,0x3f, 0x5f,0x4b,0x37, 0x57,0x43,0x33, 0x53,0x3f,0x2f, 
	0x9f,0x83,0x63, 0x8f,0x77,0x53, 0x83,0x6b,0x4b, 0x77,0x5f,0x3f, 0x67,0x53,0x33, 0x5b,0x47,0x2b, 0x4f,0x3b,0x23, 0x43,0x33,0x1b, 
	0x7b,0x7f,0x63, 0x6f,0x73,0x57, 0x67,0x6b,0x4f, 0x5b,0x63,0x47, 0x53,0x57,0x3b, 0x47,0x4f,0x33, 0x3f,0x47,0x2b, 0x37,0x3f,0x27, 
	0xff,0xff,0x73, 0xeb,0xdb,0x57, 0xd7,0xbb,0x43, 0xc3,0x9b,0x2f, 0xaf,0x7b,0x1f, 0x9b,0x5b,0x13, 0x87,0x43,0x07, 0x73,0x2b,0x00, 
	0xff,0xff,0xff, 0xff,0xdb,0xdb, 0xff,0xbb,0xbb, 0xff,0x9b,0x9b, 0xff,0x7b,0x7b, 0xff,0x5f,0x5f, 0xff,0x3f,0x3f, 0xff,0x1f,0x1f, 
	0xff,0x00,0x00, 0xef,0x00,0x00, 0xe3,0x00,0x00, 0xd7,0x00,0x00, 0xcb,0x00,0x00, 0xbf,0x00,0x00, 0xb3,0x00,0x00, 0xa7,0x00,0x00, 
	0x9b,0x00,0x00, 0x8b,0x00,0x00, 0x7f,0x00,0x00, 0x73,0x00,0x00, 0x67,0x00,0x00, 0x5b,0x00,0x00, 0x4f,0x00,0x00, 0x43,0x00,0x00, 
	0xe7,0xe7,0xff, 0xc7,0xc7,0xff, 0xab,0xab,0xff, 0x8f,0x8f,0xff, 0x73,0x73,0xff, 0x53,0x53,0xff, 0x37,0x37,0xff, 0x1b,0x1b,0xff, 
	0x00,0x00,0xff, 0x00,0x00,0xe3, 0x00,0x00,0xcb, 0x00,0x00,0xb3, 0x00,0x00,0x9b, 0x00,0x00,0x83, 0x00,0x00,0x6b, 0x00,0x00,0x53, 
	0xff,0xff,0xff, 0xff,0xeb,0xdb, 0xff,0xd7,0xbb, 0xff,0xc7,0x9b, 0xff,0xb3,0x7b, 0xff,0xa3,0x5b, 0xff,0x8f,0x3b, 0xff,0x7f,0x1b, 
	0xf3,0x73,0x17, 0xeb,0x6f,0x0f, 0xdf,0x67,0x0f, 0xd7,0x5f,0x0b, 0xcb,0x57,0x07, 0xc3,0x4f,0x00, 0xb7,0x47,0x00, 0xaf,0x43,0x00, 
	0xff,0xff,0xff, 0xff,0xff,0xd7, 0xff,0xff,0xb3, 0xff,0xff,0x8f, 0xff,0xff,0x6b, 0xff,0xff,0x47, 0xff,0xff,0x23, 0xff,0xff,0x00, 
	0xa7,0x3f,0x00, 0x9f,0x37,0x00, 0x93,0x2f,0x00, 0x87,0x23,0x00, 0x4f,0x3b,0x27, 0x43,0x2f,0x1b, 0x37,0x23,0x13, 0x2f,0x1b,0x0b, 
	0x00,0x00,0x53, 0x00,0x00,0x47, 0x00,0x00,0x3b, 0x00,0x00,0x2f, 0x00,0x00,0x23, 0x00,0x00,0x17, 0x00,0x00,0x0b, 0x00,0xff,0xff, 
	0xff,0x9f,0x43, 0xff,0xe7,0x4b, 0xff,0x7b,0xff, 0xff,0x00,0xff, 0xcf,0x00,0xcf, 0x9f,0x00,0x9b, 0x6f,0x00,0x6b, 0xa7,0x6b,0x6b, 
};



LPDIRECTDRAWSURFACE4 LoadBitmapToDDS( LPTSTR pszBitmap )
{
    //load the bitmap
    HBITMAP hBitmap = (HBITMAP)LoadImage( GetModuleHandle(NULL), pszBitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR );
    if( hBitmap == NULL ) return NULL;

    //get the bitmap information
    BITMAP Bitmap;
    GetObject( hBitmap, sizeof(BITMAP), &Bitmap );

	//prepare a surface description structure for this texture
    DDSURFACEDESC2 ddsd;
	memset( &ddsd, 0, sizeof(DDSURFACEDESC2) );
    ddsd.dwSize = sizeof(DDSURFACEDESC2);
	if( FAILED( g_pDDSBack->GetSurfaceDesc( &ddsd ) ) ) { DeleteObject( hBitmap ); return NULL; }
    ddsd.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth = Bitmap.bmWidth;
    ddsd.dwHeight = Bitmap.bmHeight;

	//create a surface
    LPDIRECTDRAWSURFACE4 pDDS = NULL;
    if( FAILED( g_pDD->CreateSurface( &ddsd, &pDDS, NULL ) ) ) { DeleteObject( hBitmap ); return NULL; }

	//select the bitmap into an offscreen device context
    HDC hDCBitmap = CreateCompatibleDC(NULL);
    SelectObject( hDCBitmap, hBitmap );

	//get the surface's device context
	HDC hDCSurface = NULL;
    if( FAILED( pDDS->GetDC( &hDCSurface ) ) ) { SAFE_RELEASE(pDDS); DeleteObject( hBitmap ); return NULL; }

    //copy the bitmap onto the surface
    BitBlt( hDCSurface, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, hDCBitmap, 0, 0, SRCCOPY );

    //clean up and return
    pDDS->ReleaseDC( hDCSurface );
    DeleteDC( hDCBitmap );
    DeleteObject( hBitmap );

    return pDDS;
}








LPDIRECTDRAWSURFACE4 LoadBitmapToPalettisedDDS(LPTSTR tszBitmap)
{
    HBITMAP             hbitmap;    // Bitmap handle
    BITMAP              bitmap;     // Bitmap information
    DDSURFACEDESC2       ddsd;       // Surface Descriptor
    LPDIRECTDRAWSURFACE4 pddsSystemMemory;
    LPDIRECTDRAWSURFACE4 pddsVideoMemory;

    // Load the bitmap from the resource file
    hbitmap = (HBITMAP)LoadImage (GetModuleHandle(NULL), tszBitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    if (hbitmap== NULL) return NULL;

    // Get the width, height and other info about the bitmap.
    GetObject (hbitmap, sizeof(BITMAP), &bitmap);

    // Create the palettized system memory ddraw surface.  Note - this assume 8bpp; use
    // "DDPF_PALETTEINDEXED4" for 4bpp surface
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize         = sizeof(DDSURFACEDESC2);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth        = bitmap.bmWidth;
    ddsd.dwHeight       = bitmap.bmHeight;
    ddsd.ddpfPixelFormat.dwSize        = sizeof(DDPIXELFORMAT);
    ddsd.ddpfPixelFormat.dwFlags       = DDPF_RGB | DDPF_PALETTEINDEXED8;
    ddsd.ddpfPixelFormat.dwRGBBitCount = 8;

    if( FAILED( g_pDD->CreateSurface(&ddsd, &pddsSystemMemory, NULL) ) ) return NULL;

    // Attach the palette to the texture surface
    if( FAILED( pddsSystemMemory->SetPalette(g_pDDPal) ) ) return NULL;

    // Create an offscreen DC for the bitmap
    HDC hdcSrc = CreateCompatibleDC(NULL);
    HDC hdcDst;
    if (!hdcSrc) return NULL;

    SelectObject(hdcSrc, hbitmap);

    // Get a DC on the texture surface
    if( FAILED( pddsSystemMemory->GetDC(&hdcDst) ) ) return NULL;

    // Copy the bitmap into the texture
    if (!BitBlt(hdcDst, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcSrc, 0, 0, SRCCOPY ) )  return NULL;

    // Release the DC
    pddsSystemMemory->ReleaseDC(hdcDst);


    //create a double-sized software one
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    if( FAILED( pddsSystemMemory->GetSurfaceDesc(&ddsd) ) ) return NULL;

    ddsd.dwWidth *= 2;  ddsd.dwHeight *= 2;

    LPDIRECTDRAWSURFACE4 pDDSSoftware2;
    if( FAILED( g_pDD->CreateSurface(&ddsd, &pDDSSoftware2, NULL) ) ) return NULL;
    if( FAILED( pDDSSoftware2->SetPalette(g_pDDPal) ) ) return NULL;
    pDDSSoftware2->Blt(NULL, pddsSystemMemory, NULL, 0, NULL);

    pddsSystemMemory->Release();

    // Create the (twiddled) video memory surface that we will load the palettized surface into.
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    if( FAILED( pDDSSoftware2->GetSurfaceDesc(&ddsd) ) ) return NULL;

    ddsd.ddsCaps.dwCaps &= ~DDSCAPS_SYSTEMMEMORY;   // Don't specify a memory location
    ddsd.ddsCaps.dwCaps |= DDSCAPS_ALLOCONLOAD;

    if( FAILED( g_pDD->CreateSurface(&ddsd, &pddsVideoMemory, NULL) ) ) return NULL;

    // Attach the palette to the device memory surface
    if( FAILED( pddsVideoMemory->SetPalette(g_pDDPal) ) ) return NULL;

    // BitBlt from the system memory surface to the video memory surface - this will twiddle the
    // bitmap, which is required for hardware-memory palettized surfaces (this is a requirement of
    // the hardware).
    pddsVideoMemory->Blt(NULL, pDDSSoftware2, NULL, 0, NULL);

    // No longer need the system memory surface
    pDDSSoftware2->Release();

    //set transparency colour
    DDCOLORKEY ddck;
    ddck.dwColorSpaceLowValue = ddck.dwColorSpaceHighValue = 247; //doom's transparent colour
    pddsVideoMemory->SetColorKey( DDCKEY_SRCBLT, &ddck );

    return pddsVideoMemory;
}


















int g_nSmallCharWidths[] = {
    6,4,7,7,7,9,8,4,7,7,7,5,4,6,4,7,8,
    5,8,8,7,7,8,8,8,8,4,4,5,5,5,8,9,8,
    8,8,8,8,8,8,8,4,8,8,8,9,8,8,8,8,8,
    7,8,8,7,9,9,8,7,5,7,5,7,};


LPDIRECTDRAWSURFACE4 g_pDDSBackground = NULL;
LPDIRECTDRAWSURFACE4 g_pDDSDoom = NULL;
LPDIRECTDRAWSURFACE4 g_pDDSSkull[2] = { NULL, NULL };
LPDIRECTDRAWSURFACE4 g_pDDSFontSmall = NULL;
LPDIRECTDRAWSURFACE4 g_pDDSFontRed = NULL;
LPDIRECTDRAWSURFACE4 g_pDDSFontWhite = NULL;

int g_nLargeCharWidths[] = {
    12,6, 10,00,00,13,00,00,
    7, 7, 0, 0, 4, 6, 4, 13,
    11,7, 11,11,11,11,11,11,
    11,11,5, 4, 00,7, 00,13,
    00,15,15,14,15,14,12,16,
    15,8, 11,16,11,17,16,16,
    14,16,15,15,12,16,16,16,
    15,16,16,00,13,00,00,};



void LoadTextures()
{
    g_pDDSBackground = LoadBitmapToDDS( TEXT("INTERPIC") );    
    g_pDDSDoom = LoadBitmapToPalettisedDDS( TEXT("M_DOOM") );
    g_pDDSSkull[0] = LoadBitmapToPalettisedDDS( TEXT("M_SKULL1") );
    g_pDDSSkull[1] = LoadBitmapToPalettisedDDS( TEXT("M_SKULL2") );
    g_pDDSFontSmall = LoadBitmapToPalettisedDDS( MAKEINTRESOURCE(IDB_SMALLFONT) );
    g_pDDSFontRed = LoadBitmapToPalettisedDDS( MAKEINTRESOURCE(IDB_REDFONT) );
    g_pDDSFontWhite = LoadBitmapToPalettisedDDS( MAKEINTRESOURCE(IDB_WHITEFONT) );
}

void FreeTextures()
{
    SAFE_RELEASE(g_pDDSDoom);
    SAFE_RELEASE(g_pDDSBackground);
    SAFE_RELEASE(g_pDDSFontSmall);
}


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
    FSDEVICEDESC devdesc;
    int i;
    BYTE coloricon[512] = {
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
        0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF
    };
    BYTE monoicon[128] = {
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,
        0xF0,0xFF,0xFF,0x0F,0xF0,0xFF,0xFF,0x0F,0xF0,0xFF,0xFF,0x0F,0xF0,0xFF,0xFF,0x0F,
        0xF0,0xF0,0x0F,0x0F,0xF0,0xF0,0x0F,0x0F,0xF0,0xF0,0x0F,0x0F,0xF0,0xF0,0x0F,0x0F,
        0xF0,0xF0,0x0F,0x0F,0xF0,0xF0,0x0F,0x0F,0xF0,0xF0,0x0F,0x0F,0xF0,0xF0,0x0F,0x0F,
        0xF0,0xFF,0xFF,0x0F,0xF0,0xFF,0xFF,0x0F,0xF0,0xFF,0xFF,0x0F,0xF0,0xFF,0xFF,0x0F,
        0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
    };
        
        
    memset (&devdesc, 0, sizeof(devdesc));
    devdesc.dwSize = sizeof(devdesc);
    devdesc.dwFlags = FSDD_COLOR_VMS | FSDD_VOLUME_ICON;
    devdesc.colorVMS = MAKE_FSARGB8(0xff, 0x80, 0x00, 0x80);
    
    devdesc.fsvolumeicon.fUsePredefinedIcon = FALSE;
    memcpy (devdesc.fsvolumeicon.imagedata.pixelsMonochrome, monoicon, 128);
    devdesc.fsvolumeicon.imagedata.fHasColor = TRUE;
    
    for( i = 0; i < 15; i++ ) devdesc.fsvolumeicon.imagedata.palette[i] = MAKE_FSARGB4(0xff, 128 + i*8, 0, 0);
    
    memcpy (devdesc.fsvolumeicon.imagedata.pixelsColor, coloricon, 512);
    
    return SUCCEEDED( pFlashDevice->DoFormat(&devdesc) );
}


IFlashDevice* Flash_CreateDevice()
{
    GUID nullguid;
    IUnknown *pIUnknown = NULL;
    IFlashDevice* pFlashDevice = NULL;
    
    memset( &nullguid, 0, sizeof(GUID) );
    if( memcmp( &g_guidFlash, &nullguid, sizeof(GUID) ) == 0 ) return NULL;
    
    if( FAILED( MapleCreateDevice(&g_guidFlash, &pIUnknown) )) return NULL;
    
    pIUnknown->QueryInterface( IID_IFlashDevice, (void**)&pFlashDevice);
    SAFE_RELEASE( pIUnknown );
    
    return pFlashDevice;
}


int Flash_ReadFile( char const* name, byte** buffer )
{
    int nSize = 0;
    IFlashDevice* pFlashDevice = Flash_CreateDevice();
    IFlashFile* pFlashFile = NULL;
    HRESULT hResult;
    if( pFlashDevice != NULL )
    {
        ChangeRebootType( FALSE );
        
        if( SUCCEEDED(hResult = pFlashDevice->OpenFlashFileByName( &pFlashFile, (LPSTR)name )) )
        {
            FSFILEDESC fsFileDesc;
            memset( &fsFileDesc, 0, sizeof(FSFILEDESC) );
            fsFileDesc.dwSize = sizeof(FSFILEDESC);
            fsFileDesc.dwFlags = FSFD_TOTAL_BYTES;
            
            if( SUCCEEDED(hResult = pFlashFile->GetFileDesc( &fsFileDesc ) ) )
            {
                byte* buf = (byte*)malloc( fsFileDesc.dwTotalBytes );
                if( buf )
                {
                    if( SUCCEEDED(hResult = pFlashFile->Read( 0, fsFileDesc.dwTotalBytes, buf ) ) )
                    {
                        nSize = fsFileDesc.dwTotalBytes;
                        *buffer = buf;
                    }
                    else
                    {
                        free( buf );
                    }
                }
            }
            SAFE_RELEASE( pFlashFile );
        }
        SAFE_RELEASE( pFlashDevice );
        
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
        if( FAILED(pFlashDevice->CheckFormat()))
        {
            if( !Flash_Format(pFlashDevice))
            {
                SAFE_RELEASE( pFlashDevice  );
                return 0;
            }
        }
        
        //delete existing file
        if( SUCCEEDED(pFlashDevice->OpenFlashFileByName( &pFlashFile, (LPSTR)name )))
        {
            pFlashFile->Delete();
            SAFE_RELEASE( pFlashFile );
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
        if( SUCCEEDED(pFlashDevice->CreateFlashFile( &pFlashFile, &fsFileDesc )))
        {
            if( SUCCEEDED( pFlashFile->Write( 0, length, (unsigned char*)source ) ) )
            {
                pFlashFile->Flush();
                bResult = 1;
            }
            else
            {
                pFlashFile->Delete();
            }
            SAFE_RELEASE( pFlashFile );
        }
        SAFE_RELEASE( pFlashDevice );
        
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
        pFlashDevice->FastEnumFlashFiles( (LPFSENUMFILESCALLBACK)Flash_CallbackFindFiles, &flashfinddata );
        SAFE_RELEASE( pFlashDevice );
        return flashfinddata.nFound;
    }
    
    return 0;
    
}



BOOL CALLBACK Controller_Enum( LPCDIDEVICEINSTANCE pdidi, void* pV )
{
    memcpy( pV, &pdidi->guidInstance, sizeof(pdidi->guidInstance) );
    return FALSE;
}

BOOL CALLBACK MapleEnumProc(LPCMAPLEDEVICEINSTANCE pmdi, LPVOID pvContext)
{
    if( pmdi->dwPort == (DWORD)g_iControllerPort )
    {
        memcpy( pvContext, &pmdi->guidDevice, sizeof(GUID) );
        return FALSE;
    }

    return TRUE;
}

void EnumControllers()
{
    GUID guid;

    //reset stuff
    g_iControllerPort = 0xFF;   
    g_nControllers = 0;
    memset( &g_guidFlash, 0, sizeof(GUID) );   

    memset( &g_diJoyState, 0, sizeof(g_diJoyState) );
    memset( &g_diMouseState, 0, sizeof(g_diMouseState) );
    memset( g_diKbdState, 0, 256 );

    //create mouse
    g_pDI->EnumDevices( DIDEVTYPE_MOUSE, Controller_Enum, &guid, 0 );
    if( SUCCEEDED( g_pDI->CreateDevice( guid, &g_pDIDMouse, NULL ) ) ) g_nControllers++;

    //create joystick
    LPDIRECTINPUTDEVICE pDIDJoy = NULL;
    g_pDI->EnumDevices( DIDEVTYPE_JOYSTICK, Controller_Enum, &guid, 0 );
    if( SUCCEEDED( g_pDI->CreateDevice( guid, &pDIDJoy, NULL ) ) )
    {
        if( SUCCEEDED( pDIDJoy->QueryInterface( IID_IDirectInputDevice2,(void**)&g_pDIDJoystick ) ) ) g_nControllers++;
        SAFE_RELEASE( pDIDJoy );
    }
    
    //create keyboard
    g_pDI->EnumDevices( DIDEVTYPE_KEYBOARD, Controller_Enum, &guid, 0 );
    if( SUCCEEDED( g_pDI->CreateDevice( guid, &g_pDIDKeyboard, NULL ) ) ) g_nControllers++;

    //init mouse
    if( g_pDIDMouse )  
    {
        g_pDIDMouse->SetDataFormat( &c_dfDIMouse );
        g_pDIDMouse->SetCooperativeLevel( g_hWnd, DISCL_EXCLUSIVE|DISCL_FOREGROUND );
        g_pDIDMouse->Acquire();
    }

    //init keyboard
    if( g_pDIDKeyboard )
    {
        g_pDIDKeyboard->SetDataFormat( &c_dfDIKeyboard );
        g_pDIDKeyboard->SetCooperativeLevel( g_hWnd, DISCL_EXCLUSIVE|DISCL_FOREGROUND );
        g_pDIDKeyboard->Acquire();
    }
    
    //init joystick
    if( g_pDIDJoystick )
    {
        g_pDIDJoystick->SetDataFormat( &c_dfDIJoystick);
        g_pDIDJoystick->SetCooperativeLevel( g_hWnd, DISCL_EXCLUSIVE|DISCL_FOREGROUND );
        
        DIPROPRANGE diprg; 
        diprg.diph.dwSize       = sizeof(diprg); 
        diprg.diph.dwHeaderSize = sizeof(diprg.diph); 
        diprg.diph.dwObj        = DIJOFS_X; 
        diprg.diph.dwHow        = DIPH_BYOFFSET; 
        diprg.lMin              = -1000; 
        diprg.lMax              = +1000; 
        g_pDIDJoystick->SetProperty( DIPROP_RANGE, &diprg.diph );
        diprg.diph.dwObj        = DIJOFS_Y; 
        g_pDIDJoystick->SetProperty( DIPROP_RANGE, &diprg.diph );
        
        DIPROPDWORD dipdw;
        dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
        dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
        dipdw.diph.dwHow        = DIPH_BYOFFSET;
        dipdw.dwData            = 1500;
        dipdw.diph.dwObj        = DIJOFS_X;
        g_pDIDJoystick->SetProperty( DIPROP_DEADZONE, &dipdw.diph );
        dipdw.dwData            = 1500;
        dipdw.diph.dwObj         = DIJOFS_Y;
        g_pDIDJoystick->SetProperty( DIPROP_DEADZONE, &dipdw.diph );
        
        g_pDIDJoystick->Acquire();

        //get port number
        dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
        dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        dipdw.diph.dwObj = 0;
        dipdw.diph.dwHow = DIPH_DEVICE;
        if( SUCCEEDED( g_pDIDJoystick->GetProperty( DIPROP_PORTNUMBER, &dipdw.diph ) ) )
        {
            g_iControllerPort = dipdw.dwData;
            MapleEnumerateDevices( MDT_STORAGE, MapleEnumProc, &g_guidFlash, 0 );
        }
    }
    

    //clear the device events
    WaitForSingleObject(g_hNewDevice, 0);
    WaitForSingleObject(g_hRemoveDevice, 0);

}




//message processing function
LRESULT CALLBACK WndProc_MainWnd( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch( uMsg )
    {
        case WM_DEVICECHANGE:
            if( wParam == DBT_DEVICEREMOVECOMPLETE )
            {
                OutputDebugString(TEXT("GD-ROM drive door has been opened.\r\n"));
                g_bDoorOpened = TRUE;
            }
            break;
    }

    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//change display mode
BOOL CreateDisplay()
{
    //change mode
    if( g_b60Hz )
        g_pDD->SetDisplayMode( 640, 480, 16, 30, 0 );
    else
        g_pDD->SetDisplayMode( 640, 480, 16, 0, 0 );

	//prepare surface description structure
    DDSURFACEDESC2 ddsd;
	memset( &ddsd, 0, sizeof(DDSURFACEDESC2) );
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS|DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE|DDSCAPS_FLIP|DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;

	//create the primary surface
    if( FAILED( g_pDD->CreateSurface( &ddsd, &g_pDDSPrimary, NULL ) ) ) return FALSE;

	//get a pointer to the back buffer
    ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
    if( FAILED( g_pDDSPrimary->GetAttachedSurface( &ddsd.ddsCaps, &g_pDDSBack ) ) ) return FALSE;

    return TRUE;
}

void DestroyDisplay()
{
    SAFE_RELEASE( g_pDDSBack );
    SAFE_RELEASE( g_pDDSPrimary );
}

void ClearDisplay()
{
    //clear the back buffer and flip
    DDBLTFX ddbltfx;
    ddbltfx.dwFillColor = 0;
    ddbltfx.dwSize = sizeof(DDBLTFX);
    g_pDDSBack->Blt( NULL, NULL, NULL, DDBLT_COLORFILL, &ddbltfx );
    g_pDDSPrimary->Flip( NULL, DDFLIP_WAIT );

    while( g_pDDSBack->GetFlipStatus(DDGFS_ISFLIPDONE) == DDERR_WASSTILLDRAWING );
}



//init function
BOOL InitApplication()
{
	LPDIRECTDRAW pDD = NULL;

    HINSTANCE hInstance = GetModuleHandle(NULL);

    //register window class
    WNDCLASS wc = { 0, WndProc_MainWnd, 0, 0, hInstance, NULL, NULL, NULL, NULL, TEXT("WndClass_MainWnd") };
    RegisterClass( &wc );

    //create window
    if( (g_hWnd = CreateWindow( wc.lpszClassName, NULL, WS_VISIBLE|WS_POPUP, 0, 0, 640, 480, NULL, NULL, hInstance, NULL ) ) == NULL ) return 0;
    UpdateWindow( g_hWnd );

	//create the DirectDraw4 device
    if( FAILED( DirectDrawCreate( NULL, &pDD, NULL ) ) ) return FALSE;
	if( FAILED( pDD->QueryInterface( IID_IDirectDraw4, (void**)&g_pDD ) ) ) { SAFE_RELEASE(pDD); return FALSE; }
	SAFE_RELEASE(pDD);

    //set the cooperative level
    g_pDD->SetCooperativeLevel( g_hWnd, DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN );

    //change display mode
    if( !CreateDisplay() ) return FALSE;
    ClearDisplay();

    //generate the palette
    PALETTEENTRY Pal[256];
    unsigned char* pTmp = DoomPalette;
    for( int i = 0; i < 256; i++ )
    {
        Pal[i].peRed = *pTmp++;
        Pal[i].peGreen = *pTmp++;
        Pal[i].peBlue = *pTmp++;

        if( i == 247 )
        {
            Pal[i].peRed = 0;
            Pal[i].peGreen = 0;
            Pal[i].peBlue = 0;
        }

    }

    //create the palette
    if( FAILED( g_pDD->CreatePalette( DDPCAPS_8BIT|DDPCAPS_ALLOW256, Pal, &g_pDDPal, NULL ) ) ) return FALSE;

    //fire up DirectInput
    if( FAILED( DirectInputCreate( hInstance, DIRECTINPUT_VERSION, &g_pDI, NULL ) ) ) return FALSE;

    //create events
    g_hNewDevice = CreateEvent(NULL, FALSE, FALSE, TEXT("MAPLE_NEW_DEVICE"));
    g_hRemoveDevice = CreateEvent(NULL, FALSE, FALSE, TEXT("MAPLE_DEVICE_REMOVED"));

    //enumerate controllers
    EnumControllers();

    //create a handle to the GD-ROM
    g_hGDROM = CreateFile(TEXT("\\Device\\CDROM0"), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL );
    if (g_hGDROM == INVALID_HANDLE_VALUE) return 0;

    //load textures
    LoadTextures();

    //initialise the sound
    if( FAILED( DirectSoundCreate( NULL, &g_pDS, NULL ) ) ) return FALSE;
    g_pDS->SetCooperativeLevel( g_hWnd, DSSCL_NORMAL );

    //load sounds
    g_pDSBMove = LoadSoundBuffer( MAKEINTRESOURCE(IDR_DSSWTCHN) );
    g_pDSBAccept = LoadSoundBuffer( MAKEINTRESOURCE(IDR_DSPISTOL) );
    g_pDSBCancel = LoadSoundBuffer( MAKEINTRESOURCE(IDR_DSSWTCHX) );

    return TRUE;
}

void DoneControllers()
{
    SAFE_RELEASE( g_pDIDMouse );
    SAFE_RELEASE( g_pDIDKeyboard );
    SAFE_RELEASE( g_pDIDJoystick );
}

//shutdown function
void DoneApplication()
{
    DoneControllers();
    FreeTextures();
    if( g_hNewDevice  )   CloseHandle( g_hNewDevice );      g_hNewDevice = NULL;
    if( g_hRemoveDevice ) CloseHandle( g_hRemoveDevice );   g_hRemoveDevice = NULL;
    if( g_hGDROM )        CloseHandle( g_hGDROM );          g_hGDROM = NULL;
    SAFE_RELEASE( g_pDSBMove );
    SAFE_RELEASE( g_pDSBAccept );
    SAFE_RELEASE( g_pDSBCancel );
    SAFE_RELEASE( g_pDS );
    SAFE_RELEASE( g_pDDPal );
    DestroyDisplay();
    SAFE_RELEASE( g_pDD );
    DestroyWindow( g_hWnd ); g_hWnd = NULL;
}

void UpdateControls()
{
    //check for new devices
    BOOL bRemove = (WaitForSingleObject( g_hRemoveDevice, 0) != WAIT_TIMEOUT); //we must call both so they get reset
    if( WaitForSingleObject( g_hNewDevice, 0) != WAIT_TIMEOUT || bRemove )
    {
        DoneControllers();
        EnumControllers();
    }

    //poll the controllers
    if( g_pDIDJoystick ) { g_pDIDJoystick->Poll();  g_pDIDJoystick->GetDeviceState( sizeof(DIJOYSTATE), &g_diJoyState ); }
    if( g_pDIDMouse )    g_pDIDMouse->GetDeviceState( sizeof(DIMOUSESTATE), &g_diMouseState );
    if( g_pDIDKeyboard ) g_pDIDKeyboard->GetDeviceState( 256, g_diKbdState );

    //update controllers
    g_bAccept = ( g_diKbdState[DIK_RETURN] & 0x80 )  || g_diJoyState.rgbButtons[1];//A
    g_bCancel = ( g_diKbdState[DIK_ESCAPE] & 0x80 )  || g_diJoyState.rgbButtons[0];//B
    g_bUp =     ( g_diKbdState[DIK_UP] & 0x80 )      || g_diJoyState.lY < 0 || g_diJoyState.rgbButtons[3];//DIGITAL UP
    g_bDown =   ( g_diKbdState[DIK_DOWN] & 0x80 )    || g_diJoyState.lY > 0 || g_diJoyState.rgbButtons[4];//DIGITAL DOWN
    g_bStart =  g_diJoyState.rgbButtons[2];//Start


    int nNewPress = 0;
    if( g_bAccept ) nNewPress++;
    if( g_bCancel ) nNewPress++;
    if( g_bUp ) nNewPress++;
    if( g_bDown ) nNewPress++;
    if( g_bStart ) nNewPress++;

    static int s_nOldPress = 0;
    g_bButtonPressNew = (nNewPress!=s_nOldPress);
    s_nOldPress = nNewPress;
}




int StringWidth( const char* pszString )
{
    int nWidth = 0;
    int nMaxWidth = 0;
    while( *pszString )
    {
        char ch = toupper(*pszString++);
        if( ch >= 32 && ch <= 95 )
            nWidth += g_nSmallCharWidths[ch-32];
        else
            if( ch == '\n' )
            {
                nWidth = 0;
            }
            else
                if( ch != '\r' ) nWidth += 5;
        if( nWidth > nMaxWidth ) nMaxWidth = nWidth;
    }

    return nMaxWidth;
}


void DrawString( int x, int y, const char* pszString, int nMaxWidth = 640, int nMaxHeight = 480 )
{
    RECT rcSrc, rcDst;
    x = max( x, 0 );
    y = max( y, 0 );
    rcDst.left = x;
    rcDst.top = y;

    while( *pszString )
    {
        char ch = toupper(*pszString);
        if( ch >= 32 && ch <= 95 )
        {
            ch-=32;

            rcDst.right = rcDst.left + 16;
            rcDst.bottom = rcDst.top + 16;

            rcSrc.left = (ch&0x0F) * 16;
            rcSrc.top = ((ch>>4)&0x0f) * 16;
            rcSrc.bottom = rcSrc.top + 16;
            rcSrc.right = rcSrc.left + 16;

            g_pDDSBack->Blt( &rcDst, g_pDDSFontSmall, &rcSrc, DDBLT_WAIT, NULL );

            rcDst.left += g_nSmallCharWidths[ch]*2;
        }
        else
            if( ch == '\n' )
            {
                rcDst.left = x;
                rcDst.top += 16;
            }
            else
                if( ch != '\r' ) rcDst.left += 10;

        if( rcDst.right > nMaxWidth ) { rcDst.left = x; rcDst.top += 14; }
        if( rcDst.bottom > nMaxHeight ) return;

        pszString++;
    }
}

int StringWidthLarge( const char* pszString )
{
    int nWidth = 0;
    int nMaxWidth = 0;
    while( *pszString )
    {
        char ch = toupper(*pszString++);
        if( ch >= 32 && ch <= 95 )
            nWidth += (g_nLargeCharWidths[ch-32]*2)-2;
        else
            if( ch == '\n' )
            {
                nWidth = 0;
            }
            else
                if( ch != '\r' ) nWidth += 20;
        if( nWidth > nMaxWidth ) nMaxWidth = nWidth;
    }

    return nMaxWidth;
}

void DrawStringLarge( int x, int y, const char* pszString, bool bWhite, int nMaxWidth = 640, int nMaxHeight = 480 )
{
    x = max( x, 0 );
    y = max( y, 0 );
    RECT rcSrc, rcDst;
    rcDst.left = x;
    rcDst.top = y;

    LPDIRECTDRAWSURFACE4 pDDSFnt = bWhite ? g_pDDSFontWhite : g_pDDSFontRed;

    while( *pszString )
    {
        char ch = toupper(*pszString);
        if( ch >= 32 && ch <= 95 )
        {
            ch-=32;

            rcDst.right = rcDst.left + 32;
            rcDst.bottom = rcDst.top + 32;

            rcSrc.left = ((ch&0x07)) * 32;
            rcSrc.top = ((ch>>3)&0x07) * 32;
            rcSrc.bottom = rcSrc.top + 32;
            rcSrc.right = rcSrc.left + 32;

            g_pDDSBack->Blt( &rcDst, pDDSFnt, &rcSrc, DDBLT_WAIT, NULL );

            rcDst.left += (g_nLargeCharWidths[ch]*2)-2;
        }
        else
            if( ch == '\n' )
            {
                rcDst.left = x;
                rcDst.top += 16;
            }
            else
                if( ch != '\r' ) rcDst.left += 20;

        if( rcDst.left > nMaxWidth ) { rcDst.left = x; rcDst.top += 28; }
        if( rcDst.top > nMaxHeight ) return;

        pszString++;
    }
}

void DrawSprite( int x, int y, LPDIRECTDRAWSURFACE4 pDDS )
{
    //draw it
    g_pDDSBack->BltFast( x, y, pDDS, NULL, DDBLTFAST_WAIT );
}

void DrawCursor( int x, int y )
{
    static int s_i = 0;
    DrawSprite( x, y, g_pDDSSkull[ s_i < 8 ? 0 : 1 ] );
    ++s_i &= 15;
}

void DrawBackground()
{

    //draw background texture
    g_pDDSBack->Blt( NULL, g_pDDSBackground, NULL, DDBLT_WAIT, NULL );
    //draw logo sprite
    DrawSprite( 200, 30, g_pDDSDoom );
/*

    //draw message
    DrawStringLarge( 26, 116, "LAUNCHER", FALSE );*/
}










BOOL Update()
{
    //flip
    g_pDDSPrimary->Flip( NULL, DDFLIP_WAIT );

    //pump messages
    MSG msg;
    while( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

    //update controls
    UpdateControls();
    if( g_bStart ) return FALSE;

    //draw the background
    DrawBackground();
    return TRUE;
}

void StopSounds()
{
    g_pDSBMove->Stop();
    g_pDSBCancel->Stop();
    g_pDSBAccept->Stop();
}

void MenuAcceptSoundEffect()
{
    StopSounds();
    g_pDSBAccept->Play( 0, 0, 0 );
}

void MenuCancelSoundEffect()
{
    StopSounds();
    g_pDSBCancel->Play( 0, 0, 0 );
}

void MenuMoveSoundEffect()
{
    StopSounds();
    g_pDSBMove->Play( 0, 0, 0 );
}


int PickItem( const char* pszCaption, const char** pszOptions, int nOptions )
{
    int iOption = 0;
    int i;
    char ch = '\0';
    int nHeight = ((nOptions * 28) + 60) / 2;

    int nCenter = StringWidthLarge( pszCaption ) >> 1;
    int nMaxW = 0;
    for( i = 0; i < nOptions; i++ )
    {
        int nW = StringWidthLarge( pszOptions[i] );
        if( nW > nMaxW ) nMaxW = nW;
    }
    nMaxW >>= 1;

    while( !g_bAccept )
    {
        if(!Update()) return -1;

        DrawStringLarge( 320-nCenter, 240-nHeight, pszCaption, TRUE );
        for( i = 0; i < nOptions; i++ )
        {
            int y = 240-nHeight+60+(i*38);
            if( i == iOption ) DrawCursor( 320-nMaxW-48, y-3 );
            DrawStringLarge( 320-nMaxW, y, pszOptions[i], FALSE );
        }

        if( g_bButtonPressNew )
        {
            if( g_bUp ) { MenuMoveSoundEffect(); if( --iOption < 0 ) iOption = nOptions - 1; }
            if( g_bDown ) { MenuMoveSoundEffect(); (iOption = (iOption+1) % nOptions); }
        }
    }

    MenuAcceptSoundEffect();

    return iOption; 
}

void DisplayMessage( const char* pszCaption, const char* pszMessage )
{
    int nCenterCaption = StringWidthLarge( pszCaption ) >> 1;
    int nCenterText = StringWidth( pszMessage ) >> 1;
    while( g_bButtonPressNew || g_bAccept ) if(!Update())return;
    while( !g_bAccept )
    {
        if(!Update()) return;

        DrawStringLarge( 320-nCenterCaption, 200, pszCaption, FALSE );
        DrawString( 320-nCenterText, 240, pszMessage );
        DrawCursor( 320-48, 400 );
    }

    MenuAcceptSoundEffect();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void MainLoop();

//main function
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd )
{
    //start up
    if( !InitApplication() ) return 0;

    //main loop
    MainLoop();

    //shut down
    DoneApplication();
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

