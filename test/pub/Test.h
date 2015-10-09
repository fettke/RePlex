#pragma once

#ifdef REPLEX_EXPORT
#define REPLEX_API __declspec(dllexport)
#else
#define REPLEX_API __declspec(dllimport)
#endif

extern "C"
{
    void REPLEX_API foo();

    extern int REPLEX_API bar;
}
