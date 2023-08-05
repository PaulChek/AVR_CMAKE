cmake_minimum_required(VERSION 3.27.1)
# Use AVR GCC toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)
set(F_CPU 8000000)
set(MCU atmega32a)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-g -Os -mmcu=${MCU} -DF_CPU=${F_CPU})

#project name
project(blinky C CXX ASM)



set(CMAKE_CXX_STANDARD 99)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_subdirectory(src)


add_custom_target(
    HEXandFLASH
    COMMAND avr-objcopy -O ihex
    ${CMAKE_BINARY_DIR}/src/${PROJECT_NAME} ${CMAKE_BINARY_DIR}/src/${PROJECT_NAME}.hex #genrate hex file
    COMMAND avrdude -c usbasp -p ${MCU} -P usb  -U flash:w:${CMAKE_BINARY_DIR}/src/${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}
    )