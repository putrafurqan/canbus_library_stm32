/**
 * @file Millis.cpp
 * @brief 
 * @date 2025-02-04
 */

#include "Millis.h"

// Constructor
Millis::Millis(uint32_t delay) : last_millis(0), delay_time(delay) {}

// Initialize the last_millis variable
void Millis::init() {
    this->last_millis = HAL_GetTick(); // Set last_millis to the current tick value
}

// Check if the delta (HAL_GetTick - last_millis) is greater than the delay
bool Millis::check() {
    uint32_t current_millis = HAL_GetTick(); // Get the current tick value
    this->delta = current_millis - this->last_millis; // Calculate the delta

    // Check if the delta is greater than or equal to the delay
    if (this->delta >= this->delay_time) {
        this->last_millis = current_millis; // Update last_millis to the current tick value
        return true; // Return true if the delay has passed
    }
    return false; // Return false if the delay has not passed
}

uint32_t Millis::get_last_delta() {
    return this->delta; // Return the last recorded millis value
}

// Set the delay time
void Millis::set_delay(uint32_t delay) {
    this->delay_time = delay; // Set the delay time
}

uint32_t Millis::get_millis() {
    return HAL_GetTick(); // Set the last_millis value
}