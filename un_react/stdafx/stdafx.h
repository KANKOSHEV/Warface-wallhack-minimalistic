///////////////////////////////////////
#include <Windows.h>
#include <d3d9.h>
#include "..\minicrt\mincrt.h"
#include "..\importer\lazy_importer.h"
#include "..\xor\xor_string.h"
///////////////////////////////////////
#define j_malloc                ((void*(*)(size_t))0x14162CF25) 
#define j_free                  ((void*(*)(void*))0x14162CF1F) 
#define j_memcpy                ((void*(*)(void*, void const*, size_t))0x14162CE11) 
#define j_memset                ((void*(*)(void*, int, size_t))0x14162CE1D) 
#define zero_memory(dst, size)  j_memset(dst, 0, size) 
#define j_get_async_key_state   ((int(*)(int))0x1400AC110) // j_GetAsyncKeyState
/////////////////////////////////////// 
void* __cdecl operator new(size_t size)
{
	return static_cast<void*>(j_malloc(size));
}
void operator delete(void* p)
{
	if (p != NULL)
		j_free(p);
}
void* __cdecl operator new[](size_t n)
{
	return operator new(n);
}
void  __cdecl operator delete[](void* p)
{
	operator delete(p);
}
void  __cdecl operator delete[](void* p, size_t)
{
	operator delete[](p);
}
void  __cdecl operator delete(void* p, size_t)
{
	operator delete(p);
}
///////////////////////////////////////
