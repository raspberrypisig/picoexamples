cmake_minimum_required(VERSION 3.12)

get_filename_component(PICOSDKIMPORT ${CMAKE_SOURCE_DIR} DIRECTORY)

include(${PICOSDKIMPORT}/001-include/pico_sdk_import.cmake)

get_filename_component(THISPROJECTNAME ${CMAKE_SOURCE_DIR} NAME)

project(${THISPROJECTNAME})

pico_sdk_init()

#string(REGEX REPLACE "^[0-9-]" "" MAINSOURCE ${PROJECT_NAME})

add_executable(${PROJECT_NAME}
    main.c
)

# enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    hardware_pwm    
)




