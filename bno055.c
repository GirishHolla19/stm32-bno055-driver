/*
 * bno055.c
 *
 *  Created on: Apr 14, 2026
 *      Author: Girish Holla
 */
#include "bno055.h"



/* Define your global variables here */
float xAngle, yAngle, zAngle;
float xMag, yMag, zMag;
float ax, ay, az;
float qw, qx, qy, qz;
float wx, wy, wz;
float gvx, gvy, gvz;
float temperature;
float lax, lay, laz;
I2C_HandleTypeDef Hi2c;

uint8_t buf[8];
char uart_msg[128];

void initialise(I2C_HandleTypeDef *hi2c)
{
	//Setting BNO055 into NDOF mode(9 degrees of freedom mode)
    uint8_t tmp;
    tmp = 0x0C;
    HAL_I2C_Mem_Write(hi2c, (0x28 << 1), 0x3D, I2C_MEMADD_SIZE_8BIT, &tmp, 1, 200);
    //Positively do not alter the I2C_MEMADD_SIZE_8BIT, output goes nuts if you do
    HAL_Delay(50);
}

void Angle(I2C_HandleTypeDef *hi2c)
{
	int16_t x, y, z;
	HAL_I2C_Mem_Read(hi2c, (0x28 << 1), 0x1A, I2C_MEMADD_SIZE_8BIT, buf, 6, 200);
    //Positively do not alter the I2C_MEMADD_SIZE_8BIT, output goes nuts if you do

	x = (int16_t)((buf[1] << 8) | buf[0]);
	y = (int16_t)((buf[3] << 8) | buf[2]);
	z = (int16_t)((buf[5] << 8) | buf[4]);

	xAngle = x / 16.0f;
	yAngle = y / 16.0f;
	zAngle = z / 16.0f;

	sprintf(uart_msg,"X: %.2f  Y: %.2f  Z: %.2f\r\n", xAngle, yAngle, zAngle);
}

void Acceleration(I2C_HandleTypeDef *hi2c)
{
	int16_t x, y, z;
	HAL_I2C_Mem_Read(hi2c, (0x28 << 1), 0x08, I2C_MEMADD_SIZE_8BIT, buf, 6, 200);
	//Positively do not alter the 'I2C_MEMADD_SIZE_8BIT', output goes nuts if you do

	x = (int16_t)((buf[1] << 8) | buf[0]);
	y = (int16_t)((buf[3] << 8) | buf[2]);
	z = (int16_t)((buf[5] << 8) | buf[4]);

	ax = x / 1.0f;
	ay = y / 1.0f;
	az = z / 1.0f;

	sprintf(uart_msg,"X: %.2f  Y: %.2f  Z: %.2f\r\n", ax, ay, az);
}

void Quaternion(I2C_HandleTypeDef *hi2c)
{
	int16_t x, y, z, w;
	HAL_I2C_Mem_Read(hi2c, (0x28 << 1), 0x20, I2C_MEMADD_SIZE_8BIT, buf, 8, 200);
	//Positively do not alter the 'I2C_MEMADD_SIZE_8BIT', output goes nuts if you do

	w = (int16_t)((buf[1] << 8) | buf[0]);
	x = (int16_t)((buf[3] << 8) | buf[2]);
	y = (int16_t)((buf[5] << 8) | buf[4]);
	z = (int16_t)((buf[7] << 8) | buf[6]);

	qw = w / 16384.0f;
	qx = x / 16384.0f;
	qy = y / 16384.0f;
	qz = z / 16384.0f;

	sprintf(uart_msg,"W: %.2f X: %.2f  Y: %.2f  Z: %.2f\r\n", qw, qx, qy, qz);
}

void linearAcceleration(I2C_HandleTypeDef *hi2c)
{
	int16_t x, y, z;
	HAL_I2C_Mem_Read(hi2c, (0x28 << 1), 0x28, I2C_MEMADD_SIZE_8BIT, buf, 6, 200);
	//Positively do not alter the 'I2C_MEMADD_SIZE_8BIT', output goes nuts if you do

	x = (int16_t)((buf[1] << 8) | buf[0]);
	y = (int16_t)((buf[3] << 8) | buf[2]);
	z = (int16_t)((buf[5] << 8) | buf[4]);

	lax = x / 100.0f;
	lay = y / 100.0f;
	laz = z / 100.0f;

	sprintf(uart_msg,"X: %.2f  Y: %.2f  Z: %.2f\r\n", lax, lay, laz);
}

void Gyro(I2C_HandleTypeDef *hi2c)
{
	int16_t x, y, z;
	HAL_I2C_Mem_Read(hi2c, (0x28 << 1), 0x14, I2C_MEMADD_SIZE_8BIT, buf, 6, 200);
	//Positively do not alter the 'I2C_MEMADD_SIZE_8BIT', output goes nuts if you do

	x = (int16_t)((buf[1] << 8) | buf[0]);
	y = (int16_t)((buf[3] << 8) | buf[2]);
	z = (int16_t)((buf[5] << 8) | buf[4]);

	wx = x / 100.0f;
	wy = y / 100.0f;
	wz = z / 100.0f;

	sprintf(uart_msg,"X: %.2f  Y: %.2f  Z: %.2f\r\n", wx, wy, wz);
}

void Magnetometer(I2C_HandleTypeDef *hi2c)
{
	//NOT WORKING
	int16_t x, y, z;
	HAL_I2C_Mem_Read(hi2c, (0x28 << 1), 0xE, I2C_MEMADD_SIZE_8BIT, buf, 6, 200);
	//Positively do not alter the 'I2C_MEMADD_SIZE_8BIT', output goes nuts if you do

	x = (int16_t)((buf[1] << 8) | buf[0]);
	y = (int16_t)((buf[3] << 8) | buf[2]);
	z = (int16_t)((buf[5] << 8) | buf[4]);

	xMag = x / 1.0f;
	yMag = y / 1.0f;
	zMag = z / 1.0f;

	sprintf(uart_msg,"X: %.2f  Y: %.2f  Z: %.2f\r\n", xMag, yMag, zMag);
}

void GravityVector(I2C_HandleTypeDef *hi2c)
{
	int16_t x, y, z;
	HAL_I2C_Mem_Read(hi2c, (0x28 << 1), 0x2E, I2C_MEMADD_SIZE_8BIT, buf, 6, 200);
	//Positively do not alter the 'I2C_MEMADD_SIZE_8BIT', output goes nuts if you do

	x = (int16_t)((buf[1] << 8) | buf[0]);
	y = (int16_t)((buf[3] << 8) | buf[2]);
	z = (int16_t)((buf[5] << 8) | buf[4]);

	gvx = x / 100.0f;
	gvy = y / 100.0f;
	gvz = z / 100.0f;
	sprintf(uart_msg,"X: %.2f  Y: %.2f  Z: %.2f\r\n", gvx, gvy, gvz);
}

void Temperature(I2C_HandleTypeDef *hi2c)
{
	//Working, but innacurate :(
	int16_t temp;
	HAL_I2C_Mem_Read(hi2c, (0x28 << 1), 0x34, I2C_MEMADD_SIZE_8BIT, buf, 1, 200);

	temp = (int8_t)buf[0];

	temperature = temp / 1.0f;

	sprintf(uart_msg,"Temperature: %.2f \r\n", temperature);
}

