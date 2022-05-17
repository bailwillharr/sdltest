cmake_minimum_required(VERSION 3.10)

project(SDLTest LANGUAGES CXX VERSION 1.0)

add_executable(sdltest 
	src/main.cpp
)

# compiling options:

set_property(TARGET sdltest PROPERTY CXX_STANDARD 14)
set_property(TARGET sdltest PROPERTY CXX_STANDARD_REQUIRED ON)

#target_compile_options(sdltest PRIVATE -Wall -Wextra -pedantic)

target_include_directories(sdltest PRIVATE include)

# project libraries:

add_subdirectory(engine)
target_link_libraries(sdltest PRIVATE engine)
target_include_directories(sdltest PRIVATE engine/include)

# external libraries:



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