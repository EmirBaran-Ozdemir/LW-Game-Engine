workspace "LW-Game-Engine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.ststem}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "LW-Game-Engine/vendor/GLFW/include"

include "LW-Game-Engine/vendor/GLFW"


project "LW-Game-Engine"
	location "LW-Game-Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "lwpch.h"
	pchsource "LW-Game-Engine/src/lwpch.h"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	
	links
	{
		"GLFW",
		"opengl32.lib",
		"dwmapi.lib"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LWE_PLATFORM_WINDOWS",
			"LWE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}


	filter "configurations:Debug"
		defines "LWE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LWE_RELEASE"
		optimize "On"
	
	filter "configurations:Dist"
		defines "LWE_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"LW-Game-Engine/vendor/spdlog/include",
		"LW-Game-Engine/src"
	}
	links
	{
		"LW-Game-Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LWE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "LWE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LWE_RELEASE"
		optimize "On"
	
	filter "configurations:Dist"
		defines "LWE_DIST"
		optimize "On"