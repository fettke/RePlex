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

    project "GoogleTest"
        kind "StaticLib"
        files { "googletest/googletest/src/gtest-all.cc" }
        includedirs { "googletest/googletest/include", "googletest/googletest" }

    -- RePlex runtime
    project "RePlexRuntime"
        kind "ConsoleApp"
        files { "runtime/**.h", "runtime/**.cpp" }
        -- link the RePlexLib library at runtime
        includedirs { "lib/pub", "test/pub", "googletest/googletest/include" }
        links { "GoogleTest" }

    project "RePlexTest"
        kind "SharedLib"
        defines { "REPLEX_EXPORT" }
        files { "test/**.h", "test/**.cpp", "test/pub/*.h" }
        includedirs { "lib/pub" }


