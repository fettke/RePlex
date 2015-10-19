#include "pub/RePlex.h"
#include <cstdio>

void* Load(const char* filepath)
{
#ifdef WIN32
	return (void*)LoadLibrary(TEXT(filepath));
#else
	return dlopen(filepath, RTLD_NOW);
#endif
}


void* LoadSymbol(void* library, const char* symbol)
{
#ifdef WIN32
	return (void*)GetProcAddress(HINSTANCE(library), symbol);
#else
	return dlsym(library, symbol);
#endif
}

void Reload(void* &library, const char* filepath)
{
#ifdef WIN32
	FreeLibrary(HINSTANCE(library));
	library = Load(filepath);
#else
	dlclose(library);
	library = dlopen(filepath, RTLD_NOW);
#endif
}
