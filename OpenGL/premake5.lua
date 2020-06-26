project "OpenGL"
    kind "ConsoleApp"
    language "C++"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Source/**.h",
        "Source/**.cpp",
        "Source/**.hpp",
        "Source/**.inl"
    }

    defines
	{
        "GLEW_STATIC",
        "_MBCS"
	}


    includedirs
    {
        "Source",
        "Source/Vendor",
        "../Dependencies/GLEW/include",
        "../Dependencies/GLFW/include"
    }

    libdirs
    {
        "../Dependencies/GLEW/lib/Release/Win32",
        "../Dependencies/GLFW/lib-vc2017"
    }

    links
    {
        "glew32s.lib",
        "glfw3.lib",
        "opengl32.lib"
    }

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
        optimize "on"