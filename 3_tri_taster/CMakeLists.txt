cmake_minimum_required (VERSION 2.6)
project (RenderTutorial)
find_package(Eigen3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
file(GLOB SOURCES *.h *.cpp)
INCLUDE_DIRECTORIES ( "/usr/local/include/" )
add_executable(${PROJECT_NAME} ${SOURCES})