solution "MySolution"
	configurations {"Debug", "Release"}
	
	project "app"
		kind "ConsoleApp"
		language "C++"
		buildoptions { "-std=c++11" }
		links { "sfml-graphics", "sfml-window", "sfml-system", "GL" }
		includedirs{ "../include" }
		files {
			"../include/**.h",
			"../src/**.cpp"
		}

