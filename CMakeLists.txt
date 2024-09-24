cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(calculator_project)

pico_sdk_init()

add_executable(calculator
    calculator.c
)

target_link_libraries(calculator pico_stdlib)

pico_enable_stdio_usb(calculator 1)
pico_enable_stdio_uart(calculator 0)

pico_add_extra_outputs(calculator)
