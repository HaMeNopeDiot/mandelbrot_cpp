cmake_minimum_required(VERSION 3.16)

project(mandelbrot_cpp LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Concurrent Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Concurrent Gui)

add_executable(mandelbrot_cpp
  src/do_mndlbrt.hpp
  src/is_mndlbrt.hpp
  src/gt_mndlbrt.hpp
  src/mndlbrt_color.hpp
  src/main.cpp
)
target_link_libraries(mandelbrot_cpp Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Gui
)

include(GNUInstallDirs)
install(TARGETS mandelbrot_cpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
