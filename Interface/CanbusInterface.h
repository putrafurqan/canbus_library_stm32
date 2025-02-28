#pragma once
#include <cstdint>

class CanbusInterface {
public:
    virtual ~CanbusInterface() = default;

    // Pure virtual methods for CAN communication
    virtual void init() = 0;
    virtual int send() = 0;
    virtual void setDeviceId(uint16_t deviceId) = 0;
    virtual void setStandardId(uint16_t deviceId, uint16_t commandId) = 0;
    virtual void filterByIdDevice(uint16_t deviceId) = 0;
    virtual void filterByIdCommand(uint16_t commandId) = 0;
    virtual void filterById(uint16_t deviceId, uint16_t commandId) = 0;

    // Message handling methods
    virtual void setMessageMotorSetpoint(float setpointMotor1Rps, float setpointMotor2Rps) = 0;
    virtual void getMessageMotorSetpoint(float *setpointMotor1Rps, float *setpointMotor2Rps) = 0;
    virtual void setMessageInt8(int8_t value) = 0;
    virtual void getMessageInt8(int8_t *value) = 0;
    virtual void setMessageFloat32(float value) = 0;
    virtual void getMessageFloat32(float *value) = 0;
    virtual void setMessageMultiFloat32(float value1, float value2) = 0;
    virtual void getMessageMultiFloat32(float *value1, float *value2) = 0;
    virtual void setMessageInt32(int32_t value) = 0;
    virtual void getMessageInt32(int32_t *value) = 0;
    virtual void setMessageMultiInt32(int32_t value1, int32_t value2) = 0;
    virtual void getMessageMultiInt32(int32_t *value1, int32_t *value2) = 0;
    virtual void setMessageMultiInt16(int16_t value1, int16_t value2, int16_t value3, int16_t value4) = 0;
    virtual void getMessageMultiInt16(int16_t *value1, int16_t *value2, int16_t *value3, int16_t *value4) = 0;
};