#pragma once

#ifdef WIN32
#include <Windows.h>

#ifdef REPLEX_EXPORT
#define REPLEX_API __declspec(dllexport)
#else
#define REPLEX_API __declspec(dllimport)
#endif
#else //WIN32
#include <dlfcn.h>
#define REPLEX_API
#endif


extern "C" {
	void REPLEX_API *Load(const char* filepath);
	void REPLEX_API *LoadSymbol(void* library, const char* symbol);
	void REPLEX_API Reload(void* &library, const char* filepath);
}
