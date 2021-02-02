cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

get_filename_component(THISPROJECTNAME ${CMAKE_SOURCE_DIR} NAME)

project(${THISPROJECTNAME})

pico_sdk_init()

#string(REGEX REPLACE "^[0-9-]" "" MAINSOURCE ${PROJECT_NAME})

add_executable(${PROJECT_NAME}
    main.c
)

add_library(kiss_fftr kiss_fftr.c)
add_library(kiss_fft kiss_fft.c)

target_link_libraries(kiss_fftr kiss_fft)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
	hardware_adc
	hardware_dma
	kiss_fftr    
)





