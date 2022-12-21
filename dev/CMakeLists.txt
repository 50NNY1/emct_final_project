cmake_minimum_required(VERSION 3.0.0)
project(finalproj VERSION 0.1.0)

include(CTest)
enable_testing()

find_package( Curses REQUIRED )
add_executable(finalproj main.cpp)
include_directories( ${CURSES_INCLUDE_DIRS} )
target_link_libraries( finalproj ${CURSES_LIBRARIES} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
