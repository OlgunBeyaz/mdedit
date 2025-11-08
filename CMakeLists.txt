cmake_minimum_required(VERSION 3.16)
project(mdedit VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SRC
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
)

qt_standard_project_setup()

qt_add_executable(mdedit ${SRC})
target_include_directories(mdedit PRIVATE src)
target_link_libraries(mdedit PRIVATE Qt6::Widgets)
