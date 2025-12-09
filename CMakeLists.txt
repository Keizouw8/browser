cmake_minimum_required(VERSION 3.24)
project(browser VERSION 1.0.0 LANGUAGES CXX)

# CMake settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_SHARED_LIBS OFF)

set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)
set(YLT_BUILD_TEST OFF)
set(YLT_BUILD_EXAMPLE OFF)
set(YLT_BUILD_BENCHMARK OFF)

# Output config
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/browser")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Packages
include(FetchContent)

FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG        3.0.2
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
	yalantinglibs
	GIT_REPOSITORY https://github.com/alibaba/yalantinglibs.git
	GIT_TAG        0.5.6
)
FetchContent_MakeAvailable(yalantinglibs)

# SFML3 has a known issue on macOS where <iostream> is missing in some files.
if(APPLE)
    foreach(target sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
        if(TARGET ${target})
            target_compile_options(${target} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-include> $<$<COMPILE_LANGUAGE:CXX>:iostream>)
        endif()
    endforeach()
endif()

# Setting source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in 'src' directory!")
endif()

# Making executables
if(WIN32)
	add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})
elseif(APPLE)
	add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES} ${HEADERS})
	set_target_properties(${PROJECT_NAME} PROPERTIES
		MACOSX_BUNDLE_BUNDLE_NAME "browser"
		MACOSX_BUNDLE_GUI_IDENTIFIER "tech.madum.browser"
		MACOSX_BUNDLE_INFO_STRING "A minimalistic C++ browser with workspaces"
		MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in"
	)
else()
	add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
endif()

find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	SFML::Graphics
	SFML::Audio
	SFML::Window
	SFML::System
	yalantinglibs::yalantinglibs
    Threads::Threads
)

# Copying assets and config directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_CURRENT_SOURCE_DIR}/assets"
	"$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
	COMMENT "Copying assets to build directory..."
)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_CURRENT_SOURCE_DIR}/config"
	"$<TARGET_FILE_DIR:${PROJECT_NAME}>/config"
	COMMENT "Copying config to build directory..."
)
