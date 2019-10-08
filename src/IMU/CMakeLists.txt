CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(pigpio REQUIRED)

set(EXECNAME IMUApp)

SET(SRCS IMUApp.cpp IMUSensor.cpp huff.cpp clogger.cpp)

include_directories( ${pigpio_INCLUDE_DIRS})

add_executable(${EXECNAME} ${SRCS})
add_executable(testing arduino.cpp rs232.c)

target_link_libraries(${EXECNAME} ${pigpio_LIBRARY})
target_link_libraries(testing -lpthread)
