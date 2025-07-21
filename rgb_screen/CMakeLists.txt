cmake_minimum_required(VERSION 3.13)

# Import pico-sdk
include(pico_sdk_import.cmake)

# Set project name and languages
project(rgb_screen C CXX ASM)

# Set language standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# Define the executable from source files
add_executable(rgb_screen
    src/main.c
    src/lv_port_disp.c
    src/turtle.c
    src/lv_screen.c
    src/motor.c
    src/low_pass_filter.c
    assets/battery/battery_low.c
    assets/battery/battery_25.c
    assets/battery/battery_50.c
    assets/battery/battery_75.c
    assets/battery/battery_full.c
    screen/battery.c


)

# Include the local header directory
target_include_directories(rgb_screen PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_SOURCE_DIR}/screen
)

# Enable standard I/O via USB and UART
pico_enable_stdio_usb(rgb_screen 1)
pico_enable_stdio_uart(rgb_screen 1)

set(LV_CONF_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/conf/lv_conf.h
    CACHE STRING "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../lib/lvgl ${CMAKE_BINARY_DIR}/lvgl)

# Link only to the Pico standard library
target_link_libraries(rgb_screen
    pico_stdlib
    lvgl
    hardware_spi
    hardware_timer
    hardware_adc
    hardware_irq
    hardware_pwm

)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Generate .uf2, .bin, and .hex files
pico_add_extra_outputs(rgb_screen)
