/**
 * @file Millis.h
 * @brief Header file for the Millis class, which inherits from MillisInterface.
 * 
 * This class provides functionality to manage time delays using the HAL library for STM32 microcontrollers.
 * It includes conditional compilation for different STM32 series (STM32F103xB and STM32F407xx).
 */

#pragma once

#include <cstdint>
#include "../../../../Interface/MillisInterface.h"

#ifdef STM32F103xB
#include "stm32f1xx_hal.h"
#endif

#ifdef STM32F407xx
#include "stm32f4xx_hal.h" 
#endif

/**
 * @class Millis
 * @brief Class for managing time delays using the HAL library.
 * 
 * This class inherits from MillisInterface and provides methods to initialize, check, and manage time delays.
 */
class Millis : public MillisInterface {
public:
    /**
     * @brief Constructor for the Millis class.
     * 
     * Initializes the Millis object with a specified delay.
     * 
     * @param delay The delay time in milliseconds.
     */
    Millis(uint32_t delay);

    /**
     * @brief Initializes the last_millis variable.
     * 
     * Sets the last_millis variable to the current tick value using HAL_GetTick().
     */
    void init() override;

    /**
     * @brief Checks if the specified delay has passed.
     * 
     * Calculates the time elapsed since last_millis and checks if it is greater than or equal to the specified delay.
     * If true, it updates last_millis and returns true; otherwise, it returns false.
     * 
     * @return True if the delay has passed, false otherwise.
     */
    bool check() override;

    /**
     * @brief Sets the delay time.
     * 
     * Sets the delay time in milliseconds.
     * 
     * @param delay The delay time in milliseconds.
     */
    void set_delay(uint32_t delay) override;

    /**
     * @brief Returns the last recorded delta time.
     * 
     * Returns the last recorded delta time.
     * 
     * @return The last recorded delta time.
     */
    uint32_t get_last_delta();

    /**
     * @brief Returns the current tick value.
     * 
     * Returns the current tick value using HAL_GetTick().
     * 
     * @return The current tick value.
     */
    uint32_t get_millis();

private:
    uint32_t delta;         ///< Stores the time difference between the current tick and the last recorded tick.
    uint32_t last_millis;   ///< Stores the last recorded tick value.
    uint32_t delay_time;    ///< Stores the delay time in milliseconds.
};
