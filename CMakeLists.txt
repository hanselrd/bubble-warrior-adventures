cmake_minimum_required(VERSION 2.8)

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

# Declare SFML_ROOT and TGUI_ROOT
game_set_option(SFML_ROOT "" PATH "SFML root directory")
game_set_option(TGUI_ROOT "" PATH "TGUI root directory")

# Choose between linking to SFML statically or dynamically
# Note that you must link to TGUI the same way
game_set_option(USE_STATIC_LIBRARIES TRUE BOOL "TRUE to link to SFML/TGUI statically, FALSE to link dynamically")

# Project name
project(game)

# Project version
set(MAJOR_VERSION 0)
set(MAJOR_VERSION 1)

# Require C++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Disable deprecated warnings from SFML
add_definitions(-DSFML_NO_DEPRECATED_WARNINGS)

# Enable header only mode for pugixml
add_definitions(-DPUGIXML_HEADER_ONLY)

# Include the configuration file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

if (SFML_OS_WINDOWS)
	if (USE_STATIC_LIBRARIES)
	    set(SFML_STATIC_LIBRARIES TRUE)
	endif()
endif()

# Find sfml, tgui and python3
find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)
find_package(TGUI REQUIRED)
set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs 3 REQUIRED)
find_package(Boost 1.58 REQUIRED)

# FindSFML couldn't find SFML
if (NOT SFML_FOUND)
    set(SFML_ROOT "" CACHE PATH "SFML root directory" FORCE)
    message(FATAL_ERROR "CMake couldn't find SFML. Set the SFML_ROOT entry to SFML's root directory (containing \"include\" and \"lib\" directories).")
endif()

# FindTGUI couldn't find TGUI
if (NOT TGUI_FOUND)
    set(TGUI_ROOT "" CACHE PATH "TGUI root directory" FORCE)
    message(FATAL_ERROR "CMake couldn't find TGUI. Set the TGUI_ROOT entry to TGUI's root directory (containing \"include\" and \"lib\" directories).")
endif()

# Add the sfml and tgui include directories
include_directories(${SFML_INCLUDE_DIR} ${TGUI_INCLUDE_DIR} ${PYTHON_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/extlibs/cereal/include)
include_directories(${PROJECT_SOURCE_DIR}/extlibs/cppcodec)
include_directories(${PROJECT_SOURCE_DIR}/extlibs/pugixml/src)
include_directories(${PROJECT_SOURCE_DIR}/extlibs/pybind11/include)

# Add all the source files
file(GLOB GAME_SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Game executable
add_executable(${PROJECT_NAME} ${GAME_SRC})

# Link against libraries
set(GAME_EXT_LIBS ${SFML_LIBRARIES} ${TGUI_LIBRARY} ${PYTHON_LIBRARIES})
if (USE_STATIC_LIBRARIES)
    set(GAME_EXT_LIBS ${GAME_EXT_LIBS} ${SFML_DEPENDENCIES})
endif()
target_link_libraries(${PROJECT_NAME} ${GAME_EXT_LIBS})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Copy sfml and tgui .dlls
if (SFML_OS_WINDOWS)
    if (NOT USE_STATIC_LIBRARIES)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${SFML_ROOT}/bin" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
        file(GLOB TGUI_DLLS "${TGUI_ROOT}/lib/*.dll")
        foreach (dll_i ${TGUI_DLLS})
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy ${dll_i} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
        endforeach(dll_i)
    endif()
endif()

# Copy assets directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/assets" ${PROJECT_BINARY_DIR}/assets

    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/assets" $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
