cmake_minimum_required(VERSION 3.10)

project(SDLTest LANGUAGES CXX VERSION 1.0)
add_executable(sdltest src/main.cpp)

target_compile_options(sdltest PRIVATE -Wall)

set_target_properties(sdltest PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED ON)

# libraries
find_library(LIB_SDL2 SDL2)
target_link_libraries(sdltest PRIVATE ${LIB_SDL2})

# install
install(TARGETS sdltest DESTINATION bin)
