#include "stdafx.h"

/**
	Note: you might have to disable "Whole-program optimization" (/GL) for this file in MSVC
**/
#if defined(TINY)
#include <stdint.h>
#include <intrin.h>

#pragma warning(disable: 28251 28252 6001)

#ifdef tiny_memset
#pragma function(memset)
void* __cdecl memset(void* _Dst, _In_ int _Val, _In_ size_t _Size) {
	#ifdef _MSC_VER
	__stosb(static_cast<uint8_t*>(_Dst), static_cast<uint8_t>(_Val), _Size);
	#else
	auto ptr = static_cast<uint8_t*>(_Dst);
	while (_Size) {
		*ptr++ = _Val;
		_Size--;
	}
	#endif
	return _Dst;
}
#endif

#ifdef tiny_memcpy
#pragma function(memcpy)
void* memcpy(void* _Dst, const void* _Src, size_t _Size) {
	// NB! Doesn't handle overlaps between source and destination block.
	#ifdef _MSC_VER
	__movsb(static_cast<uint8_t*>(_Dst), static_cast<const uint8_t*>(_Src), _Size);
	#else
	auto src8 = static_cast<const uint64_t*>(_Src);
	auto dst8 = static_cast<uint64_t*>(_Dst);
	for (; _Size > 32; _Size -= 32) {
		*dst8++ = *src8++;
		*dst8++ = *src8++;
		*dst8++ = *src8++;
		*dst8++ = *src8++;
	}
	for (; _Size > 8; _Size -= 8) *dst8++ = *src8++;
	//
	auto src1 = (const uint8_t*)(src8);
	auto dst1 = (uint8_t*)(dst8);
	for (; _Size != 0; _Size--) *dst1++ = *src1++;
	#endif
	return _Dst;
}
#endif

#pragma warning(default: 28251 28252 6001)

#endif
