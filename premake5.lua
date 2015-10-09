workspace "RePlex"
    configurations {"Debug", "Release"}
    -- Use C++ as the target language for all builds
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    flags { "C++14" }

    filter "configurations:Debug"
        -- Add the preprocessor definition DEBUG to debug builds
        defines { "DEBUG" }
        -- Ensure symbols are bundled with debug builds
        flags { "Symbols" }

    filter "configurations:Release"
        defines { "RELEASE" }
        -- Turn on compiler optimizations for release builds
        optimize "On"

    -- RePlex library
    project "RePlex"
        kind "SharedLib"
        defines { "REPLEX_EXPORT" }
        -- recursively glob .h and .cpp files in the lib directory
        files { "lib/**.h", "lib/**.cpp" }

    -- RePlex runtime
    project "RePlexRuntime"
        kind "ConsoleApp"
        files { "runtime/**.h", "runtime/**.cpp" }
        -- link the RePlexLib library at runtime
        links { "RePlex" }
        includedirs { "lib/pub" }

