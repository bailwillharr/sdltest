cmake_minimum_required(VERSION 3.10)

project(SDLTest LANGUAGES CXX VERSION 1.0)

add_executable(sdltest 
	src/main.cpp
	src/window.cpp
	src/input.cpp
	src/scene.cpp
	src/object.cpp
	src/component.cpp
	src/components/transform.cpp
	src/components/camera.cpp
	src/components/renderer.cpp
)

set_property(TARGET sdltest PROPERTY CXX_STANDARD 11)
set_property(TARGET sdltest PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_options(sdltest PRIVATE -Wall -Wextra -pedantic)

target_include_directories(sdltest PRIVATE include)

# libraries

# MinGW library if using it
if (MINGW)
	target_link_libraries(sdltest PRIVATE mingw32)
endif()

# SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(sdltest PRIVATE ${SDL2_LIBRARIES})

# GLAD
add_subdirectory(vendor/glad)
target_link_libraries(sdltest PRIVATE glad)
target_include_directories(sdltest PRIVATE vendor/glad/include)

# If using MinGW and not in Debug mode, use '-mwindows'
if (MINGW)
	set_property(TARGET sdltest PROPERTY WIN32_EXECUTABLE TRUE)
	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		set_property(TARGET sdltest PROPERTY WIN32_EXECUTABLE FALSE)
	endif()
endif()

# install
install(TARGETS sdltest DESTINATION bin)
