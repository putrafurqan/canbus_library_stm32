/**
 * @file f1038t6.h
 * @brief 
 * @date 2025-02-04
 */

// UART Peripherals
#define HUART_PC huart1

// CAN Peripherals
#define HCAN hcan

// Encoder (Interrupt-based) Peripherals
#define ENC_EXTI1_GPIO_Port GPIOB
#define ENC_EXTI2_GPIO_Port GPIOB

// Motor Peripherals
#define HTIM_MOTOR2 htim1
#define HTIM_CHANNEL_MOTOR2 TIM_CHANNEL_2
#define HTIM_MOTOR1 htim1
#define HTIM_CHANNEL_MOTOR1 TIM_CHANNEL_1

// I2C Peripherals
#define HI2C hi2c2
