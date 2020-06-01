project "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../target/" .. outputdir .. "/%{prj.name}")
	objdir ("../target/tmp/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"../Engine/src",
		"../Engine/vendor",
		"../Engine/vendor/spdlog/include",
		"../Engine/%{IncludeDir.glad}",
		"../Engine/%{IncludeDir.glm}",
		"../Engine/%{IncludeDir.imgui}",
	}

	links {
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		runtime "Release"
        optimize "on"
