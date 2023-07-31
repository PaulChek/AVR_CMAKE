cmake_minimum_required(VERSION 3.27.1)
# Use AVR GCC toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)
set(MCU atmega32a)

add_compile_options( -mmcu=${MCU} -Os )

project(blinky)
add_subdirectory(src)


add_custom_target(
    HEXandFLASH
    COMMAND avr-objcopy  -O ihex -j .text -j .data 
    ${CMAKE_BINARY_DIR}/src/${PROJECT_NAME} ${CMAKE_BINARY_DIR}/src/${PROJECT_NAME}.hex #genrate hex file
    COMMAND avrdude -c usbasp -p ${MCU} -P usb  #flash to MCU
    -U flash:w:${CMAKE_BINARY_DIR}/src/${PROJECT_NAME}.hex:i
    )