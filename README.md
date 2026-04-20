# stm32-bno055-driver
A STM32 HAL driver for the BNO055 9-axis IMU using I2C, It can be used with any STM MCU.
# STM32 BNO055 9-Axis IMU Driver

![STM32](https://img.shields.io/badge/STM32-CubeIDE-blue)
![C](https://img.shields.io/badge/Language-C-00599C)
![License](https://img.shields.io/badge/License-MIT-green)

A clean, modular, and easy-to-use bare-metal HAL driver for interfacing the Bosch BNO055 9-axis Absolute Orientation Sensor with STM32 microcontrollers via I2C.

## Features
* **Dependency Injected I2C:** Pass any `I2C_HandleTypeDef` to the functions, allowing you to use multiple sensors on different I2C buses without changing the driver code.
* **NDOF Fusion Mode:** Automatically configured to output 9 Degrees of Freedom data.
* **Data Extraction:** Easy-to-call functions for Euler Angles, Quaternions, Linear Acceleration, Gravity Vectors, and Gyroscope data.
* **No Blocking Delays in Loop:** Built to run efficiently in your `main()` loop.

## Hardware Requirements
* **Microcontroller:** Any STM Microcontroller (Tested on `STM32 Nucleo F446RE`)
* **Sensor:** BNO055 Breakout Board

## Wiring Guide

| BNO055 Pin | STM32 Pin (I2C1) | Description |
| :--- | :--- | :--- |
| **VIN** | 3.3V | Power |
| **GND** | GND | Ground |
| **SCL** | PB8 (Example) | I2C Clock |
| **SDA** | PB9 (Example) | I2C Data |

*(Note: Verify your specific Nucleo's I2C1 pins in STM32CubeIDE's `.ioc` file)*


**1. Clone the repository and include the files in your project:**
Add `bno055.h` to your `Core/Inc` folder and `bno055.c` to your `Core/Src` folder.
## Available Sensor Functions
To retrieve different types of data from the BNO055, simply call the corresponding function in your main loop. All functions update the global variables and the `uart_msg` string automatically.

| Function Call | Data Retrieved | Global Variables Updated |
| :--- | :--- | :--- |
| `Angle(&hi2c1)` | Euler Orientation | `xAngle`, `yAngle`, `zAngle` |
| `Acceleration(&hi2c1)` | Raw Acceleration | `ax`, `ay`, `az` |
| `linearAcceleration(&hi2c1)` | Linear Acceleration (No Gravity) | `lax`, `lay`, `laz` |
| `Quaternion(&hi2c1)` | Quaternion Orientation | `qw`, `qx`, `qy`, `qz` |
| `Gyro(&hi2c1)` | Angular Velocity | `wx`, `wy`, `wz` |
| `GravityVector(&hi2c1)` | Gravity Vector | `gvx`, `gvy`, `gvz` |
| `Magnetometer(&hi2c1)` | Magnetic Field Strength | `xMag`, `yMag`, `zMag` |
| `Temperature(&hi2c1)` | Ambient Temperature | `temperature` |

> **Note:** Ensure you pass the correct I2C handle (e.g., `&hi2c1`) that matches your hardware configuration.

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

