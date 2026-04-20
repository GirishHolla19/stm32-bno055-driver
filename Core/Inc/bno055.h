/*
 * bno055.h
 *
 *  Created on: Apr 14, 2026
 *      Author: Girish Holla
 */

#ifndef INC_BNO055_H_
#define INC_BNO055_H_
#include "main.h"
#include <stdio.h>
#include <string.h>


extern float xAngle, yAngle, zAngle;
extern float xMag, yMag, zMag;
extern float ax, ay, az;
extern float qw, qx, qy, qz;
extern float wx, wy, wz;
extern float gvx, gvy, gvz;
extern float temperature;
extern float lax, lay, laz;

extern char uart_msg[128];

/* Function Declarations */
void initialise(I2C_HandleTypeDef *hi2c);
void Angle(I2C_HandleTypeDef *hi2c);
void Acceleration(I2C_HandleTypeDef *hi2c);
void Quaternion(I2C_HandleTypeDef *hi2c);
void linearAcceleration(I2C_HandleTypeDef *hi2c);
void Gyro(I2C_HandleTypeDef *hi2c);
void Magnetometer(I2C_HandleTypeDef *hi2c);
void GravityVector(I2C_HandleTypeDef *hi2c);
void Temperature(I2C_HandleTypeDef *hi2c);


#endif /* INC_BNO055_H_ */
