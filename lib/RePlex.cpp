#include "pub/RePlex.h"
#include <cstdio>

void* Load(const char* filepath)
{
	return (void*)LoadLibrary(TEXT(filepath));
}


void* LoadSymbol(void* library, const char* symbol)
{
	return (void*)GetProcAddress(HINSTANCE(library), symbol);
}

void Reload(void* &library, const char* filepath)
{
	FreeLibrary(HINSTANCE(library));
	library = Load(filepath);
}
