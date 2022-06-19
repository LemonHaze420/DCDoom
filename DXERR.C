/////////////////////////////////////////////////////////////////////////////////////
// DirectX Includes...
/////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <ddraw.h>
#include <dinput.h>
#include <dsound.h>

void WriteDebug(char *);

void DS_Error( HRESULT hresult, char *msg )
   {
    char msgtext[128];
    char errmsg[128];
    switch(hresult)
       {
        case DS_OK:
             strcpy(errmsg,"The request completed successfully.");
             break;

        case DSERR_ALLOCATED:
             strcpy(errmsg,"The request failed because resources, such as a priority level, were already in use by another caller.");
             break;

        case DSERR_ALREADYINITIALIZED:
             strcpy(errmsg,"The object is already initialized.");
             break;

        case DSERR_BADFORMAT:
             strcpy(errmsg,"The specified wave format is not supported.");
             break;

        case DSERR_BUFFERLOST:
             strcpy(errmsg,"The buffer memory has been lost and must be restored.");
             break;

        case DSERR_CONTROLUNAVAIL:
             strcpy(errmsg,"The control (volume, pan, and so forth) requested by the caller is not available.");
             break;

        case DSERR_GENERIC:
             strcpy(errmsg,"An undetermined error occurred inside the DirectSound subsystem.");
             break;

        case DSERR_INVALIDCALL:
             strcpy(errmsg,"This function is not valid for the current state of this object.");
             break;

        case DSERR_INVALIDPARAM:
             strcpy(errmsg,"An invalid parameter was passed to the returning function.");
             break;

        case DSERR_NOAGGREGATION:
             strcpy(errmsg,"The object does not support aggregation.");
             break;

        case DSERR_NODRIVER:
             strcpy(errmsg,"No sound driver is available for use.");
             break;

        case DSERR_OTHERAPPHASPRIO:
             strcpy(errmsg,"This value is obsolete and is not used.");
             break;

        case DSERR_OUTOFMEMORY:
             strcpy(errmsg,"The DirectSound subsystem could not allocate sufficient memory to complete the caller's request.");
             break;

        case DSERR_PRIOLEVELNEEDED:
             strcpy(errmsg,"The caller does not have the priority level required for the function to succeed.");
             break;

        case DSERR_UNINITIALIZED:
             strcpy(errmsg,"The IDirectSound::Initialize method has not been called or has not been called successfully before other methods were called.");
             break;

        case DSERR_UNSUPPORTED:
             strcpy(errmsg,"The function called is not supported at this time.");
             break;

        default:
             sprintf(errmsg,"Unknown Error Code: %04X", hresult);
             strcpy(errmsg, msgtext);
             break;
       }

    sprintf(msgtext, "DSERR: %s\n", errmsg);
    WriteDebug( msgtext );
    sprintf(msgtext, "%s FAILED\n", msg);
    WriteDebug( msgtext );
   }

void DD_Error( HRESULT hresult, char *msg )
   {
    static char msgtext[128];
    static char errmsg[128];
    switch(hresult)
       {
        case DD_OK:
             strcpy(errmsg,"The request completed successfully.");
             break;

        case DDERR_ALREADYINITIALIZED:
             strcpy(errmsg,"The object has already been initialized.");
             break;

        case DDERR_BLTFASTCANTCLIP:
             strcpy(errmsg,"A DirectDrawClipper object is attached to a source surface that has passed into a call to the IDirectDrawSurface2::BltFast method.");
             break;

        case DDERR_CANNOTATTACHSURFACE:
             strcpy(errmsg,"A surface cannot be attached to another requested surface.");
             break;

        case DDERR_CANNOTDETACHSURFACE:
             strcpy(errmsg,"A surface cannot be detached from another requested surface.");
             break;

        case DDERR_CANTCREATEDC:
             strcpy(errmsg,"Windows cannot create any more device contexts (DCs).");
             break;

        case DDERR_CANTDUPLICATE:
             strcpy(errmsg,"Primary and 3D surfaces, or surfaces that are implicitly created, cannot be duplicated.");
             break;

        case DDERR_CANTLOCKSURFACE:
             strcpy(errmsg,"Access to this surface is refused because an attempt was made to lock the primary surface without DCI support.");
             break;

        case DDERR_CANTPAGELOCK:
             strcpy(errmsg,"An attempt to page lock a surface failed. Page lock will not work on a display-memory surface or an emulated primary surface.");
             break;

        case DDERR_CANTPAGEUNLOCK:
             strcpy(errmsg,"An attempt to page unlock a surface failed. Page unlock will not work on a display-memory surface or an emulated primary surface.");
             break;

        case DDERR_CLIPPERISUSINGHWND:
             strcpy(errmsg,"An attempt was made to set a clip list for a DirectDrawClipper object that is already monitoring a window handle.");
             break;

        case DDERR_COLORKEYNOTSET:
             strcpy(errmsg,"No source color key is specified for this operation.");
             break;

        case DDERR_CURRENTLYNOTAVAIL:
             strcpy(errmsg,"No support is currently available.");
             break;

        case DDERR_DCALREADYCREATED:
             strcpy(errmsg,"A device context (DC) has already been returned for this surface. Only one DC can be retrieved for each surface.");
             break;

        case DDERR_DIRECTDRAWALREADYCREATED:
             strcpy(errmsg,"A DirectDraw object representing this driver has already been created for this process.");
             break;

        case DDERR_EXCEPTION:
             strcpy(errmsg,"An exception was encountered while performing the requested operation.");
             break;

        case DDERR_EXCLUSIVEMODEALREADYSET:
             strcpy(errmsg,"An attempt was made to set the cooperative level when it was already set to exclusive.");
             break;

        case DDERR_GENERIC:
             strcpy(errmsg,"There is an undefined error condition.");
             break;

        case DDERR_HEIGHTALIGN:
             strcpy(errmsg,"The height of the provided rectangle is not a multiple of the required alignment.");
             break;

        case DDERR_HWNDALREADYSET:
             strcpy(errmsg,"The DirectDraw cooperative level window handle has already been set. It cannot be reset while the process has surfaces or palettes created.");
             break;

        case DDERR_HWNDSUBCLASSED:
             strcpy(errmsg,"DirectDraw is prevented from restoring state because the DirectDraw cooperative level window handle has been subclassed.");
             break;

        case DDERR_IMPLICITLYCREATED:
             strcpy(errmsg,"The surface cannot be restored because it is an implicitly created surface.");
             break;

        case DDERR_INCOMPATIBLEPRIMARY:
             strcpy(errmsg,"The primary surface creation request does not match with the existing primary surface.");
             break;

        case DDERR_INVALIDCAPS:
             strcpy(errmsg,"One or more of the capability bits passed to the callback function are incorrect.");
             break;

        case DDERR_INVALIDCLIPLIST:
             strcpy(errmsg,"DirectDraw does not support the provided clip list.");
             break;

        case DDERR_INVALIDDIRECTDRAWGUID:
             strcpy(errmsg,"The globally unique identifier (GUID) passed to the DirectDrawCreate function is not a valid DirectDraw driver identifier.");
             break;

        case DDERR_INVALIDMODE:
             strcpy(errmsg,"DirectDraw does not support the requested mode.");
             break;

        case DDERR_INVALIDOBJECT:
             strcpy(errmsg,"DirectDraw received a pointer that was an invalid DirectDraw object.");
             break;

        case DDERR_INVALIDPARAMS:
             strcpy(errmsg,"One or more of the parameters passed to the method are incorrect.");
             break;

        case DDERR_INVALIDPIXELFORMAT:
             strcpy(errmsg,"The pixel format was invalid as specified.");
             break;

        case DDERR_INVALIDPOSITION:
             strcpy(errmsg,"The position of the overlay on the destination is no longer legal.");
             break;

        case DDERR_INVALIDRECT:
             strcpy(errmsg,"The provided rectangle was invalid.");
             break;

        case DDERR_INVALIDSURFACETYPE:
             strcpy(errmsg,"The requested operation could not be performed because the surface was of the wrong type.");
             break;

        case DDERR_LOCKEDSURFACES:
             strcpy(errmsg,"One or more surfaces are locked, causing the failure of the requested operation.");
             break;

        case DDERR_NO3D:
             strcpy(errmsg,"No 3D hardware or emulation is present.");
             break;

        case DDERR_NOALPHAHW:
             strcpy(errmsg,"No alpha acceleration hardware is present or available, causing the failure of the requested operation.");
             break;

        case DDERR_NOBLTHW:
             strcpy(errmsg,"No blitter hardware is present.");
             break;

        case DDERR_NOCLIPLIST:
             strcpy(errmsg,"No clip list is available.");
             break;

        case DDERR_NOCLIPPERATTACHED:
             strcpy(errmsg,"No DirectDrawClipper object is attached to the surface object.");
             break;

        case DDERR_NOCOLORCONVHW:
             strcpy(errmsg,"The operation cannot be carried out because no color-conversion hardware is present or available.");
             break;

        case DDERR_NOCOLORKEY:
             strcpy(errmsg,"The surface does not currently have a color key.");
             break;

        case DDERR_NOCOLORKEYHW:
             strcpy(errmsg,"The operation cannot be carried out because there is no hardware support for the destination color key.");
             break;

        case DDERR_NOCOOPERATIVELEVELSET:
             strcpy(errmsg,"A create function is called without the IDirectDraw2::SetCooperativeLevel method being called.");
             break;

        case DDERR_NODC:
             strcpy(errmsg,"No DC has ever been created for this surface.");
             break;

        case DDERR_NODDROPSHW:
             strcpy(errmsg,"No DirectDraw raster operation (ROP) hardware is available.");
             break;

        case DDERR_NODIRECTDRAWHW:
             strcpy(errmsg,"Hardware-only DirectDraw object creation is not possible; the driver does not support any hardware.");
             break;

        case DDERR_NODIRECTDRAWSUPPORT:
             strcpy(errmsg,"DirectDraw support is not possible with the current display driver.");
             break;

        case DDERR_NOEMULATION:
             strcpy(errmsg,"Software emulation is not available.");
             break;

        case DDERR_NOEXCLUSIVEMODE:
             strcpy(errmsg,"The operation requires the application to have exclusive mode, but the application does not have exclusive mode.");
             break;

        case DDERR_NOFLIPHW:
             strcpy(errmsg,"Flipping visible surfaces is not supported.");
             break;

        case DDERR_NOGDI:
             strcpy(errmsg,"No GDI is present.");
             break;

        case DDERR_NOHWND:
             strcpy(errmsg,"Clipper notification requires a window handle, or no window handle has been previously set as the cooperative level window handle.");
             break;

        case DDERR_NOMIPMAPHW:
             strcpy(errmsg,"The operation cannot be carried out because no mipmap texture mapping hardware is present or available.");
             break;

        case DDERR_NOMIRRORHW:
             strcpy(errmsg,"The operation cannot be carried out because no mirroring hardware is present or available.");
             break;

        case DDERR_NOOVERLAYDEST:
             strcpy(errmsg,"The IDirectDrawSurface2::GetOverlayPosition method is called on an overlay that the IDirectDrawSurface2::UpdateOverlay method has not been called on to establish a destination.");
             break;

        case DDERR_NOOVERLAYHW:
             strcpy(errmsg,"The operation cannot be carried out because no overlay hardware is present or available.");
             break;

        case DDERR_NOPALETTEATTACHED:
             strcpy(errmsg,"No palette object is attached to this surface.");
             break;

        case DDERR_NOPALETTEHW:
             strcpy(errmsg,"There is no hardware support for 16- or 256-color palettes.");
             break;

        case DDERR_NORASTEROPHW:
             strcpy(errmsg,"The operation cannot be carried out because no appropriate raster operation hardware is present or available.");
             break;

        case DDERR_NOROTATIONHW:
             strcpy(errmsg,"The operation cannot be carried out because no rotation hardware is present or available.");
             break;

        case DDERR_NOSTRETCHHW:
             strcpy(errmsg,"The operation cannot be carried out because there is no hardware support for stretching.");
             break;

        case DDERR_NOT4BITCOLOR:
             strcpy(errmsg,"The DirectDrawSurface object is not using a 4-bit color palette and the requested operation requires a 4-bit color palette.");
             break;

        case DDERR_NOT4BITCOLORINDEX:
             strcpy(errmsg,"The DirectDrawSurface object is not using a 4-bit color index palette and the requested operation requires a 4-bit color index palette.");
             break;

        case DDERR_NOT8BITCOLOR:
             strcpy(errmsg,"The DirectDrawSurface object is not using an 8-bit color palette and the requested operation requires an 8-bit color palette.");
             break;

        case DDERR_NOTAOVERLAYSURFACE:
             strcpy(errmsg,"An overlay component is called for a non-overlay surface.");
             break;

        case DDERR_NOTEXTUREHW:
             strcpy(errmsg,"The operation cannot be carried out because no texture-mapping hardware is present or available.");
             break;

        case DDERR_NOTFLIPPABLE:
             strcpy(errmsg,"An attempt has been made to flip a surface that cannot be flipped.");
             break;

        case DDERR_NOTFOUND:
             strcpy(errmsg,"The requested item was not found.");
             break;

        case DDERR_NOTINITIALIZED:
             strcpy(errmsg,"An attempt was made to call an interface method of a DirectDraw object created by CoCreateInstance before the object was initialized.");
             break;

        case DDERR_NOTLOCKED:
             strcpy(errmsg,"An attempt is made to unlock a surface that was not locked.");
             break;

        case DDERR_NOTPAGELOCKED:
             strcpy(errmsg,"An attempt is made to page unlock a surface with no outstanding page locks.");
             break;

        case DDERR_NOTPALETTIZED:
             strcpy(errmsg,"The surface being used is not a palette-based surface.");
             break;

        case DDERR_NOVSYNCHW:
             strcpy(errmsg,"The operation cannot be carried out because there is no hardware support for vertical blank synchronized operations.");
             break;

        case DDERR_NOZBUFFERHW:
             strcpy(errmsg,"The operation to create a z-buffer in display memory or to perform a blit using a z-buffer cannot be carried out because there is no hardware support for z-buffers.");
             break;

        case DDERR_NOZOVERLAYHW:
             strcpy(errmsg,"The overlay surfaces cannot be z-layered based on the z-order because the hardware does not support z-ordering of overlays.");
             break;

        case DDERR_OUTOFCAPS:
             strcpy(errmsg,"The hardware needed for the requested operation has already been allocated.");
             break;

        case DDERR_OUTOFMEMORY:
             strcpy(errmsg,"DirectDraw does not have enough memory to perform the operation.");
             break;

        case DDERR_OUTOFVIDEOMEMORY:
             strcpy(errmsg,"DirectDraw does not have enough display memory to perform the operation.");
             break;

        case DDERR_OVERLAYCANTCLIP:
             strcpy(errmsg,"The hardware does not support clipped overlays.");
             break;

        case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
             strcpy(errmsg,"An attempt was made to have more than one color key active on an overlay.");
             break;

        case DDERR_OVERLAYNOTVISIBLE:
             strcpy(errmsg,"The IDirectDrawSurface2::GetOverlayPosition method is called on a hidden overlay.");
             break;

        case DDERR_PALETTEBUSY:
             strcpy(errmsg,"Access to this palette is refused because the palette is locked by another thread.");
             break;

        case DDERR_PRIMARYSURFACEALREADYEXISTS:
             strcpy(errmsg,"This process has already created a primary surface.");
             break;

        case DDERR_REGIONTOOSMALL:
             strcpy(errmsg,"The region passed to the IDirectDrawClipper::GetClipList method is too small.");
             break;

        case DDERR_SURFACEALREADYATTACHED:
             strcpy(errmsg,"An attempt was made to attach a surface to another surface to which it is already attached.");
             break;

        case DDERR_SURFACEALREADYDEPENDENT:
             strcpy(errmsg,"An attempt was made to make a surface a dependency of another surface to which it is already dependent.");
             break;

        case DDERR_SURFACEBUSY:
             strcpy(errmsg,"Access to the surface is refused because the surface is locked by another thread.");
             break;

        case DDERR_SURFACEISOBSCURED:
             strcpy(errmsg,"Access to the surface is refused because the surface is obscured.");
             break;

        case DDERR_SURFACELOST:
             strcpy(errmsg,"Access to the surface is refused because the surface memory is gone. The DirectDrawSurface object representing this surface should have the IDirectDrawSurface2::Restore method called on it.");
             break;

        case DDERR_SURFACENOTATTACHED:
             strcpy(errmsg,"The requested surface is not attached.");
             break;

        case DDERR_TOOBIGHEIGHT:
             strcpy(errmsg,"The height requested by DirectDraw is too large.");
             break;

        case DDERR_TOOBIGSIZE:
             strcpy(errmsg,"The size requested by DirectDraw is too large. However, the individual height and width are OK.");
             break;

        case DDERR_TOOBIGWIDTH:
             strcpy(errmsg,"The width requested by DirectDraw is too large.");
             break;

        case DDERR_UNSUPPORTED:
             strcpy(errmsg,"The operation is not supported.");
             break;

        case DDERR_UNSUPPORTEDFORMAT:
             strcpy(errmsg,"The FourCC format requested is not supported by DirectDraw.");
             break;

        case DDERR_UNSUPPORTEDMASK:
             strcpy(errmsg,"The bitmask in the pixel format requested is not supported by DirectDraw.");
             break;

        case DDERR_UNSUPPORTEDMODE:
             strcpy(errmsg,"The display is currently in an unsupported mode.");
             break;

        case DDERR_VERTICALBLANKINPROGRESS:
             strcpy(errmsg,"A vertical blank is in progress.");
             break;

        case DDERR_WASSTILLDRAWING:
             strcpy(errmsg,"The previous blit operation that is transferring information to or from this surface is incomplete.");
             break;

        case DDERR_WRONGMODE:
             strcpy(errmsg,"This surface cannot be restored because it was created in a different mode.");
             break;

        case DDERR_XALIGN:
             strcpy(errmsg,"The provided rectangle was not horizontally aligned on a required boundary.");
             break;

        default:
             sprintf(errmsg, "Unknown Error Code : %04X", hresult);
             break;
       }

    sprintf(msgtext, "DDERR: %s\n", errmsg);
    WriteDebug( msgtext );
    sprintf(msgtext, "%s FAILED\n", msg);
    WriteDebug( msgtext );
   }

void DI_Error( HRESULT hresult, char *msg)
   {
    char msgtext[512];
    char errmsg[512];
    switch(hresult)
       {
        case DI_BUFFEROVERFLOW:
             strcpy(errmsg, "The device buffer overflowed and some input was lost. This value is equal to the S_FALSE standard COM return value.");
             break;
        case DI_DOWNLOADSKIPPED: 
             strcpy(errmsg, "The parameters of the effect were successfully updated, but the effect could not be downloaded because the associated device was not acquired in exclusive mode.");
             break;
        case DI_EFFECTRESTARTED:
             strcpy(errmsg, "The effect was stopped, the parameters were updated, and the effect was restarted.");
             break;
        case DI_OK:
             strcpy(errmsg, "The operation completed successfully. This value is equal to the S_OK standard COM return value.");
             break;
        case DI_POLLEDDEVICE:
             strcpy(errmsg, "The device is a polled device. As a result, device buffering will not collect any data and event notifications will not be signaled until the IDirectInputDevice2::Poll method is called.");
             break;
        case DI_TRUNCATED:
             strcpy(errmsg, "The parameters of the effect were successfully updated, but some of them were beyond the capabilities of the device and were truncated to the nearest supported value.");
             break;
        case DI_TRUNCATEDANDRESTARTED:
             strcpy(errmsg, "Equal to DI_EFFECTRESTARTED | DI_TRUNCATED");
             break;
        case DIERR_ACQUIRED:
             strcpy(errmsg, "The operation cannot be performed while the device is acquired.");
             break;
        case DIERR_ALREADYINITIALIZED:
             strcpy(errmsg, "This object is already initialized");
             break;
        case DIERR_BADDRIVERVER:
             strcpy(errmsg, "The object could not be created due to an incompatible driver version or mismatched or incomplete driver components.");
             break;
        case DIERR_BETADIRECTINPUTVERSION:
             strcpy(errmsg, "The application was written for an unsupported prerelease version of DirectInput.");
             break;
        case DIERR_DEVICEFULL:
             strcpy(errmsg, "The device is full.");
             break;
        case DIERR_DEVICENOTREG:
             strcpy(errmsg, "The device or device instance is not registered with DirectInput. This value is equal to the REGDB_E_CLASSNOTREG standard COM return value.");
             break;
        case DIERR_EFFECTPLAYING:
             strcpy(errmsg, "The parameters were updated in memory but were not downloaded to the device because the device does not support updating an effect while it is still playing.");
             break;
        case DIERR_HASEFFECTS:
             strcpy(errmsg, "The device cannot be reinitialized because there are still effects attached to it");
             break;
        case DIERR_GENERIC:
             strcpy(errmsg, "An undetermined error occurred inside the DirectInput subsystem. This value is equal to the E_FAIL standard COM return value.");
             break;
        case DIERR_HANDLEEXISTS:
             strcpy(errmsg, "The device already has an event notification associated with it. This value is equal to the E_ACCESSDENIED standard COM return value.");
             break;
        case DIERR_INCOMPLETEEFFECT:
             strcpy(errmsg, "The effect could not be downloaded because essential information is missing. For example, no axes have been associated with the effect, or no type-specific information has been supplied.");
             break;
        case DIERR_INPUTLOST:
             strcpy(errmsg, "Access to the input device has been lost. It must be reacquired.");
             break;
        case DIERR_INVALIDPARAM:
             strcpy(errmsg, "An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called. This value is equal to the E_INVALIDARG standard COM return value.");
             break;
        case DIERR_MOREDATA:
             strcpy(errmsg, "Not all the requested information fitted into the buffer.");
             break;
        case DIERR_NOAGGREGATION:
             strcpy(errmsg, "This object does not support aggregation.");
             break;
        case DIERR_NOINTERFACE:
             strcpy(errmsg, "The specified interface is not supported by the object. This value is equal to the E_NOINTERFACE standard COM return value.");
             break;
        case DIERR_NOTACQUIRED:
             strcpy(errmsg, "The operation cannot be performed unless the device is acquired.");
             break;
        case DIERR_NOTBUFFERED:
             strcpy(errmsg, "The device is not buffered. Set the DIPROP_BUFFERSIZE property to enable buffering.");
             break;
        case DIERR_NOTDOWNLOADED:
             strcpy(errmsg, "The effect is not downloaded.");
             break;
        case DIERR_NOTEXCLUSIVEACQUIRED:
             strcpy(errmsg, "The operation cannot be performed unless the device is acquired in DISCL_EXCLUSIVE mode.");
             break;
        case DIERR_NOTFOUND:
             strcpy(errmsg, "The requested object does not exist.");
             break;
        case DIERR_NOTINITIALIZED:
             strcpy(errmsg, "This object has not been initialized.");
             break;
        case DIERR_OLDDIRECTINPUTVERSION:
             strcpy(errmsg, "The application requires a newer version of DirectInput.");
             break;
        case DIERR_OUTOFMEMORY:
             strcpy(errmsg, "The DirectInput subsystem couldn't allocate sufficient memory to complete the call. This value is equal to the E_OUTOFMEMORY standard COM return value.");
             break;
        case DIERR_UNSUPPORTED:
             strcpy(errmsg, "The function called is not supported at this time. This value is equal to the E_NOTIMPL standard COM return value.");
             break;
        case E_PENDING:
             strcpy(errmsg, "Data is not yet available.");
             break;
        default:
             sprintf(errmsg, "Unknown Error Code : %04X", hresult);
             break;
       }
    sprintf(msgtext, "DIERR: %s\n", errmsg);
    WriteDebug( msgtext );
    sprintf(msgtext, "%s FAILED\n", msg);
    WriteDebug( msgtext );
   }


