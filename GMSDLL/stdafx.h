// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef _WINDOWS
	#include "targetver.h"
	
	#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
	#include <windows.h>
#endif

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#define tiny_cpp17
#endif

#if defined(WIN32)
#define dllx extern "C" __declspec(dllexport)
#elif defined(GNUC)
#define dllx extern "C" __attribute__ ((visibility("default"))) 
#else
#define dllx extern "C"
#endif

#define _trace // requires user32.lib;Kernel32.lib
//#define tiny_memset
//#define tiny_memcpy
//#define tiny_malloc

#ifdef _trace
#ifdef _WINDOWS
void trace(const char* format, ...);
#else
#define trace(...) { printf("[GMSDLL:%d] ", __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#endif
#endif

#pragma region typed memory helpers
template<typename T> T* malloc_arr(size_t count) {
	return (T*)malloc(sizeof(T) * count);
}
template<typename T> T* realloc_arr(T* arr, size_t count) {
	return (T*)realloc(arr, sizeof(T) * count);
}
template<typename T> T* memcpy_arr(T* dst, const T* src, size_t count) {
	return (T*)memcpy(dst, src, sizeof(T) * count);
}
#pragma endregion

#include "gml_ext.h"

// TODO: reference additional headers your program requires here
