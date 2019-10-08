CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(pigpio REQUIRED)

set(EXECNAME gpsApp)

SET(SRCS gpsApp.cpp)

include_directories( ${pigpio_INCLUDE_DIRS})

add_executable(${EXECNAME} ${SRCS})

target_link_libraries(${EXECNAME} ${pigpio_LIBRARY})
