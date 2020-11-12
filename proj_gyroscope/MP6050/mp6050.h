/*
 * mp6050.h
 *
 *  Created on: Oct 4, 2020
 *      Author: akash
 */

#ifndef MP6050_MP6050_H_
#define MP6050_MP6050_H_

/*
 * Includes
 */
#include "stm32f0xx_hal.h"
#include "stdbool.h"

/*
 * User defines
 */

#define DEV_ADDRESS 0xD0 			//actual slave address is 0b1101000x (only first MSB 7 bits)

/*
 * structure
 */
typedef struct  {
	int16_t temp ;

	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;

	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;

} mpu6050_t;


extern mpu6050_t mpu6050;

/*
 * Function prototypes
 */

bool init_mpu6050(I2C_HandleTypeDef *I2C_handle, mpu6050_t * mpu6050);
void  mpu_readTemp(I2C_HandleTypeDef *I2C_handle, mpu6050_t * mpu6050);
int16_t getTemp(mpu6050_t * mpu6050);

void  mpu_readGyroscope(I2C_HandleTypeDef *I2C_handle, mpu6050_t * mpu6050);
int16_t read_Gyro_X(mpu6050_t * mpu6050);
int16_t read_Gyro_Y(mpu6050_t * mpu6050);
int16_t read_Gyro_Z(mpu6050_t * mpu6050);

void  mpu_readAccel(I2C_HandleTypeDef *I2C_handle, mpu6050_t * mpu6050);
int16_t read_accel_X(mpu6050_t * mpu6050);
int16_t read_accel_Y(mpu6050_t * mpu6050);
int16_t read_accel_Z(mpu6050_t * mpu6050);

#endif /* MP6050_MP6050_H_ */
