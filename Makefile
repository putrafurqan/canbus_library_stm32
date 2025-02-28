##########################################################################################################################
# Makefile for STM32CubeCLT and Mbed OS projects
# created by Furqon - KRU15 - furqanriansyah@gmail.com
##########################################################################################################################

##########################################################################################################################
# Project Identity
##########################################################################################################################
# Pastikan tak ada spasi dalam nama project!
PROJECT_NAME = PROJECT_STRUCTURE
BUILD_DIR = build

##########################################################################################################################
# HAL Configuration
##########################################################################################################################
MCU_TYPE ?= F103C8T6
# MCU_TYPE ?= F407VET6RE
CMAKE_C_STANDARD = 11
CMAKE_BUILD_TYPE = Debug

##########################################################################################################################
# OS Detection and Configuration
##########################################################################################################################
ifeq ($(OS),Windows_NT)
    # Windows configuration
	# Pastikan tidak ada SPASI " " dan tanpa petik ""
    STM32CUBECLT_PATH = C:/ST/STM32CubeCLT_1.16.0
    CMAKE_PATH = $(STM32CUBECLT_PATH)/CMake/bin/cmake.exe
    NINJA_PATH = $(STM32CUBECLT_PATH)/Ninja/bin/ninja.exe
    STM32_PROGRAMMER_CLI = $(STM32CUBECLT_PATH)/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe
    RM = rmdir /s /q
    MKDIR = mkdir
    SHELL = cmd
else
    # Linux configuration
    STM32CUBECLT_PATH = /home/putra/st/stm32cubeclt_1.16.0
    CMAKE_PATH = $(STM32CUBECLT_PATH)/CMake/bin/cmake
    NINJA_PATH = $(STM32CUBECLT_PATH)/Ninja/bin/ninja
    STM32_PROGRAMMER_CLI = $(STM32CUBECLT_PATH)/STM32CubeProgrammer/bin/STM32_Programmer_CLI
    RM = rm -rf
    MKDIR = mkdir -p
    SHELL = bash
endif

##########################################################################################################################
# Build Application
##########################################################################################################################

cmake_configure:
	@echo Configuring CMake for MCU: $(MCU_TYPE)...
	-@$(MKDIR) $(BUILD_DIR)
	@echo $(CMAKE_PATH) -G Ninja -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) -DMCU_TYPE=$(MCU_TYPE) -DTEST=$(TEST) -DPROJECT_NAME=$(PROJECT_NAME) -B $(BUILD_DIR) -S .
	@$(CMAKE_PATH) -G Ninja -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) -DMCU_TYPE=$(MCU_TYPE) -DTEST=$(TEST) -DPROJECT_NAME=$(PROJECT_NAME) -B $(BUILD_DIR) -S .
	@echo CMake configuration complete.

# Build target
build:
	@echo Building target: $(PROJECT_NAME)_$(MCU_TYPE)
	-@cd $(BUILD_DIR) && $(NINJA_PATH)
	@echo Build finished.

# Clean target
clean:
	@echo Cleaning target: $(PROJECT_NAME)_$(MCU_TYPE)
	-@$(RM) $(BUILD_DIR)
	@echo Clean finished.

# Compile target 
compile:
	@echo Compiling target: $(PROJECT_NAME)_$(MCU_TYPE)
	@echo -------------------------
	@cd $(BUILD_DIR) && $(NINJA_PATH) 
	@echo Compile finished
	@echo -------------------------

# Flash target
flash:
	@echo Flashing target: $(PROJECT_NAME)_$(MCU_TYPE)
	@echo -------------------------
	@echo $(STM32_PROGRAMMER_CLI) --connect port=swd --download $(BUILD_DIR)/$(PROJECT_NAME)_$(MCU_TYPE).elf -hardRst -rst --start
	@$(STM32_PROGRAMMER_CLI) --connect port=swd --download $(BUILD_DIR)/$(PROJECT_NAME)_$(MCU_TYPE).elf -hardRst -rst --start
	@echo Flash finished
	@echo -------------------------

# List available communication interfaces
list_interfaces:
	@echo Listing all available communication interfaces...
	@$(STM32_PROGRAMMER_CLI) --list
	@echo Listing finished
	@echo -------------------------

# Combined target for clean, build, and flash
clean_rebuild_flash: clean cmake_configure build compile flash

clean_rebuild: clean cmake_configure build compile

all: build flash

# ----------------------------------------
# Documentation
# ----------------------------------------

# Variables:
# - PROJECT_NAME: The name of the project.
# - MCU_TYPE: The microcontroller type (default is F103C8T6).
# - BUILD_DIR: The directory where build files are stored.
# - STM32CUBECLT_PATH: The path to the STM32CubeCLT tools.
# - CMAKE_PATH: The path to the CMake executable.
# - NINJA_PATH: The path to the Ninja executable.
# - STM32_PROGRAMMER_CLI: The path to the STM32CubeProgrammer CLI.
# - CMAKE_C_STANDARD: The C standard to use (default is C11).
# - CMAKE_BUILD_TYPE: The build type (default is Debug).

# Targets:
# - cmake_configure: Configures the project using CMake.
# - build: Builds the project using Ninja.
# - clean: Cleans the build directory.
# - compile: Deprecated, use 'build' instead. Compiles the project using Ninja.
# - flash: Flashes the built ELF file to the target microcontroller.
# - list_interfaces: Lists all available communication interfaces.
# - clean_rebuild_flash: Cleans, builds, and flashes the project.
# - all: Default target that runs clean_rebuild_flash.
