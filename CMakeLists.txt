cmake_minimum_required(VERSION 3.24)

project(browser VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_SHARED_LIBS OFF)

set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)
set(YLT_BUILD_TEST OFF)
set(YLT_BUILD_EXAMPLE OFF)
set(YLT_BUILD_BENCHMARK OFF)

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

find_package(Threads REQUIRED)

set(SOURCES main.cpp)

if(WIN32)
	add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
elseif(APPLE)
	add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES})

	set_target_properties(${PROJECT_NAME} PROPERTIES
		MACOSX_BUNDLE_BUNDLE_NAME "browser"
		MACOSX_BUNDLE_GUI_IDENTIFIER "cc.madum.browser"
		MACOSX_BUNDLE_INFO_STRING "A minimalistic C++ browser with workspaces"
	)
else()
	add_executable(${PROJECT_NAME} ${SOURCES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
	SFML::Graphics
	SFML::Audio
	SFML::Window
	SFML::System
	yalantinglibs::yalantinglibs
    Threads::Threads
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_CURRENT_SOURCE_DIR}/assets"
	"$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
	COMMENT "Copying assets to build directory..."
)
