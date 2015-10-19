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
#include <array>
#include <unordered_map>
#include <string>

template <typename E, size_t NumSymbols>
class RePlexModule
{
public:
    static void LoadLibrary() { GetInstance().Load(); }
    static void ReloadLibrary() { GetInstance().Reload(); }

    static E& GetInstance()
    {
        static E instance;
        return instance;
    }

    // Should return the path to the library on disk
    virtual const char* GetPath() const = 0;

    // Should return a reference to an array of C-strings of size NumSymbols.
    // Used when loading or reloading the library to lookup the address of all
    // exported symbols.
    virtual std::array<const char*, NumSymbols>& GetSymbolNames() const = 0;

protected:

    template <typename Ret, typename... Args>
    Ret Execute(const char* name, Args... args)
    {
        // Lookup the function address
        auto symbol = m_symbols.find(name);
        if (symbol != m_symbols.end())
        {
            // Cast the address to the appropriate function type and call it,
            // forwarding all arguments
            return reinterpret_cast<Ret(*)(Args...)>(symbol->second)(args...);
        }
        else
        {
            throw std::runtime_error(std::string("Function not found: ") + name);
        }
    }

    template <typename T>
    T* GetVar(const char* name)
    {
        auto symbol = m_symbols.find(name);
        if (symbol != m_symbols.end())
        {
            return static_cast<T*>(symbol->second);
        }
        else
        {
            return nullptr;
        }
    }

private:
    void Load()
    {
        m_libHandle = dlopen(GetPath(), RTLD_NOW);
        LoadSymbols();
    }

    void Reload()
    {
        dlclose(m_libHandle);
        m_symbols.clear();
        Load();
    }

    void LoadSymbols()
    {
        for (const char* symbol: GetSymbolNames())
        {
            m_symbols[symbol] = dlsym(m_libHandle, symbol);
        }
    }

    void* m_libHandle;
    std::unordered_map<std::string, void*> m_symbols;
};

