CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(pigpio REQUIRED)

set(EXECNAME1 unitTests)
set(EXECNAME2 funcTests)

set(SRCS1 unitTests.cpp ../IMU/huff.cpp)
set(SRCS2 funcTests.cpp ../IMU/IMUSensor.cpp ../IMU/huff.cpp ../IMU/clogger.cpp)

include_directories( ${pigpio_INCLUDE_DIRS})

add_executable(${EXECNAME1} ${SRCS1})

target_link_libraries(${EXECNAME1} ${pigpio_LIBRARY})

add_executable(${EXECNAME2} ${SRCS2})

target_link_libraries(${EXECNAME2} ${pigpio_LIBRARY})
