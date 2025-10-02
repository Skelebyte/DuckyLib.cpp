workspace "DuckyLib"
    configurations { "Debug", "Release" }
    platforms { "x64", "x86" }
    location "build"

project "DuckyLib"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}-%{cfg.platform}"
    objdir "obj/%{cfg.buildcfg}-%{cfg.platform}/%{prj.name}"

    files { "duckylib/include/*/*.hpp", "duckylib/include/*.hpp", "duckylib/third_party/*/*.h", "duckylib/src/*/*.cpp", "duckylib/src/*.cpp", "duckylib/third_party/*/*.c" }

    includedirs { "duckylib/include", "duckylib/third_party/*", "duckylib/include/*" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
