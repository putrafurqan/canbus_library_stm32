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

![image](https://github.com/user-attachments/assets/8ab1faac-e5cd-4776-b4ca-98b0fe53e37c)
- **Device ID**: Identifies the device. The number of LED blinks on the device indicates its Device ID.
- **Command ID**: Specifies the type of message or command.

---

### Message Structure

The library supports the following message types:

Each CAN message is identified by a `Command ID`, which determines the type of data being transmitted. The library processes the received data based on the `Command ID` and stores it in the `message_` structure.

---

### Command ID: `1`
![image](https://github.com/user-attachments/assets/c1179404-273f-46c0-9e93-2a79f58aa2a7)
- **Description**: Single 8-bit integer value.
- **Data Structure**:
  - Byte 0: `int8` value.
  


---

### Command ID: `2`

![image](https://github.com/user-attachments/assets/66c4e787-52c3-4ac6-b19e-66b469faaddc)

- **Description**: Single 32-bit floating-point value.
- **Data Structure**:
  - Bytes 0-3: `float32` value.

---

### Command ID: `3`

![image](https://github.com/user-attachments/assets/e0b1bae0-84a3-4a15-a1fc-8cf72c3b83db)


- **Description**: Two 32-bit floating-point values.
- **Data Structure**:
  - Bytes 0-3: `float32` value 1.
  - Bytes 4-7: `float32` value 2.

---

### Command ID: `4`

![image](https://github.com/user-attachments/assets/e39bddc0-0d1a-4793-a484-8f1063b696ef)

- **Description**: Single 32-bit integer value.
- **Data Structure**:
  - Bytes 0-3: `int32` value.

---

### Command ID: `5`

![image](https://github.com/user-attachments/assets/fa2e7fa6-8917-46c3-bb82-104ab69055f4)


- **Description**: Two 32-bit integer values.
- **Data Structure**:
  - Bytes 0-3: `int32` value 1.
  - Bytes 4-7: `int32` value 2.

---

### Command ID: `6`

![image](https://github.com/user-attachments/assets/130cfbab-26c0-43df-b962-e719e1abeae1)


- **Description**: Four 16-bit integer values.
- **Data Structure**:
  - Bytes 0-1: `int16` value 1.
  - Bytes 2-3: `int16` value 2.
  - Bytes 4-5: `int16` value 3.
  - Bytes 6-7: `int16` value 4.

---

### Command ID: `10`

![image](https://github.com/user-attachments/assets/e0b1bae0-84a3-4a15-a1fc-8cf72c3b83db)

- **Description**: Motor setpoint values (speed in RPS).
- **Data Structure**:
  - Bytes 0-3: `float32` setpoint for Motor 1 (RPS).
  - Bytes 4-7: `float32` setpoint for Motor 2 (RPS).


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

