cmake_minimum_required(VERSION 2.8.3)

# define a macro that helps defining an option
macro(game_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# Set a default build type and module path if none was provided
game_set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")
game_set_option(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules" STRING "The path to the cmake modules. This path must contain the FindSFML.cmake and FindTGUI.cmake files")

# Choose between linking to SFML statically or dynamically
# Note that you must link to TGUI the same way
game_set_option(SFML_TGUI_STATIC TRUE BOOL "TRUE to link to SFML/TGUI statically, FALSE to link dynamically")

# Project name
project(game)

# Project version
set(MAJOR_VERSION 0)
set(MAJOR_VERSION 1)

# Disable deprecated warnings from SFML
add_definitions(-DSFML_NO_DEPRECATED_WARNINGS)

# Find sfml and tgui
if (SFML_OS_WINDOWS)
    find_package(SFML 2 COMPONENTS main system window graphics audio network REQUIRED)
    find_package(TGUI 0.7 REQUIRED)
#elseif (SFML_OS_ANDROID)
#    find_host_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)
#    find_host_package(TGUI 0.7 REQUIRED)
else()
    find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)
    find_package(TGUI 0.7 REQUIRED)
endif()

# FindSFML couldn't find SFML
if (NOT SFML_FOUND)
    set(SFML_ROOT "" CACHE PATH "SFML root directory")
    message(FATAL_ERROR "CMake couldn't find SFML. Set the SFML_ROOT entry to SFML's root directory (containing \"include\" and \"lib\" directories).")
endif()

# FindTGUI couldn't find TGUI
if (NOT TGUI_FOUND)
    set(TGUI_ROOT "" CACHE PATH "TGUI root directory")
    message(FATAL_ERROR "CMake couldn't find TGUI. Set the TGUI_ROOT entry to TGUI's root directory (containing \"include\" and \"lib\" directories).")
endif()

# Add the sfml and tgui include directories
include_directories(${SFML_INCLUDE_DIR} ${TGUI_INCLUDE_DIR})

# The source code
add_subdirectory(src)

# Game executable
add_executable(game)

# Link against sfml and tgui libraries
set(GAME_EXT_LIBS ${SFML_LIBARIES} ${TGUI_LIBRARY})
if (SFML_TGUI_STATIC)
    add_definitions(-DSFML_STATIC)
    set(GAME_EXT_LIBS ${GAME_EXT_LIBS} ${SFML_DEPENDENCIES})
endif()
target_link_libraries(game ${GAME_SRC} ${GAME_EXT_LIBS})
