# STM32 CAN Bus Library

This library provides an easy-to-use interface for CAN bus communication on STM32 microcontrollers. It supports sending and receiving CAN messages with various data types, filtering messages by device and command IDs, and handling different message structures. The library is designed to be robust, efficient, and easy to integrate into your STM32 projects.

## Features
- **Easy Initialization**: Simple setup for CAN bus communication.
- **Flexible Message Handling**: Supports sending and receiving messages with different data types (e.g., `int8`, `int16`, `int32`, `float32`).
- **Message Filtering**: Filter incoming messages by device ID, command ID, or both.
- **Predefined Message Structures**: Built-in support for common message types like motor setpoints, PWM values, and sensor data.
- **Customizable**: Extend the library to support additional message types or protocols.

---

## CAN Bus Protocol Documentation

### Bitrate
- **Bitrate**: 1 Mbps

### CAN ID Structure (Standard ID)
The CAN ID is structured as follows:

| Bit-n | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|----|---|---|---|---|---|---|---|---|---|---|
| Data  | 0  | 0 | 1 | Device ID | Command ID |

- **Device ID**: Identifies the device. The number of LED blinks on the device indicates its Device ID.
- **Command ID**: Specifies the type of message or command.

---

### Message Structure

The library supports the following message types:

#### 1. **Get Driver Status** (Command ID: `0`)
- **Type**: Remote Transmission Request (RTR)
- **Description**: Requests the driver status, including error codes, PWM values, and current measurements.

| Byte | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|------|---|---|---|---|---|---|---|---|
| Data | D | C | B | A |
- **A**: `int8` Device ID
- **B**: `int8` Error code
- **C**: `int16` Actual PWM value (1000 = 100.0%)
- **D**: `float32` Current in Amperes

---

#### 2. **Get Measured Value** (Command ID: `1`)
- **Type**: Remote Transmission Request (RTR)
- **Description**: Requests measured values like speed and position.

| Byte | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|------|---|---|---|---|---|---|---|---|
| Data | B | A |
- **A**: `float32` Speed in RPS (Revolutions Per Second)
- **B**: `float32` Position in rotations (1 per rotation)

---

#### 3. **Set PWM (Open-Loop)** (Command ID: `2`)
- **Type**: Data Frame
- **Description**: Sets the PWM value for open-loop control.

| Byte | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|------|---|---|---|---|---|---|---|---|
| Data | - | - | - | - | - | B | A |
- **A**: `int8`
  - `0`: Maintain previous control mode
  - `1`: Switch to PWM control mode
- **B**: `int16` Desired PWM value (1000 = 100.0%)

---

#### 4. **Set Speed** (Command ID: `3`)
- **Type**: Data Frame
- **Description**: Sets the desired speed in RPS.

| Byte | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|------|---|---|---|---|---|---|---|---|
| Data | - | - | - | B | A |
- **A**: `int8`
  - `0`: Maintain previous control mode
  - `1`: Switch to speed control mode
- **B**: `float32` Desired speed in RPS

---

#### 5. **Set Position** (Command ID: `4`)
- **Type**: Data Frame
- **Description**: Sets the desired position.

| Byte | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|------|---|---|---|---|---|---|---|---|
| Data | - | - | - | B | A |
- **A**: `int8`
  - `0`: Maintain previous control mode
  - `1`: Switch to position control mode
- **B**: `float32` Desired position

---

#### 6. **Set Kp & Ki Speed** (Command ID: `5`)
- **Type**: Data Frame
- **Description**: Sets the proportional (Kp) and integral (Ki) gains for speed control.

| Byte | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|------|---|---|---|---|---|---|---|---|
| Data | B | A |
- **A**: `float32` Desired Kp value
- **B**: `float32` Desired Ki value

---

#### 7. **Set Kp Position** (Command ID: `6`)
- **Type**: Data Frame
- **Description**: Sets the proportional (Kp) gain for position control.

| Byte | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|------|---|---|---|---|---|---|---|---|
| Data | A |
- **A**: `float32` Desired Kp value

---

#### 8. **Set Max Values** (Command ID: `7`)
- **Type**: Data Frame
- **Description**: Sets the maximum PWM and speed values.

| Byte | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|------|---|---|---|---|---|---|---|---|
| Data | B | A |
- **A**: `int16` Maximum PWM value (1000 = 100.0%)
- **B**: `float32` Maximum speed in RPS

---

## Library Usage

### Initialization
```cpp
CAN_HandleTypeDef hcan; // CAN handle (configured using STM32CubeMX)
Canbus canbus(&hcan);   // Create Canbus object
canbus.init();          // Initialize CAN bus
```

### Sending Messages
```cpp
// Set motor setpoints
canbus.setMessageMotorSetpoint(1.5f, 2.0f);
canbus.send();

// Send an 8-bit integer
canbus.setMessageInt8(42);
canbus.send();

// Send a 32-bit float
canbus.setMessageFloat32(3.14f);
canbus.send();
```

### Receiving Messages
```cpp
// Handle received messages
canbus.callback(&hcan);

// Process received data
if (canbus.getRxCommandId() == 10) { // Motor setpoint message
    float motor1, motor2;
    canbus.getMessageMotorSetpoint(&motor1, &motor2);
    // Use motor1 and motor2
}
```

### Filtering Messages
```cpp
// Filter messages by device ID
canbus.filterByIdDevice(0x01);

// Filter messages by command ID
canbus.filterByIdCommand(0x02);

// Filter messages by both device and command ID
canbus.filterById(0x01, 0x02);
```

---

## Example Code
See the [example code](main_app.cpp) for a complete demonstration of the library's functionality.

---

