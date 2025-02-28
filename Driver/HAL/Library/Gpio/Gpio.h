/**
 * @file Gpio.h
 * @brief This file defines the GPIO class for STM32 microcontrollers.
 *
 * This class provides an interface to interact with GPIO pins, allowing for initialization,
 * reading, writing, and toggling pin states. It supports STM32F103xB and STM32F407xx series.
 */
#pragma once

#include "../../../../Interface/GpioInterface.h"
#include "gpio.h"

#ifdef STM32F103xB
#include "stm32f1xx_hal.h"
#elif STM32F407xx
#include "stm32f4xx_hal.h"
#endif

/**
 * @class GPIO
 * @brief A class for controlling GPIO pins on STM32 microcontrollers.
 *
 * This class inherits from the GPIOInterface and provides methods to initialize,
 * write to, read from, and toggle the state of a GPIO pin.
 */
class GPIO : public GPIOInterface {
public:
    /**
     * @brief Constructor for the GPIO class.
     *
     * @param port The GPIO port.
     * @param pin The GPIO pin number.
     */
    GPIO(GPIO_TypeDef *port, uint16_t pin);

    /**
     * @brief Initializes the GPIO pin.
     *
     * Enables the GPIO clock and configures the pin as an output push-pull with no pull-up or pull-down resistor.
     */
    void init() override;

    /**
     * @brief Writes a state to the GPIO pin.
     *
     * @param state The state to write to the pin (true for high, false for low).
     */
    void write(bool state) override;

    /**
     * @brief Reads the current state of the GPIO pin.
     *
     * @return True if the pin is high, false if it is low.
     */
    bool read() override;

    /**
     * @brief Toggles the state of the GPIO pin.
     */
    void toggle() override;

private:
    GPIO_TypeDef *port; /**< The GPIO port. */
    uint16_t pin;       /**< The GPIO pin number. */
};
