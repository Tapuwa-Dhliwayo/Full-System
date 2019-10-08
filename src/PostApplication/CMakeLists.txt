

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


#this builds an example program
set(EXECNAME PostApp)

find_package(MOOS 10)
find_package(pigpio REQUIRED)
find_package(Threads)

#what files are needed?
SET(SRCS PostApp.cpp  ../IMU/IMUSensor.cpp ../IMU/huff.cpp ../IMU/clogger.cpp )

include_directories( ${MOOS_INCLUDE_DIRS} ${MOOS_DEPEND_INCLUDE_DIRS} ${pigpio_INCLUDE_DIRS})
add_executable(${EXECNAME} ${SRCS} )
target_link_libraries(${EXECNAME} ${MOOS_LIBRARIES} ${MOOS_DEPEND_LIBRARIES} ${pigpio_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})  

