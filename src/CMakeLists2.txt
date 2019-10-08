set(PROJECTNAME MYMOOSComms)

project(${PROJECTNAME})

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()


CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

add_subdirectory(PostApplication)
add_subdirectory(ReceiveApplication)
add_subdirectory(ArduinoTest)
