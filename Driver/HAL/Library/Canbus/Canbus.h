/**
 * @file Canbus.h
 * @date 2025-02-05
 * @class Canbus
 * @brief This class provides an interface for CAN bus communication on STM32 microcontrollers.
 * 
 * The Canbus class inherits from CanbusInterface and implements methods for initializing the CAN peripheral,
 * sending and receiving messages, setting filters, and handling various types of data messages.
 */

#pragma once

#include "../../../../Interface/CanbusInterface.h"
#include "can.h"

class Canbus : public CanbusInterface {
    
public:
    /**
     * @brief Constructor for the Canbus class.
     * @param hcan Pointer to the CAN_HandleTypeDef structure used for CAN communication.
     */
    Canbus(CAN_HandleTypeDef *hcan);

    /**
     * @brief Initializes the CAN peripheral.
     * 
     * This method sets up the CAN hardware and configures the necessary filters and interrupts.
     */
    void init() override;

    /**
     * @brief Sends a CAN message.
     * @return int Returns 0 on success, or a negative value on failure.
     */
    int send() override;

    /**
     * @brief Sets the device ID for CAN messages.
     * @param deviceId The device ID to be set.
     */
    void setDeviceId(uint16_t deviceId) override;

    /**
     * @brief Sets the standard ID for CAN messages.
     * @param deviceId The device ID to be set.
     * @param commandId The command ID to be set.
     */
    void setStandardId(uint16_t deviceId, uint16_t commandId) override;

    /**
     * @brief Filters incoming CAN messages by device ID.
     * @param deviceId The device ID to filter by.
     */
    void filterByIdDevice(uint16_t deviceId) override;

    /**
     * @brief Filters incoming CAN messages by command ID.
     * @param commandId The command ID to filter by.
     */
    void filterByIdCommand(uint16_t commandId) override;

    /**
     * @brief Filters incoming CAN messages by both device ID and command ID.
     * @param deviceId The device ID to filter by.
     * @param commandId The command ID to filter by.
     */
    void filterById(uint16_t deviceId, uint16_t commandId) override;

    /**
     * @brief Callback function for handling CAN interrupts.
     * @param hcan Pointer to the CAN_HandleTypeDef structure.
     */
    void callback(CAN_HandleTypeDef *hcan);

    /**
     * @brief Enables or disables automatic reset of the CAN bus idle state.
     * @param status If true, enables auto-reset; if false, disables it.
     * @param wait_time The time to wait before resetting the idle state.
     */
    void setAutoResetIdle(bool status, uint32_t wait_time);

    /**
     * @brief Resets the CAN bus idle state.
     */
    void resetIdle();

    /**
     * @brief Retrieves the device ID from the received CAN message.
     * @return int The device ID of the received message.
     */
    int getRxDeviceId();

    /**
     * @brief Retrieves the command ID from the received CAN message.
     * @return int The command ID of the received message.
     */
    int getRxCommandId();


    /**
     * @brief Retrieves the standard ID from the received CAN message header.
     * @return int The standard ID of the received message.
     */
    int getRxheaderStdId();

    /**
     * @brief Get the Message in 8-bytes of uint8_t char
     * @param data Pointer to store the raw 8-byte data
     */
    void getMessageRaw(uint8_t* data);

    /**
     * @brief Sets the motor setpoint values in the CAN message.
     * @param setpointMotor1Rps The setpoint for motor 1 in revolutions per second.
     * @param setpointMotor2Rps The setpoint for motor 2 in revolutions per second.
     */
    void setMessageMotorSetpoint(float setpointMotor1Rps, float setpointMotor2Rps) override;

    /**
     * @brief Retrieves the motor setpoint values from the CAN message.
     * @param setpointMotor1Rps Pointer to store the setpoint for motor 1.
     * @param setpointMotor2Rps Pointer to store the setpoint for motor 2.
     */
    void getMessageMotorSetpoint(float *setpointMotor1Rps, float *setpointMotor2Rps) override;

    /**
     * @brief Sets an 8-bit integer value in the CAN message.
     * @param value The 8-bit integer value to be set.
     */
    void setMessageInt8(int8_t value) override;

    /**
     * @brief Retrieves an 8-bit integer value from the CAN message.
     * @param value Pointer to store the retrieved 8-bit integer value.
     */
    void getMessageInt8(int8_t *value) override;

    /**
     * @brief Sets a 32-bit floating-point value in the CAN message.
     * @param value The 32-bit floating-point value to be set.
     */
    void setMessageFloat32(float value) override;

    /**
     * @brief Retrieves a 32-bit floating-point value from the CAN message.
     * @param value Pointer to store the retrieved 32-bit floating-point value.
     */
    void getMessageFloat32(float *value) override;

    /**
     * @brief Sets two 32-bit floating-point values in the CAN message.
     * @param value1 The first 32-bit floating-point value to be set.
     * @param value2 The second 32-bit floating-point value to be set.
     */
    void setMessageMultiFloat32(float value1, float value2) override;

    /**
     * @brief Retrieves two 32-bit floating-point values from the CAN message.
     * @param value1 Pointer to store the first 32-bit floating-point value.
     * @param value2 Pointer to store the second 32-bit floating-point value.
     */
    void getMessageMultiFloat32(float *value1, float *value2) override;

    /**
     * @brief Sets a 32-bit integer value in the CAN message.
     * @param value The 32-bit integer value to be set.
     */
    void setMessageInt32(int32_t value) override;

    /**
     * @brief Retrieves a 32-bit integer value from the CAN message.
     * @param value Pointer to store the retrieved 32-bit integer value.
     */
    void getMessageInt32(int32_t *value) override;

    /**
     * @brief Sets two 32-bit integer values in the CAN message.
     * @param value1 The first 32-bit integer value to be set.
     * @param value2 The second 32-bit integer value to be set.
     */
    void setMessageMultiInt32(int32_t value1, int32_t value2) override;

    /**
     * @brief Retrieves two 32-bit integer values from the CAN message.
     * @param value1 Pointer to store the first 32-bit integer value.
     * @param value2 Pointer to store the second 32-bit integer value.
     */
    void getMessageMultiInt32(int32_t *value1, int32_t *value2) override;

    /**
     * @brief Sets four 16-bit integer values in the CAN message.
     * @param value1 The first 16-bit integer value to be set.
     * @param value2 The second 16-bit integer value to be set.
     * @param value3 The third 16-bit integer value to be set.
     * @param value4 The fourth 16-bit integer value to be set.
     */
    void setMessageMultiInt16(int16_t value1, int16_t value2, int16_t value3, int16_t value4) override;

    /**
     * @brief Retrieves four 16-bit integer values from the CAN message.
     * @param value1 Pointer to store the first 16-bit integer value.
     * @param value2 Pointer to store the second 16-bit integer value.
     * @param value3 Pointer to store the third 16-bit integer value.
     * @param value4 Pointer to store the fourth 16-bit integer value.
     */
    void getMessageMultiInt16(int16_t *value1, int16_t *value2, int16_t *value3, int16_t *value4) override;

private:
    /**
     * @brief Pointer to the CAN_HandleTypeDef structure used for CAN communication.
     */
    CAN_HandleTypeDef *hcan_;

    /**
     * @brief CAN transmit header structure.
     */
    CAN_TxHeaderTypeDef txHeader_;

    /**
     * @brief Array to store CAN transmit data.
     */
    uint8_t txData_[8];

    /**
     * @brief CAN transmit mailbox.
     */
    uint32_t txMailbox_;

    /**
     * @brief Device ID for CAN messages.
     */
    uint16_t deviceId_;

    /**
     * @brief Command ID for CAN messages.
     */
    uint16_t commandId_;

    /**
     * @brief CAN filter configuration for reception.
     */
    CAN_FilterTypeDef rxFilterConfig_;

    /**
     * @brief CAN receive header structure.
     */
    CAN_RxHeaderTypeDef rxHeader_;

    /**
     * @brief Array to store CAN receive data.
     */
    uint8_t rxData_[8];

    /**
     * @brief Flag to enable or disable automatic reset of the CAN bus idle state.
     */
    bool autoResetStatus;

    /**
     * @brief Timestamp for the last reset of the CAN bus idle state.
     */
    uint32_t millis_reset;

    /**
     * @brief Time to wait before resetting the CAN bus idle state.
     */
    uint32_t wait_time_reset;

    /**
     * @struct Message
     * @brief Structure to store various types of CAN message data.
     */
    struct Message {
        int8_t int8;                        ///< 8-bit integer value.
        float float32;                      ///< 32-bit floating-point value.
        float float32_1, float32_2;         ///< Two 32-bit floating-point values.
        int32_t int32;                      ///< 32-bit integer value.
        int32_t int32_1, int32_2;           ///< Two 32-bit integer values.
        int16_t int16_1, int16_2, int16_3, int16_4; ///< Four 16-bit integer values.
        float setpointMotor1Rps, setpointMotor2Rps; ///< Motor setpoint values in revolutions per second.
    } message_;

    /**
     * @brief Configures the CAN filter based on the current device and command IDs.
     */
    void configureFilter();

    /**
     * @brief Handles the received CAN message.
     */
    void handleReceivedMessage();
};