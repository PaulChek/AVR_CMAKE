#add_executable(${PROJECT_NAME}   main.c)

# adding custom target cuz avr mcu fails run programm with .S files
add_custom_target(${PROJECT_NAME}
WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}/src
COMMAND avr-gcc -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} 
 main.c RotateBits.S ../spiI2cuart/*.c ../spiI2cuart/*.h
-o ${CMAKE_BINARY_DIR}/src/${PROJECT_NAME}
)