cmake_minimum_required(VERSION 3.17)
project(imgServer)

set(CMAKE_CXX_STANDARD 14)
FIND_PACKAGE(Boost REQUIRED COMPONENTS system thread regex)
FIND_PACKAGE(Boost)
find_package(OpenCV REQUIRED )
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    include_directories( ${OpenCV_INCLUDE_DIRS} )
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

add_executable(imgServer main.cpp)
TARGET_LINK_LIBRARIES(imgServer ${USED_LIBS} Boost::boost ${OpenCV_LIBS})