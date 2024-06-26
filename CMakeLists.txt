cmake_minimum_required(VERSION 3.27)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project(qwindowkit VERSION 1.1.1.0 LANGUAGES CXX)

# ----------------------------------
# Build Options
# ----------------------------------
option(QWINDOWKIT_BUILD_STATIC "Build static libraries" OFF)
option(QWINDOWKIT_BUILD_WIDGETS "Build widgets module" ON)
option(QWINDOWKIT_BUILD_QUICK "Build quick module" OFF)
option(QWINDOWKIT_BUILD_EXAMPLES "Build examples" ON)
option(QWINDOWKIT_BUILD_DOCUMENTATIONS "Build documentations" OFF)
option(QWINDOWKIT_INSTALL "Install library" ON)

option(QWINDOWKIT_ENABLE_QT_WINDOW_CONTEXT "Enable Qt Window Context anyway" OFF)
option(QWINDOWKIT_ENABLE_WINDOWS_SYSTEM_BORDERS "Enable system borders on Windows" ON)
option(QWINDOWKIT_ENABLE_STYLE_AGENT "Enable building style agent" ON)

include_directories(inc build/KSyntaxHighlighting build_win/KSyntaxHighlighting . ./KSyntaxHighlighting ./syntax-highlighting/src/lib ./build_win/syntax-highlighting/src/lib ./build/syntax-highlighting/src/lib) 

#[[

Detailed Introcuction to Configure Options:

`QWINDOWKIT_BUILD_DOCUMENTATIONS`
  - If you have installed `Doxygen`, you can ENABLE this option so that the documentations
    will also be built and installed.
  - If not, you can read the comments in `qdoc` style in `cpp` files to get detailed usages
    of the public APIs.

`QWINDOWKIT_ENABLE_WINDOWS_SYSTEM_BORDERS`
  - If you don't want the system borders on Windows 10/11, you can DISABLE this option.
  - If so, the Windows 10 top border issue will disappear. However, part of the client edge
    area will be occupied as the resizing margins.

`QWINDOWKIT_ENABLE_QT_WINDOW_CONTEXT`
  - If you want to use pure Qt emulated frameless implementation, you can ENABLE this option.
  - If so, all system native features will be lost.

`QWINDOWKIT_ENABLE_STYLE_AGENT`
  - Select whether to exclude the style component by DISABLING this option according to your
    requirements and your Qt version.

#]]

# ----------------------------------
# CMake Settings
# ----------------------------------
if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /manifest:no")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /manifest:no")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /manifest:no")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

    if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
        set(CMAKE_DEBUG_POSTFIX "d")
    endif()
elseif(MINGW)
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

if(QWINDOWKIT_INSTALL)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)
endif()

# ----------------------------------
# Project Variables
# ----------------------------------
set(QWINDOWKIT_VERSION ${PROJECT_VERSION})
set(QWINDOWKIT_INSTALL_NAME ${PROJECT_NAME})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# ----------------------------------
# Find basic dependencies
# ----------------------------------
find_package(qmsetup QUIET)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets QuickWidgets Qml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets QuickWidgets Qml)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

if(NOT TARGET qmsetup::library)
    # Modify this variable according to your project structure
    set(_source_dir ${CMAKE_CURRENT_SOURCE_DIR}/qmsetup)

    # Import install function
    include("${_source_dir}/cmake/modules/private/InstallPackage.cmake")

    # Install package in place
    set(_package_path)
    qm_install_package(qmsetup
        SOURCE_DIR ${_source_dir}
        BUILD_TYPE Release
        RESULT_PATH _package_path
    )

    # Find package again
    find_package(qmsetup REQUIRED PATHS ${_package_path})

    # Update import path
    set(qmsetup_DIR ${_package_path} CACHE PATH "" FORCE)
endif()

qm_import(Filesystem)
qm_init_directories()

# ----------------------------------
# Add source modules
# ----------------------------------
#add_subdirectory(src)
add_subdirectory(syntax-highlighting)

add_subdirectory(pureQt)

if(QWINDOWKIT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()