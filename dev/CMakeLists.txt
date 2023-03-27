cmake_minimum_required(VERSION 3.0.0)
project(finalproj VERSION 0.1.0)

include(CTest)
enable_testing()
add_compile_options(-Wno-c++11-extensions)

find_package(Curses REQUIRED)
find_library(PANEL_LIBRARY panel)
add_executable(finalproj main.cpp Editor.cpp Buffer.cpp)
include_directories(${CURSES_INCLUDE_DIRS})
target_link_libraries(finalproj ${NCURSES_LIBRARIES} ${PANEL_LIBRARY} -lpanel)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)