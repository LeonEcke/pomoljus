cmake_minimum_required(VERSION 3.22)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(extern/pico-sdk/pico_sdk_init.cmake)

# Setup project
project(pomoljus
	VERSION 0.1.1
	DESCRIPTION "Main Firmware for the Pomoljus"
	LANGUAGES C CXX
	)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Create main executable
add_executable(main main.cpp)

set_target_properties(	main PROPERTIES
							C_STANDARD 17
							CXX_STANDARD_REQUIRED 17)

# Add custom libraries.
# Add generated PIO executable to sk6812Driver.
add_subdirectory(src)
pico_generate_pio_header(sk6812Driver ${CMAKE_CURRENT_LIST_DIR}/pio/sk6812.pio)

# Link libraries to main
target_link_libraries(	main
						PRIVATE
						sk6812Driver
						pico_stdlib
)

# Last in root CMakeList. Generates binary for RP2040
pico_add_extra_outputs(main)