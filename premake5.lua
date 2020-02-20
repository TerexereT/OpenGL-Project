




outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


IncludeDir = {}
IncludeDir["Catch2"] = "dependencies/Catch2"
IncludeDir["glad"] = "dependencies/glad/include"
IncludeDir["glm"] = "dependencies/glm/"
IncludeDir["ImGui"] = "dependencies/imgui/"
IncludeDir["SDL"] = "dependencies/SDL/include"
IncludeDir["stb"] = "dependencies/stb"
IncludeDir["GLFW"] = "dependencies/glfw/include"
-- IncludeDir["ImguIZMO"] = "dependencies/imGuIZMO.quat"

workspace "EasyDIP"
disablewarnings { "26495" }
   architecture "x64"
   startproject("EasyDIPClient")
   configurations { "Debug", "Release"}

   group "Dependencies"
      include "dependencies/glad"
      include "dependencies/imgui"
      include "dependencies/glfw"
      -- include "imquat"
      -- include "dependencies/imGuIZMO.quat"
      --include "dependencies/SDL"	
   group ""

project "EasyDIPAPI"
   systemversion "latest"
   architecture "x64"

   location("%{prj.name}")
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"

   files { "%{prj.name}/**.h", "%{prj.name}/**.cpp", "%{prj.name}/shaders/**.*"}

   links {
      "glad",
      "GLFW"
   }
	includedirs{
      -- "%{IncludeDir.SDL}",
      --"%{IncludeDir.ImguIZMO}",
      "%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
      "%{IncludeDir.stb}",
      "%{IncludeDir.glm}"

	}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      

   filter "action:xcode4"
      buildoptions {
         "-Wall", "-Wextra", "-Werror", "-fdeclspec"
      }
      xcodebuildsettings { 
         ["WARNING_CFLAGS"] = "-Wall -Wextra " ..
            "-Wno-missing-field-initializers " ..
            "-Wno-unknown-pragmas " ..
            "-Wno-unused-parameter " ..
            "-Wno-unused-local-typedef " ..
            "-Wno-missing-braces " ..
            "-Wno-microsoft-anon-tag ",
            ["CLANG_ENABLE_OBJC_WEAK"] = "YES",
            ["Enable Testability"] = "YES",
      }
            
project "EasyDIPClient"
   systemversion "latest"
   location("%{prj.name}")
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"

   files { "%{prj.name}/**.h", "%{prj.name}/**.cpp" }

   links {
      --"imGuIZMO.quat",
      "imquat",
      "EasyDIPAPI",
      "glad",
      "GLFW",
      "ImGui"
   }
   libdirs { "../RecastDemo/Contrib/SDL/lib/%{cfg.architecture:gsub('x86_64', 'x64')}" }
   postbuildcommands {
      -- Copy the SDL2 dll to the Bin folder.
      -- '{COPY} "%{path.getabsolute("Contrib/SDL/lib/" .. cfg.architecture:gsub("x86_64", "x64") .. "/SDL2.dll")}" "%{cfg.targetdir}"'
   }

   includedirs{
      --"%{IncludeDir.ImguIZMO}",
      "EasyDIPAPI",
		"%{prj.name}/src",
		"%{IncludeDir.SDL}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
      "%{IncludeDir.GLFW}"
      
      
	}


   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"




      
project "imquat"
   kind "StaticLib"
   language "C"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   files
   {
      "dependencies/imGuIZMO.quat/*.h",
      "dependencies/imGuIZMO.quat/*.cpp",
   }

   includedirs
   {
      ".",
      "%{IncludeDir.glm}",
      "%{IncludeDir.ImGui}"
   }

   links
   {
      "ImGui"
   }

   filter "system:windows"
      systemversion "latest"

   filter "configurations:Debug"
      runtime "Debug"
      symbols "on"

   filter "configurations:Release"
      runtime "Release"
      optimize "on"