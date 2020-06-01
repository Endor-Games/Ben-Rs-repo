workspace "Game"
    architecture "x64"
    startproject "Game"

    configurations {
        "Debug",
        "Release"
    }

    flags {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to Engine
IncludeDir = {}
IncludeDir["glad"] = "vendor/glad/include"
IncludeDir["glfw"] = "vendor/glfw/include"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["imgui"] = "vendor/imgui"

-- Projects
group "Dependencies"
    include "Engine/vendor/glfw"
    include "Engine/vendor/glad"
    include "Engine/vendor/imgui"
group ""

include "Engine"
include "Game"
