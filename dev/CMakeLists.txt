cmake_minimum_required(VERSION 3.0.0)
project(1-UP VERSION 0.1)

include(CTest)
enable_testing()

add_compile_options(-Wno-c++11-extensions)
find_package(Curses REQUIRED)
add_executable(1-UP main.cpp Editor.cpp Buffer.cpp OSC.cpp Euc.cpp)
include_directories(${CURSES_INCLUDE_DIRS} /opt/homebrew/Cellar/liblo/0.31/include)
target_link_libraries(1-UP ${NCURSES_LIBRARIES} /opt/homebrew/Cellar/liblo/0.31/lib/liblo.dylib)

target_compile_options(1-UP PRIVATE -std=c++11)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)