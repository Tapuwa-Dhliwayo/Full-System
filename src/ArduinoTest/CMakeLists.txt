

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


#this builds an example program
set(EXECNAME ard_test)

find_package(MOOS 10)

#what files are needed?
SET(SRCS arduino_test.cpp rs232.c)


include_directories(  ${MOOS_INCLUDE_DIRS} ${MOOS_DEPEND_INCLUDE_DIRS})
add_executable(${EXECNAME} ${SRCS} )
target_link_libraries(${EXECNAME} ${MOOS_LIBRARIES} ${MOOS_DEPEND_LIBRARIES})

