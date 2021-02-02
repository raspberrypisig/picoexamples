cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

get_filename_component(THISPROJECTNAME ${CMAKE_SOURCE_DIR} NAME)

project(${THISPROJECTNAME})

pico_sdk_init()

#string(REGEX REPLACE "^[0-9-]" "" MAINSOURCE ${PROJECT_NAME})

add_executable(${PROJECT_NAME}
    main.c
)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} pico_stdlib)



