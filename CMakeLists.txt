cmake_minimum_required(VERSION 3.5)

project(MyQtProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Use clang-tidy if available 
find_program(CLANG_TIDY "clang-tidy")

if(CLANG_TIDY)
    message(STATUS "Found clang-tidy")
    set(CMAKE_CXX_CLANG_TIDY 
        clang-tidy 
        -warnings-as-errors=* 
        -checks=-*,readability-*,-readability-magic-numbers,-readability-isolate-declaration
    )
    set(CMAKE_C_CLANG_TIDY 
        clang-tidy 
        -warnings-as-errors=* 
        -checks=-*,readability-*,-readability-magic-numbers,-readability-isolate-declaration
    )
endif()

# Search for Boost static libraries only
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.65.0 COMPONENTS unit_test_framework QUIET)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets SerialPort REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Widgets Multimedia MultimediaWidgets SerialPort REQUIRED)

file(GLOB PROJECT_SOURCES
    "*.c"
    "*.cpp"
    "*.h"
    "*.hpp"
    "*.ui"
    "*.qrc"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MyQtProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(MyQtProject SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(MyQtProject
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MyQtProject PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
    Qt${QT_VERSION_MAJOR}::SerialPort
    )

set_target_properties(MyQtProject PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MyQtProject)
endif()
