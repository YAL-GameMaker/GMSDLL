#include "stdafx.h"

/**
    Implements the absolute bare minimum for static init, cleanup, and and atexit()
    https://learn.microsoft.com/en-us/cpp/c-runtime-library/crt-initialization?view=msvc-170
    https://gist.github.com/vaualbus/622099d88334fbba1d4ae703642c2956
**/
#if defined(TINY) && defined(tiny_init_cleanup)

#pragma section(".CRT$XIA", long, read) // First C Initializer
#pragma section(".CRT$XIZ", long, read) // Last C Initializer
#pragma section(".CRT$XCA", long, read) // First C++ Initializer
#pragma section(".CRT$XCZ", long, read) // Last C++ Initializer
#pragma section(".CRT$XPA", long, read) // First Pre-Terminator
#pragma section(".CRT$XPZ", long, read) // Last Pre-Terminator
#pragma section(".CRT$XTA", long, read) // First Terminator
#pragma section(".CRT$XTZ", long, read) // Last Terminator

#pragma comment(linker, "/merge:.CRT=.rdata")

#define _CRTALLOC(x) __declspec(allocate(x))
typedef int(__cdecl* _PIFV)(void);
typedef void(__cdecl* _PVFV)(void);

extern "C" {
    _CRTALLOC(".CRT$XIA") _PIFV __xi_a[] = { nullptr }; // C initializers (first)
    _CRTALLOC(".CRT$XIZ") _PIFV __xi_z[] = { nullptr }; // C initializers (last)
    _CRTALLOC(".CRT$XCA") _PVFV __xc_a[] = { nullptr }; // C++ initializers (first)
    _CRTALLOC(".CRT$XCZ") _PVFV __xc_z[] = { nullptr }; // C++ initializers (last)
    _CRTALLOC(".CRT$XPA") _PVFV __xp_a[] = { nullptr }; // C pre-terminators (first)
    _CRTALLOC(".CRT$XPZ") _PVFV __xp_z[] = { nullptr }; // C pre-terminators (last)
    _CRTALLOC(".CRT$XTA") _PVFV __xt_a[] = { nullptr }; // C terminators (first)
    _CRTALLOC(".CRT$XTZ") _PVFV __xt_z[] = { nullptr }; // C terminators (last)

    int __cdecl _initterm_e(_PIFV* first, _PIFV* last) {
        for (_PIFV* it = first; it != last; ++it) {
            if (*it == nullptr) continue;

            int const result = (**it)();
            if (result != 0) return result;
        }
        return 0;
    }

    void __cdecl _initterm(_PVFV* first, _PVFV* last) {
        for (_PVFV* it = first; it != last; ++it) {
            if (*it != nullptr) {
                (**it)();
            }
        }
    }

    struct {
        _PVFV* items = nullptr;
        size_t size = 0;
        size_t capacity = 0;
    } static exitList;

    int __cdecl atexit(_PVFV func) {
        auto capacity = exitList.capacity;
        if (exitList.size >= capacity) {
            if (capacity) capacity *= 2; else capacity = 4;
            _PVFV* new_data = realloc_arr(exitList.items, capacity);
            if (new_data == nullptr) return -1;
            exitList.items = new_data;
            exitList.capacity = capacity;
        }
        exitList.items[exitList.size++] = func;
        return 0;
    }
}

void tiny_init() {
    _initterm_e(__xi_a, __xi_z);
    _initterm(__xc_a, __xc_z);
}

void tiny_cleanup() {
    if (exitList.size) {
        auto i = exitList.size;
        do {
            auto fn = exitList.items[--i];
            fn();
        } while (i != 0);
        exitList.size = 0;
        exitList.capacity = 0;
        HeapFree(GetProcessHeap(), 0, exitList.items);
        exitList.items = nullptr;
    }

    _initterm(__xp_a, __xp_z);
    _initterm(__xt_a, __xt_z);
}

#else
void tiny_init() {}
void tiny_cleanup() {}
#endif