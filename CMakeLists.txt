cmake_minimum_required(VERSION 3.10)
project(GestureControl)

include(CTest)
enable_testing()

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(GestureControl main.cpp  "gestureControlHelper.cpp")

target_link_libraries( GestureControl ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)