#include "Canbus.h"

// Constructor
Canbus::Canbus(CAN_HandleTypeDef *hcan) {
    this->hcan_ = hcan;
    this->deviceId_ = 0;
    this->commandId_ = 0;

    this->autoResetStatus = false;
}

// Initialize CAN communication
void Canbus::init() {
    HAL_CAN_Start(this->hcan_);

    // Configure reception filter
    this->rxFilterConfig_.FilterActivation = CAN_FILTER_ENABLE;
    this->rxFilterConfig_.FilterFIFOAssignment = CAN_FILTER_FIFO1;
    this->rxFilterConfig_.FilterMode = CAN_FILTERMODE_IDMASK;
    this->rxFilterConfig_.FilterScale = CAN_FILTERSCALE_16BIT;
    this->rxFilterConfig_.FilterIdHigh = 0x0;
    this->rxFilterConfig_.FilterIdLow = 0;
    this->rxFilterConfig_.FilterMaskIdHigh = 0x0;
    this->rxFilterConfig_.FilterMaskIdLow = 0;

    HAL_CAN_ConfigFilter(this->hcan_, &this->rxFilterConfig_);
    HAL_CAN_ActivateNotification(this->hcan_, CAN_IT_RX_FIFO1_MSG_PENDING);
}

// Send a CAN message
int Canbus::send() {
    this->setStandardId(this->deviceId_, this->commandId_);
    return HAL_CAN_AddTxMessage(this->hcan_, &this->txHeader_, this->txData_, &this->txMailbox_);
}

void Canbus::setDeviceId(uint16_t deviceId) {
    this->deviceId_ = deviceId;
}

// Set standard ID for transmission
void Canbus::setStandardId(uint16_t deviceId, uint16_t commandId) {
    this->deviceId_ = deviceId;
    this->commandId_ = commandId;
    this->txHeader_.StdId = (deviceId << 4) | commandId;
}

// Get standard ID for reception
int Canbus::getRxheaderStdId() {
    return (this->rxHeader_.StdId);
}

// Get Device ID for reception
int Canbus::getRxDeviceId() {
    return (this->rxHeader_.StdId >> 4);
}

// Get Device ID for reception
int Canbus::getRxCommandId() {
    return (this->rxHeader_.StdId & 0xF);
}

void Canbus::getMessageRaw(uint8_t* data){
    for (int i = 0; i < 8; i++){
        data[i] = this->rxData_[i];
    }
}

void Canbus::resetIdle(){

    this->message_.int8 = 0;
    this->message_.float32 = 0;
    this->message_.float32_1 = 0;
    this->message_.float32_2 = 0;
    this->message_.int32 = 0;
    this->message_.int32_1 = 0;
    this->message_.int32_2 = 0;
    this->message_.int16_1 = 0;
    this->message_.int16_2 = 0;
    this->message_.int16_3 = 0;
    this->message_.int16_4 = 0;
    this->message_.setpointMotor1Rps = 0;
    this->message_.setpointMotor2Rps = 0;
    
}

void Canbus::setAutoResetIdle(bool status, uint32_t wait_time){

    if (status)
    {
        this->autoResetStatus = true;
        this->wait_time_reset = wait_time;
        this->millis_reset = HAL_GetTick();
    }

}

// Configure filter by device ID
void Canbus::filterByIdDevice(uint16_t deviceId) {
    uint16_t filterId = deviceId << 4;
    uint16_t filterMask = 0x00F0;

    this->rxFilterConfig_.FilterIdHigh = filterId << 5;
    this->rxFilterConfig_.FilterMaskIdHigh = filterMask << 5;
    this->rxFilterConfig_.FilterIdLow = filterId << 5;
    this->rxFilterConfig_.FilterMaskIdLow = filterMask << 5;

    HAL_CAN_ConfigFilter(this->hcan_, &this->rxFilterConfig_);
}

// Configure filter by command ID
void Canbus::filterByIdCommand(uint16_t commandId) {
    uint16_t filterId = commandId;
    uint16_t filterMask = 0x000F;

    this->rxFilterConfig_.FilterIdHigh = filterId << 5;
    this->rxFilterConfig_.FilterMaskIdHigh = filterMask << 5;
    this->rxFilterConfig_.FilterIdLow = filterId << 5;
    this->rxFilterConfig_.FilterMaskIdLow = filterMask << 5;

    HAL_CAN_ConfigFilter(this->hcan_, &this->rxFilterConfig_);
}

// Configure filter by both device and command ID
void Canbus::filterById(uint16_t deviceId, uint16_t commandId) {
    uint16_t filterId = (deviceId << 4) | commandId;
    uint16_t filterMask = 0x00FF;

    this->rxFilterConfig_.FilterIdHigh = filterId << 5;
    this->rxFilterConfig_.FilterMaskIdHigh = filterMask << 5;
    this->rxFilterConfig_.FilterIdLow = filterId << 5;
    this->rxFilterConfig_.FilterMaskIdLow = filterMask << 5;

    HAL_CAN_ConfigFilter(this->hcan_, &this->rxFilterConfig_);
}

// Message handling methods
void Canbus::setMessageMotorSetpoint(float setpointMotor1Rps, float setpointMotor2Rps) {
    this->commandId_ = 10;
    this->txHeader_.DLC = 8;
    this->message_.setpointMotor1Rps = setpointMotor1Rps;
    this->message_.setpointMotor2Rps = setpointMotor2Rps;
    *(float *)&this->txData_[0] = setpointMotor1Rps;
    *(float *)&this->txData_[4] = setpointMotor2Rps;
}



void Canbus::setMessageInt8(int8_t value) {
    this->commandId_ = 1;
    this->txHeader_.DLC = 1;
    this->message_.int8 = value;
    *(int8_t *)&this->txData_[0] = value;
}

void Canbus::setMessageFloat32(float value) {
    this->commandId_ = 2;
    this->txHeader_.DLC = 4;
    this->message_.float32 = value;
    *(float *)&this->txData_[0] = value;
}

void Canbus::setMessageMultiFloat32(float value1, float value2) {
    this->commandId_ = 3;
    this->txHeader_.DLC = 8;
    this->message_.float32_1 = value1;
    this->message_.float32_2 = value2;
    *(float *)&this->txData_[0] = value1;
    *(float *)&this->txData_[4] = value2;
}

void Canbus::setMessageInt32(int32_t value) {
    this->commandId_ = 4;
    this->txHeader_.DLC = 4;
    this->message_.int32 = value;
    *(int32_t *)&this->txData_[0] = value;
}

void Canbus::setMessageMultiInt32(int32_t value1, int32_t value2) {
    this->commandId_ = 5;
    this->txHeader_.DLC = 8;
    this->message_.int32_1 = value1;
    this->message_.int32_2 = value2;
    *(int32_t *)&this->txData_[0] = value1;
    *(int32_t *)&this->txData_[4] = value2;
}

void Canbus::setMessageMultiInt16(int16_t value1, int16_t value2, int16_t value3, int16_t value4) {
    this->commandId_ = 6;
    this->txHeader_.DLC = 8;
    this->message_.int16_1 = value1;
    this->message_.int16_2 = value2;
    this->message_.int16_3 = value3;
    this->message_.int16_4 = value4;
    *(int16_t *)&this->txData_[0] = value1;
    *(int16_t *)&this->txData_[2] = value2;
    *(int16_t *)&this->txData_[4] = value3;
    *(int16_t *)&this->txData_[6] = value4;
}


void Canbus::getMessageMotorSetpoint(float *setpointMotor1Rps, float *setpointMotor2Rps) {
    *setpointMotor1Rps = this->message_.setpointMotor1Rps;
    *setpointMotor2Rps = this->message_.setpointMotor2Rps;
}

void Canbus::getMessageInt8(int8_t *value) {
    *value = this->message_.int8;
}

void Canbus::getMessageFloat32(float *value) {
    *value = this->message_.float32;
}

void Canbus::getMessageMultiFloat32(float *value1, float *value2) {
    *value1 = this->message_.float32_1;
    *value2 = this->message_.float32_2;
}

void Canbus::getMessageInt32(int32_t *value) {
    *value = this->message_.int32;
}

void Canbus::getMessageMultiInt32(int32_t *value1, int32_t *value2) {
    *value1 = this->message_.int32_1;
    *value2 = this->message_.int32_2;
}

void Canbus::getMessageMultiInt16(int16_t *value1, int16_t *value2, int16_t *value3, int16_t *value4) {
    *value1 = this->message_.int16_1;
    *value2 = this->message_.int16_2;
    *value3 = this->message_.int16_3;
    *value4 = this->message_.int16_4;
}

// Callback for handling received messages
void Canbus::callback(CAN_HandleTypeDef *hcan) {
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &this->rxHeader_, this->rxData_);

    this->handleReceivedMessage();
}

// Handle received messages
void Canbus::handleReceivedMessage() {

    uint8_t commandId = this->rxHeader_.StdId & 0x0F;
    
    switch (commandId) {
        case 1:
            this->message_.int8 = *(int8_t *)&this->rxData_[0];
            break;
        case 2:
            this->message_.float32 = *(float *)&this->rxData_[0];
            break;
        case 3:
            this->message_.float32_1 = *(float *)&this->rxData_[0];
            this->message_.float32_2 = *(float *)&this->rxData_[4];
            break;
        case 4:
            this->message_.int32 = *(int32_t *)&this->rxData_[0];
            break;
        case 5:
            this->message_.int32_1 = *(int32_t *)&this->rxData_[0];
            this->message_.int32_2 = *(int32_t *)&this->rxData_[4];
            break;
        case 6:
            this->message_.int16_1 = *(int16_t *)&this->rxData_[0];
            this->message_.int16_2 = *(int16_t *)&this->rxData_[2];
            this->message_.int16_3 = *(int16_t *)&this->rxData_[4];
            this->message_.int16_4 = *(int16_t *)&this->rxData_[6];
            break;
        case 10:
            this->message_.setpointMotor1Rps = *(float *)&this->rxData_[0];
            this->message_.setpointMotor2Rps = *(float *)&this->rxData_[4];
            break;
        default:
            // Handle unknown command IDs if necessary
            break;
    }
}