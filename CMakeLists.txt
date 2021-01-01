cmake_minimum_required(VERSION 3.5)

project(Rasp4Home LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core5Compat REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        weather.cpp
        weather.h
        restconnector.cpp
        restconnector.h
        qrcodeservice.cpp
        qrcodeservice.h
        wiki.cpp
        wiki.h
        utils.cpp
        utils.h
)

set ( UIS main.ui weather.ui wiki.ui)

QT_WRAP_UI( PROJECT_SOURCES ${UIS} )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Rasp4Home
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Rasp4Home SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Rasp4Home
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Rasp4Home PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Rasp4Home PRIVATE Qt6::Network)
target_link_libraries(Rasp4Home PRIVATE Qt6::Core5Compat)

