# stm32-bno055-driver
A STM32 HAL driver for the BNO055 9-axis IMU using I2C, It can be used with any STM MCU.
# STM32 BNO055 9-Axis IMU Driver

![STM32](https://img.shields.io/badge/STM32-CubeIDE-blue)
![C](https://img.shields.io/badge/Language-C-00599C)
![License](https://img.shields.io/badge/License-MIT-green)

A clean, modular, and easy-to-use bare-metal HAL driver for interfacing the Bosch BNO055 9-axis Absolute Orientation Sensor with STM32 microcontrollers via I2C.

## 🚀 Features
* **Dependency Injected I2C:** Pass any `I2C_HandleTypeDef` to the functions, allowing you to use multiple sensors on different I2C buses without changing the driver code.
* **NDOF Fusion Mode:** Automatically configured to output 9 Degrees of Freedom data.
* **Data Extraction:** Easy-to-call functions for Euler Angles, Quaternions, Linear Acceleration, Gravity Vectors, and Gyroscope data.
* **No Blocking Delays in Loop:** Built to run efficiently in your `main()` loop.

## 🛠️ Hardware Requirements
* **Microcontroller:** Any STM Microcontroller (Tested on `STM32 Nucleo F446RE`)
* **Sensor:** BNO055 Breakout Board

## 🔌 Wiring Guide

| BNO055 Pin | STM32 Pin (I2C1) | Description |
| :--- | :--- | :--- |
| **VIN** | 3.3V | Power |
| **GND** | GND | Ground |
| **SCL** | PB8 (Example) | I2C Clock |
| **SDA** | PB9 (Example) | I2C Data |

*(Note: Verify your specific Nucleo's I2C1 pins in STM32CubeIDE's `.ioc` file)*


**1. Clone the repository and include the files in your project:**
Add `bno055.h` to your `Core/Inc` folder and `bno055.c` to your `Core/Src` folder.

**2. Include the header in `main.c`:**
```c
#include "bno055.h"

**3. Initialize and Read:**
// Inside main(), before the while(1) loop:
initialise(&hi2c1);

// Inside the while(1) loop:
Angle(&hi2c1);
HAL_UART_Transmit(&huart2, (uint8_t*)uart_msg, strlen(uart_msg), 100);
HAL_Delay(100);

Note for accessing other functionalities instead of Angle(&hi2c) call Acceleration(&hi2c), Quaternion(&hi2c), linearAcceleration(&hi2c), Gyro(&hi2c), Magnetometer(&hi2c), GravityVector(&hi2c), Temperature(&hi2c) according to your need
