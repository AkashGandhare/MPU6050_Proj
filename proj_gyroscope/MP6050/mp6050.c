/*
 * mp6050.c
 *
 *  Created on: Oct 4, 2020
 *      Author: akash
 */

/*
 * Includes
 */

#include "mp6050.h"
#include "main.h"
#include "string.h"


/*
 * User defines
 *
 */

// Memory address of MPU6050 Register to write/read using I2C
#define WHO_AM_I		0x75
#define DEVICE_OK		0x68
#define PWR_MGMT_1		0x6B
#define GYRO_CONFIG 	0x1B
#define ACCEL_CONFIG 	0x1C
#define SMPLRT_DIV_REG 	0x19

#define SIGNAL_PATH_RESET 0x68

#define ACCEL_XOUT_H 			0x3B
#define ACCEL_XOUT_L 			0x3C
#define ACCEL_YOUT_H 			0x3D
#define ACCEL_YOUT_L 			0x3E
#define ACCEL_ZOUT_H 			0x3F
#define ACCEL_ZOUT_L 			0x40

#define TEMP_MEM_ADDRESS_HIGH	0x41
#define TEMP_MEM_ADDRESS_LOW	0x42

#define GYRO_XOUT_H 			0x43
#define GYRO_XOUT_L 			0x44
#define GYRO_YOUT_H 			0x45
#define GYRO_YOUT_L 			0x46
#define GYRO_ZOUT_H 			0x47
#define GYRO_ZOUT_L 			0x48

#define I2C_TIMEOUT 1000

/*
 * structure
 */

/*Functions prototypes
 *
 */

/*
 * @brief Initialize MPU6050 device
 * @param1 I2C handle type
 */
bool init_mpu6050(I2C_HandleTypeDef *I2C_handle, mpu6050_t *mpu6050) {
	uint8_t data = 0;
	uint8_t check_ok = 0;
	HAL_StatusTypeDef status;

	memset(mpu6050, 0, sizeof(mpu6050_t));

	//identify the device
	data = 0;

	status = HAL_I2C_Mem_Read(I2C_handle, DEV_ADDRESS, WHO_AM_I, 1, &check_ok, sizeof(check_ok), I2C_TIMEOUT);

	if(check_ok == DEVICE_OK) {

		// Wake up register by writing all 0 to PWR_MGMT_1 register
		data = 0x00;
		status = HAL_I2C_Mem_Write(I2C_handle, DEV_ADDRESS, PWR_MGMT_1, 1, &data, sizeof(data), I2C_TIMEOUT);
			HAL_Delay(100);

		// set sample rate to 1 KHz by writing SMPLRT_DIV register sample rate = Gyroscope output i.e. 8KHz / (1+SMPLRT_DIV)
		data = 0x07;
		status = HAL_I2C_Mem_Write(I2C_handle, DEV_ADDRESS, SMPLRT_DIV_REG, 1, &data, sizeof(data), I2C_TIMEOUT);
			HAL_Delay(100);

		// Reset Gyroscope
		//XG_ST = 0, YG_ST = 0, ZG_ST = 0, GFS = +- 250 °/s
		data = 0x00;
		status = HAL_I2C_Mem_Write(I2C_handle, DEV_ADDRESS, GYRO_CONFIG, 1, &data, sizeof(data), I2C_TIMEOUT);
			HAL_Delay(100);

		// Reset Accelerometer and set its range
		//XA_ST = 0, YA_ST = 0, ZA_ST = 0, AFS = +- 2g
		data = 0x00;
		status = HAL_I2C_Mem_Write(I2C_handle, DEV_ADDRESS, ACCEL_CONFIG, 1, &data, sizeof(data), I2C_TIMEOUT);
			HAL_Delay(100);

		return false;
	}

	return true;
}


/*
 * @brief Read temperature for the register
 *  @param1 I2C handle type
 *  @parm2 struct MPU6050
 */

void  mpu_readTemp(I2C_HandleTypeDef *I2C_handle, mpu6050_t *mpu6050) {
	uint8_t readTemp[2] = {0,0};
	int16_t temp = 0;

	//read two bytes of temperature data start from TEMP_MEM_HIGH_ADDRES

	if(HAL_I2C_Mem_Read(I2C_handle, DEV_ADDRESS, TEMP_MEM_ADDRESS_HIGH, 1, readTemp, sizeof(readTemp), I2C_TIMEOUT) == HAL_OK) {

		temp = (readTemp[0] << 8) | readTemp[1];
		temp = (int16_t) (temp/340 + 36.53);  	// temp in degC
		mpu6050->temp = temp;		// store into struct variable
	}
}

/*
 * @brief return stored temp value
 */
int16_t getTemp(mpu6050_t *mpu6050) {
	return mpu6050->temp;
}

/*
 * @brief Read Gyroscope values for X,Y,Z from the register
 *  @param1 I2C handle type
 *  @parm2 struct MPU6050
 */

void mpu_readGyroscope(I2C_HandleTypeDef *I2C_handle, mpu6050_t *mpu6050) {

	uint8_t gyro_xyz[6];
	int16_t gyro_x = 0, gyro_y = 0, gyro_z = 0;
	memset(gyro_xyz, 0, sizeof(gyro_xyz));

	//read 6 bytes of gyroscope register start from GYRO_XOUT_H

	if (HAL_I2C_Mem_Read(I2C_handle, DEV_ADDRESS, GYRO_XOUT_H, 1, gyro_xyz, sizeof(gyro_xyz), I2C_TIMEOUT) == HAL_OK) {

		gyro_x = (gyro_xyz[0] << 8) | gyro_xyz[1];
		gyro_y = (gyro_xyz[2] << 8) | gyro_xyz[3];
		gyro_z = (gyro_xyz[4] << 8) | gyro_xyz[5];

		mpu6050->gyro_x = gyro_x/131.0;
		mpu6050->gyro_y = gyro_y/131.0;
		mpu6050->gyro_z = gyro_z/131.0;
	}
}
/*
 * @brief return stored gyro_x value
 */
int16_t read_Gyro_X(mpu6050_t *mpu6050) {

	return mpu6050->gyro_x;
}
/*
 * @brief return stored gyro_y value
 */
int16_t read_Gyro_Y(mpu6050_t *mpu6050) {

	return mpu6050->gyro_y;
}
/*
 * @brief return stored gyro_z value
 */
int16_t read_Gyro_Z(mpu6050_t *mpu6050) {

	return mpu6050->gyro_z;
}

/*
 * @brief Read Gyroscope values for X,Y,Z from the register
 *  @param1 I2C handle type
 *  @parm2 struct MPU6050
 */

void mpu_readAccel(I2C_HandleTypeDef *I2C_handle, mpu6050_t * mpu6050) {

	uint8_t accel_xyz[6];
	int16_t accel_x = 0, accel_y = 0, accel_z = 0;
	memset(accel_xyz, 0, sizeof(accel_xyz));

	//read 6 bytes of gyroscope register start from GYRO_XOUT_H

	if (HAL_I2C_Mem_Read(I2C_handle, DEV_ADDRESS, ACCEL_XOUT_H, 1, accel_xyz, sizeof(accel_xyz), I2C_TIMEOUT) == HAL_OK) {

		accel_x = (accel_xyz[0] << 8) | accel_xyz[1];
		accel_y = (accel_xyz[2] << 8) | accel_xyz[3];
		accel_z = (accel_xyz[4] << 8) | accel_xyz[5];

		mpu6050->accel_x = accel_x/16384.0;		// as full scale select as 2g and its sensitivity is 16384/g
		mpu6050->accel_y = accel_y/16384.0;
		mpu6050->accel_z = accel_z/16384.0;
	}
}

/*
 * @brief return stored accel_x value
 */
int16_t read_accel_X(mpu6050_t * mpu6050) {

	return mpu6050->accel_x;
}
/*
 * @brief return stored gyro_y value
 */
int16_t read_accel_Y(mpu6050_t * mpu6050) {

	return mpu6050->accel_y;
}
/*
 * @brief return stored gyro_z value
 */
int16_t read_accel_Z(mpu6050_t * mpu6050) {

	return mpu6050->accel_z;
}
