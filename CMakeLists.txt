cmake_minimum_required(VERSION 3.12)

project(sdltest LANGUAGES CXX VERSION 1.0)

add_executable(sdltest 
	"src/main.cpp"
	"src/game.cpp"
	"src/window.cpp"
	"src/input.cpp"
	"src/object.cpp"
	"src/sceneroot.cpp"
	"src/component.cpp"
	"src/components/custom.cpp"
	"src/components/transform.cpp"
	"src/components/renderer.cpp"
	"src/components/camera.cpp"
	"src/resources/mesh.cpp"
	"src/resources/shader.cpp"
	"src/resources/texture.cpp"
	"src/resource_manager.cpp"
	"src/resource.cpp"

	"src/game.hpp"
	"src/window.hpp"
	"src/input.hpp"
	"src/component.hpp"
	"src/components/custom.hpp"
	"src/object.hpp"
	"src/sceneroot.hpp"
	"src/components/camera.hpp"
	"src/components/renderer.hpp"
	"src/components/transform.hpp"
	"src/inputs/keyboard.hpp"
	"src/inputs/mouse.hpp"
	"src/resources/mesh.hpp"
	"src/resource_manager.hpp"
	"src/resource.hpp"
	"src/resources/shader.hpp"
	"src/resources/texture.hpp"
)

# compiling options:

set_property(TARGET sdltest PROPERTY CXX_STANDARD 20)
set_property(TARGET sdltest PROPERTY CXX_STANDARD_REQUIRED ON)

if (MSVC)
	target_compile_options(sdltest PUBLIC /W3)
	# Build in parallel under Visual Studio. Not enabled by default.
	target_compile_options(sdltest INTERFACE "/MP")
endif()

target_include_directories(sdltest PUBLIC src)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(sdltest PUBLIC SDLTEST_DEBUG)
endif()



# libraries:

# MinGW library if using it
if (MINGW)
	target_link_libraries(sdltest PUBLIC mingw32)
endif()

# SDL2:
set(SDL2_DISABLE_INSTALL ON CACHE INTERNAL "" FORCE)
set(SDL_SHARED ON CACHE INTERNAL "" FORCE)
set(SDL_STATIC OFF CACHE INTERNAL "" FORCE)
set(SDL_TEST OFF CACHE INTERNAL "" FORCE)
add_subdirectory(vendor/SDL)

#include
target_include_directories(sdltest PUBLIC vendor/SDL/include)

# linking
target_link_libraries(sdltest PUBLIC SDL2::SDL2)
target_link_libraries(sdltest PUBLIC SDL2::SDL2main)

# copy DLL
add_custom_command(
	TARGET sdltest PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:sdltest>)
install(TARGETS SDL2 RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

# GLM:
add_subdirectory(vendor/glm)
target_include_directories(sdltest PUBLIC vendor/glm)

# GLAD:
add_subdirectory(vendor/glad)
target_link_libraries(sdltest PUBLIC glad)
target_include_directories(sdltest PUBLIC vendor/glad/include)



# linking options:

# If not in Debug mode, use '-mwindows'
set_property(TARGET sdltest PROPERTY WIN32_EXECUTABLE TRUE)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set_property(TARGET sdltest PROPERTY WIN32_EXECUTABLE FALSE)
endif()

add_custom_command(
	TARGET sdltest POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E create_symlink
	${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:sdltest>/res)

# install:
install(TARGETS sdltest DESTINATION bin)
install(DIRECTORY res/ DESTINATION share/sdltest)
