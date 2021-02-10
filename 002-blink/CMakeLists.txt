cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(002-blink)

pico_sdk_init()

add_executable(002-blink
    blink.c
)

# enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(002-blink)

target_link_libraries(002-blink pico_stdlib)
