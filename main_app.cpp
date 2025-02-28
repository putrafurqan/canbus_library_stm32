#include "main.h"
#include "tim.h"

#ifdef STM32F103xB
#include "Driver/HAL/Library/Pinout/f103c8t6.h"
#elif STM32F407xx
#include "Driver/HAL/Library/Pinout/f407vet6re.h"
#endif

#include "../Driver/HAL/Library/Canbus/Canbus.h"
#include "../Driver/HAL/Library/Gpio/Gpio.h"
#include "../Driver/HAL/Library/Millis/Millis.h"

// GPIO object for LED
GPIO led(LED_GPIO_Port, LED_Pin);
Millis millis_led(250);

// CAN bus object
Canbus canbus(&hcan);

extern "C" void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    canbus.callback(hcan);
}

// Main function
extern "C" int main_app(void);
int main_app(void) {
    // Initialize the CAN bus
    canbus.init();

    // Set the device ID (e.g., 0x01 for this device)
    canbus.setDeviceId(0x01);

    // Variables for sending and receiving data
    float motor1Setpoint = 0.0f, motor2Setpoint = 0.0f;
    int8_t receivedInt8 = 0;
    float receivedFloat32 = 0.0f;

    // Main loop
    while (1) {
        
        // Toggle LED every 250ms
        if (millis_led.check()) {
            led.toggle();
        }

        // Send a CAN message every 1 second
        static Millis canSendInterval(1000);
        if (canSendInterval.check()) {
            // Set motor setpoints (example values)
            motor1Setpoint += 0.1f;
            motor2Setpoint += 0.2f;

            // Send motor setpoints over CAN
            canbus.setMessageMotorSetpoint(motor1Setpoint, motor2Setpoint);
            canbus.send();

            // Send an 8-bit integer over CAN
            static int8_t int8Value = 0;
            int8Value++;
            canbus.setMessageInt8(int8Value);
            canbus.send();

            // Send a 32-bit float over CAN
            static float float32Value = 0.0f;
            float32Value += 0.5f;
            canbus.setMessageFloat32(float32Value);
            canbus.send();
        }

        // Check if a message was received
        if (canbus.getRxCommandId() == 10) { // Motor setpoint message
            canbus.getMessageMotorSetpoint(&motor1Setpoint, &motor2Setpoint);

        } else if (canbus.getRxCommandId() == 1) { 
            canbus.getMessageInt8(&receivedInt8);

        } else if (canbus.getRxCommandId() == 2) {
            canbus.getMessageFloat32(&receivedFloat32);

        }
    }
    return 0;
}