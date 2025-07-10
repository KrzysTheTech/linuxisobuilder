# Set the minimum required version of CMake and project name.
cmake_minimum_required(VERSION 3.4.1)
project(LinuxIsoBuilderGUI CXX)

# Set the C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the project version, allowing it to be overridden by the build environment.
set(PROJECT_VERSION "0.1.0-alpha1-local" CACHE STRING "Project version string")
message(STATUS "Project Version: ${PROJECT_VERSION}")

# Find PkgConfig to help locate system libraries.
find_package(PkgConfig REQUIRED)

# Use PkgConfig to find the GTKmm-4.0 library.
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

# Add the GTKmm header directories to the include path.
include_directories(${GTKMM_INCLUDE_DIRS})

# Define the executable target with platform-specific settings.
if(WIN32)
    add_executable(linuxisobuilder-gui WIN32 main.gui.cpp)
else()
    add_executable(linuxisobuilder-gui main.gui.cpp)
    if(APPLE)
        set_target_properties(linuxisobuilder-gui PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_GUI_IDENTIFIER "tech.krzys.linuxisobuilder.gui"
        )
    endif()
endif()

# Pass the version string to the source code as a preprocessor definition.
target_compile_definitions(linuxisobuilder-gui PRIVATE "PROJECT_VERSION=\"${PROJECT_VERSION}\"")

# Link the executable against the GTKmm libraries.
target_link_libraries(linuxisobuilder-gui ${GTKMM_LIBRARIES})
