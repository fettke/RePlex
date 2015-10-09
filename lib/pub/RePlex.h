#pragma once

#ifdef REPLEX_EXPORT
#define REPLEX_API __declspec(dllexport)
#else
#define REPLEX_API __declspec(dllimport)
#endif

class REPLEX_API Foo
{
public:
    int GetTheAnswer() const;
private:
    int m_answer = 42;
};
