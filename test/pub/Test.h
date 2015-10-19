#pragma once

#ifdef WIN32
#ifdef REPLEX_EXPORT
#define REPLEX_API __declspec(dllexport)
#else
#define REPLEX_API __declspec(dllimport)
#endif
#else
#define REPLEX_API
#endif

extern "C"
{
    void REPLEX_API foo();

    extern int REPLEX_API bar;
}
