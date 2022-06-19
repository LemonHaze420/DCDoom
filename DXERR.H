// dxerr.h
#include <ddraw.h>
#include <dinput.h>
#include <dsound.h>

void DS_Error( HRESULT hresult, char *msg );
void DI_Error( HRESULT hresult, char *msg );
void DD_Error( HRESULT hresult, char *msg );

