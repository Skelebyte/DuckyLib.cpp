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

    files { 
        "duckylib/include/*/*.hpp",
        "duckylib/third_party/*.hpp", 
        "duckylib/third_party/*/*.h", 
        "duckylib/src/*/*.cpp", 
        "duckylib/src/*/*/*.cpp", 
        "duckylib/src/*.cpp", 
        "duckylib/third_party/*/*.c", 
        "duckylib/third_party/*/*.cpp",
    }
    

    includedirs { "duckylib/include", "duckylib/third_party/*", "duckylib/third_party/SDL3/include", "duckylib/include/*", "duckylib/include/*/*" }

    libdirs { "duckylib/third_party/libs/windows", "duckylib/third_party/libs/linux" }

    buildoptions { "-lSDL3" }

    filter "system:windows"
        links { "SDL3", "assimp-vc143-mtd" }

    filter "system:linux"
        links { "SDL3", "assimp" }
        
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
