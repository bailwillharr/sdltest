cmake_minimum_required(VERSION 3.10)

project(SDLTest LANGUAGES CXX VERSION 1.0)

add_executable(sdltest 
	src/main.cpp
)

# compiling options:

set_property(TARGET sdltest PROPERTY CXX_STANDARD 14)
set_property(TARGET sdltest PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_options(sdltest PRIVATE -Wall -Wextra -pedantic)

target_include_directories(sdltest PRIVATE include)

# project libraries:

add_subdirectory(engine)
target_link_libraries(sdltest PRIVATE engine)
target_include_directories(sdltest PRIVATE engine/include)

# external libraries:



# linking options:

# If using MinGW and not in Debug mode, use '-mwindows'
if (MINGW)
	set_property(TARGET sdltest PROPERTY WIN32_EXECUTABLE TRUE)
	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		set_property(TARGET sdltest PROPERTY WIN32_EXECUTABLE FALSE)
	endif()
endif()

# install:

install(TARGETS sdltest DESTINATION bin)
