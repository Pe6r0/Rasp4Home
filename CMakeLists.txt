cmake_minimum_required(VERSION 3.5)

project(Rasp4Home VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:\\Programs\\Qt\\5.15.2\\winrt_x64_msvc2019")
set(Qt5_DIR "C:\\Programs\\Qt\\5.15.2\\winrt_x86_msvc2019\\lib\\cmake\\Qt5")

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)

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

set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

QT_WRAP_UI( PROJECT_SOURCES ${UIS} )

add_executable(Rasp4Home ${PROJECT_SOURCES})

target_link_libraries(Rasp4Home PRIVATE Qt5::Widgets)
target_link_libraries(Rasp4Home PRIVATE Qt5::Network)

