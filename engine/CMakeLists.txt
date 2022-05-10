cmake_minimum_required(VERSION 3.10)

project(engine LANGUAGES CXX VERSION 1.0)

add_library(engine STATIC
	src/window.cpp
	src/input.cpp
	src/ecs/object.cpp
	src/ecs/sceneroot.cpp
	src/ecs/component.cpp
	src/ecs/components/transform.cpp
	src/ecs/components/renderer.cpp
	src/rendering/material.cpp
	src/rendering/shader.cpp
)

set_property(TARGET engine PROPERTY CXX_STANDARD 14)
set_property(TARGET engine PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_options(engine PRIVATE -Wall -Wextra -pedantic)

target_include_directories(engine PRIVATE include)

# libraries

# MinGW library if using it
if (MINGW)
	target_link_libraries(engine PUBLIC mingw32)
endif()

# SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(engine PUBLIC ${SDL2_LIBRARIES})
target_include_directories(engine PUBLIC ${SDL2_INCLUDE_DIRS})

# GLM
find_package(glm REQUIRED)
target_include_directories(engine PUBLIC ${GLM_INCLUDE_DIRS})

# GLAD
add_subdirectory(vendor/glad)
target_link_libraries(engine PUBLIC glad)
target_include_directories(engine PUBLIC vendor/glad/include)
