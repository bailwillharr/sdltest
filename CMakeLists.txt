cmake_minimum_required(VERSION 3.10)

project(SDLTest LANGUAGES CXX VERSION 1.0)

add_executable(sdltest 
	src/main.cpp
	src/window.cpp
	src/input.cpp
)

set_property(TARGET sdltest PROPERTY CXX_STANDARD 11)
set_property(TARGET sdltest PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_options(sdltest PRIVATE -Wall -Wextra -pedantic)

target_include_directories(sdltest PRIVATE include)

# libraries

# SDL2
find_library(LIB_SDL2 SDL2)
target_link_libraries(sdltest PRIVATE ${LIB_SDL2})

# GLAD
add_subdirectory(vendor/glad)
target_link_libraries(sdltest PRIVATE glad)
target_include_directories(sdltest PRIVATE vendor/glad/include)

# install
install(TARGETS sdltest DESTINATION bin)
