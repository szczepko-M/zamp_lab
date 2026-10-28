cmake_minimum_required(VERSION 3.10)

set(PROJ_NAME "cmds_interpreter")
project(${PROJ_NAME} CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -pedantic)

add_subdirectory(plugin)

include_directories(${PROJECT_SOURCE_DIR}/inc)
add_executable(${PROJ_NAME}
  src/main.cpp
  src/LibInterface.cpp
  src/Set4LibInterfaces.cpp)

target_link_libraries(${PROJ_NAME} ${CMAKE_DL_LIBS})

# Program szuka wtyczek w podkatalogu "plugin" lezacym obok pliku wykonywalnego
# (niezaleznie od biezacego katalogu roboczego).
set_target_properties(${PROJ_NAME} PROPERTIES
  BUILD_RPATH "\$ORIGIN/plugin"
  BUILD_WITH_INSTALL_RPATH OFF)

add_dependencies(${PROJ_NAME} Interp4Move Interp4Rotate Interp4Set Interp4Pause)

configure_file(${PROJECT_SOURCE_DIR}/opis_dzialan.cmd
               ${CMAKE_BINARY_DIR}/opis_dzialan.cmd COPYONLY)
file(COPY ${PROJECT_SOURCE_DIR}/examples DESTINATION ${CMAKE_BINARY_DIR})

add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo " Utworzony zostal program:  ${PROJ_NAME}"
    COMMAND ${CMAKE_COMMAND} -E echo ""
  )
