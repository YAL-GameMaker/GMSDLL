#include "stdafx.h"

#if defined(TINY) && defined(tiny_malloc)

#pragma warning(disable: 28251 28252)
void* __cdecl malloc(size_t _Size) {
	auto result = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, _Size);
	return result;
}
void* __cdecl realloc(void* _Block, size_t _Size) {
	auto heap = GetProcessHeap();
	void* result;
	if (_Block == nullptr) {
		// unlike the CRT realloc, HeapReAlloc won't Alloc if a block is NULL
		result = HeapAlloc(heap, HEAP_ZERO_MEMORY, _Size);
	} else {
		result = HeapReAlloc(heap, HEAP_ZERO_MEMORY, _Block, _Size);
	}
	return result;
}
void __cdecl free(void* _Block) {
	HeapFree(GetProcessHeap(), 0, _Block);
}

#ifdef tiny_new
void* operator new(size_t _Size) {
	return malloc(_Size);
}
void* operator new[](size_t _Size) {
	return malloc(_Size);
}

void operator delete(void* _Block) {
	free(_Block);
}
void operator delete(void* _Block, size_t _Size) {
	free(_Block);
}
void operator delete[](void* _Block) {
	free(_Block);
}
void operator delete[](void* _Block, size_t _Size) {
	free(_Block);
}
#endif

#pragma warning(default: 28251 28252)

#endif
