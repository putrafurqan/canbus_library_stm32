/**
 * @file Gpio.cpp
 * @brief 
 * @date 2025-02-04
 */

#include "Gpio.h"

// Constructor to initialize the GPIO port and pin
GPIO::GPIO(GPIO_TypeDef *port, uint16_t pin) {
    this->port = port;
    this->pin = pin;
}

// Initialize the GPIO pin
void GPIO::init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable the GPIO clock
    if (this->port == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (this->port == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (this->port == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } // Add more ports if needed

    // Configure the GPIO pin
    GPIO_InitStruct.Pin = this->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(this->port, &GPIO_InitStruct);
}

// Write a state to the GPIO pin
void GPIO::write(bool state) {
    HAL_GPIO_WritePin(this->port, this->pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// Read the current state of the GPIO pin
bool GPIO::read() {
    return HAL_GPIO_ReadPin(this->port, this->pin) == GPIO_PIN_SET;
}

// Toggle the state of the GPIO pin
void GPIO::toggle() {
    HAL_GPIO_TogglePin(this->port, this->pin);
}