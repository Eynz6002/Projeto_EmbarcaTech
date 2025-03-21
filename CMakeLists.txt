# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Trabalho_EmbarcaTech C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

<<<<<<< HEAD
add_executable(Trabalho_EmbarcaTech Trabalho_EmbarcaTech.c inc/ssd1306_i2c.c)
=======
<<<<<<< HEAD
add_executable(Trabalho_EmbarcaTech Trabalho_EmbarcaTech.c )
=======
add_executable(Trabalho_EmbarcaTech Trabalho_EmbarcaTech.c inc/ssd1306_i2c.c)
>>>>>>> 1000fa0 (Atualização do para fase de nivelamento)
>>>>>>> 708134d669d8165a8b70a85f06ee337ee9311309

pico_set_program_name(Trabalho_EmbarcaTech "Trabalho_EmbarcaTech")
pico_set_program_version(Trabalho_EmbarcaTech "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Trabalho_EmbarcaTech 0)
pico_enable_stdio_usb(Trabalho_EmbarcaTech 1)

# Add the standard library to the build
target_link_libraries(Trabalho_EmbarcaTech
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(Trabalho_EmbarcaTech PRIVATE
<<<<<<< HEAD
  ${CMAKE_CURRENT_LIST_DIR}
=======
<<<<<<< HEAD
        ${CMAKE_CURRENT_LIST_DIR}
=======
  ${CMAKE_CURRENT_LIST_DIR}
>>>>>>> 1000fa0 (Atualização do para fase de nivelamento)
>>>>>>> 708134d669d8165a8b70a85f06ee337ee9311309
)

# Add any user requested libraries
target_link_libraries(Trabalho_EmbarcaTech 
<<<<<<< HEAD
=======
<<<<<<< HEAD
        
        )

pico_add_extra_outputs(Trabalho_EmbarcaTech)

=======
>>>>>>> 708134d669d8165a8b70a85f06ee337ee9311309
        hardware_pwm
        hardware_clocks
        hardware_i2c
        )

pico_add_extra_outputs(Trabalho_EmbarcaTech)
<<<<<<< HEAD
=======
>>>>>>> 1000fa0 (Atualização do para fase de nivelamento)
>>>>>>> 708134d669d8165a8b70a85f06ee337ee9311309
