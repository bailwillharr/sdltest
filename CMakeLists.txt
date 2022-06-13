cmake_minimum_required(VERSION 3.12)

set(SDLTEST_VERSION_MAJOR 0)
set(SDLTEST_VERSION_MINOR 2)

project(sdltest LANGUAGES CXX
	VERSION "${SDLTEST_VERSION_MAJOR}.${SDLTEST_VERSION_MINOR}"
)

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

configure_file(config.h.in config.h)
target_include_directories(sdltest PUBLIC ${CMAKE_CURRENT_BINARY_DIR})



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
add_subdirectory(libraries/SDL)
target_include_directories(sdltest PUBLIC libraries/SDL/include)
target_link_libraries(sdltest PUBLIC SDL2::SDL2)
target_link_libraries(sdltest PUBLIC SDL2::SDL2main)
add_custom_command(
	TARGET sdltest PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:sdltest>)

# GLM:
add_subdirectory(libraries/glm)
target_include_directories(sdltest PUBLIC libraries/glm)

# GLAD:
set(GLAD_PROFILE "core" CACHE INTERNAL "" FORCE)
set(GLAD_API "gl=3.3" CACHE INTERNAL "" FORCE)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(GLAD_GENERATOR "c-debug" CACHE INTERNAL "" FORCE)
else()
	set(GLAD_GENERATOR "c" CACHE INTERNAL "" FORCE)
endif()
set(GLAD_SPEC "gl" CACHE INTERNAL "" FORCE)
add_subdirectory(libraries/glad)
target_link_libraries(sdltest PUBLIC glad)
target_include_directories(sdltest PUBLIC libraries/glad/include)



# linking options:

# If not in Debug mode, use '-mwindows'
#set_property(TARGET sdltest PROPERTY WIN32_EXECUTABLE TRUE)
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
if (WIN32)
	install(TARGETS SDL2 RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
endif(WIN32)
