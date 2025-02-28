cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set variables based on MCU_TYPE
if(MCU_TYPE STREQUAL "F103C8T6")
    set(MCU_CPU "cortex-m3")
    set(MCU_LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/Driver/HAL/F103C8T6/stm32f103c8tx_flash.ld")
    set(STM32CUBEMX_TARGET stm32cubemx_f103c8t6)
    set(STM32CUBEMX_DIR Driver/HAL/F103C8T6/cmake/stm32cubemx)
elseif(MCU_TYPE STREQUAL "F407VET6RE")
    set(MCU_CPU "cortex-m4")
    set(MCU_LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/Driver/HAL/F407VET6RE/stm32f407vetx_flash.ld")
    set(STM32CUBEMX_TARGET stm32cubemx_f407vet6re)
    set(STM32CUBEMX_DIR Driver/HAL/F407VET6RE/cmake/stm32cubemx)
endif()

# Set the project name
set(CMAKE_PROJECT_NAME ${PROJECT_NAME}_${MCU_TYPE})
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include toolchain file
include("Driver/HAL/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C CXX ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(${STM32CUBEMX_DIR})
add_subdirectory(Interface)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)


# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    ${STM32CUBEMX_TARGET}
    Interface
)