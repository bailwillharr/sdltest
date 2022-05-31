cmake_minimum_required(VERSION 3.12)

project(sdltest LANGUAGES CXX VERSION 1.0)

add_executable(sdltest 
	"src/main.cpp"
	"src/window.cpp"
	"src/input.cpp"
	"src/ecs/object.cpp"
	"src/ecs/sceneroot.cpp"
	"src/ecs/component.cpp"
	"src/ecs/components/transform.cpp"
	"src/ecs/components/renderer.cpp"
	"src/ecs/components/camera.cpp"
	"src/rendering/mesh.cpp"
	"src/resources/shader.cpp"
	"src/resource_manager.cpp"
	"src/resource.cpp"
	"src/window.hpp"
	"src/input.hpp"
	"src/ecs/component.hpp"
	"src/ecs/object.hpp"
	"src/ecs/sceneroot.hpp"
	"src/ecs/components/camera.hpp"
	"src/ecs/components/renderer.hpp"
	"src/ecs/components/transform.hpp"
	"src/inputs/keyboard.hpp"
	"src/inputs/mouse.hpp"
	"src/rendering/mesh.hpp"
	"src/resource_manager.hpp"
	"src/resource.hpp"
	"src/resources/shader.hpp"
)

# compiling options:

set_property(TARGET sdltest PROPERTY CXX_STANDARD 17)
set_property(TARGET sdltest PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(sdltest PUBLIC src)

# libraries:

# MinGW library if using it
if (MINGW)
	target_link_libraries(sdltest PUBLIC mingw32)
endif()

# SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(sdltest PUBLIC ${SDL2_LIBRARIES})
target_include_directories(sdltest PUBLIC ${SDL2_INCLUDE_DIRS})

# GLM
find_package(glm REQUIRED)
target_include_directories(sdltest PUBLIC ${GLM_INCLUDE_DIRS})

# GLAD
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