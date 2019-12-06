#include "stdafx/stdafx.h"
#include "library/cry_classes.h"
#include "library/cry_reversing.h"
#include "hook/hook.h"

BOOL WINAPI create_update(i_system* _system, int flags, int pause_mode)
{
	create_silhouettes();
	return p_update(_system, flags, pause_mode);
}

BOOL APIENTRY entry_dll(HINSTANCE h_module, DWORD dw_reason, LPVOID lpv_reserved)
{
	UNREFERENCED_PARAMETER(h_module);
	UNREFERENCED_PARAMETER(lpv_reserved);
	if (dw_reason == DLL_PROCESS_ATTACH)
	{
		p_hook = new c_vmt((PDWORD64*)i_system_global::singleton()->get_system());
		p_update = (m_update)p_hook->apply((DWORD64)create_update, 0x4);
	}
	else if (dw_reason == DLL_PROCESS_DETACH)
	{
		p_hook->un_hook();
	}
	return TRUE;
}







