/// @author YellowAfterlife

#include "stdafx.h"

#if defined(WIN32)
#define dllx extern "C" __declspec(dllexport)
#elif defined(GNUC)
#define dllx extern "C" __attribute__ ((visibility("default"))) 
#else
#define dllx extern "C"
#endif

#define trace(...) { printf("[GMSDLL:%d] ", __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }

