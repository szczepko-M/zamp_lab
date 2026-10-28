cmake_minimum_required(VERSION 3.10)

project(plugins_4_program CXX)

include_directories(${PROJECT_SOURCE_DIR}/inc ${PROJECT_SOURCE_DIR}/../inc)

set(PLUGIN_COMMANDS Move Rotate Set Pause)

foreach(CMD ${PLUGIN_COMMANDS})
  set(TARGET_NAME Interp4${CMD})
  add_library(${TARGET_NAME} MODULE src/Interp4${CMD}.cpp)
  set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "lib")
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo " Utworzony zostal plugin:  libInterp4${CMD}.so"
  )
endforeach()
