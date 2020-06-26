workspace "OpenGL"
    architecture "x86"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
 
include "OpenGL"