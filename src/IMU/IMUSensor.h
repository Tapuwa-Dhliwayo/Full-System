//Sensor Library for FXOS8700 and FXAS21002 sensors(IMU)

#include <stdint.h>
#include <pigpio.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>

#ifndef _IMUSENSOR_H_
#define _IMUSENSOR_H_

#define SENSOR1 		    0x1F //FXOS8700
#define SENSOR1_ID                  0xC7 //FXOS8700 ID
#define SENSOR2                     0x21 //FXAS21002
#define SENSOR2_ID                  0xD7 //FXAS21002 ID

//Sensor value scaling constants (Processing raw data to actual information)
#define ACCEL_MG_LSB_2G 	    0.000244F
#define ACCEL_MG_LSB_4G 	    0.000488F
#define ACCEL_MG_LSB_8G             0.000976F
#define MAG_UT_LSB                  0.1F
#define SENSORS_GRAVITY_STANDARD    9.80665F
#define GYRO_SENSITIVITY_250DPS	    0.0078125F
#define GYRO_SENSITIVITY_500DPS     0.015625F
#define GYRO_SENSITIVITY_1000DPS    0.03125F
#define GYRO_SENSITIVITY_2000DPS    0.0625F
#define SENSORS_DPS_TO_RADS         0.017453293F

//Registers for the FXOS8700 Sensor 1
typedef enum
{
      FXOS8700_REGISTER_STATUS          = 0x00, /**< 0x00 */
      FXOS8700_REGISTER_OUT_X_MSB       = 0x01, /**< 0x01 */
      FXOS8700_REGISTER_OUT_X_LSB       = 0x02, /**< 0x02 */
      FXOS8700_REGISTER_OUT_Y_MSB       = 0x03, /**< 0x03 */
      FXOS8700_REGISTER_OUT_Y_LSB       = 0x04, /**< 0x04 */
      FXOS8700_REGISTER_OUT_Z_MSB       = 0x05, /**< 0x05 */
      FXOS8700_REGISTER_OUT_Z_LSB       = 0x06, /**< 0x06 */
      FXOS8700_REGISTER_WHO_AM_I        = 0x0D, /**< 0x0D (default value = 0b11000111, read only) */
      FXOS8700_REGISTER_XYZ_DATA_CFG    = 0x0E, /**< 0x0E */
      FXOS8700_REGISTER_CTRL_REG1       = 0x2A, /**< 0x2A (default value = 0b00000000, read/write) */
      FXOS8700_REGISTER_CTRL_REG2       = 0x2B, /**< 0x2B (default value = 0b00000000, read/write) */
      FXOS8700_REGISTER_CTRL_REG3       = 0x2C, /**< 0x2C (default value = 0b00000000, read/write) */
      FXOS8700_REGISTER_CTRL_REG4       = 0x2D, /**< 0x2D (default value = 0b00000000, read/write) */
      FXOS8700_REGISTER_CTRL_REG5       = 0x2E, /**< 0x2E (default value = 0b00000000, read/write) */
      FXOS8700_REGISTER_MSTATUS         = 0x32, /**< 0x32 */
      FXOS8700_REGISTER_MOUT_X_MSB      = 0x33, /**< 0x33 */
      FXOS8700_REGISTER_MOUT_X_LSB      = 0x34, /**< 0x34 */
      FXOS8700_REGISTER_MOUT_Y_MSB      = 0x35, /**< 0x35 */
      FXOS8700_REGISTER_MOUT_Y_LSB      = 0x36, /**< 0x36 */
      FXOS8700_REGISTER_MOUT_Z_MSB      = 0x37, /**< 0x37 */
      FXOS8700_REGISTER_MOUT_Z_LSB      = 0x38, /**< 0x38 */
      FXOS8700_REGISTER_MCTRL_REG1      = 0x5B, /**< 0x5B (default value = 0b00000000, read/write) */
      FXOS8700_REGISTER_MCTRL_REG2      = 0x5C, /**< 0x5C (default value = 0b00000000, read/write) */
      FXOS8700_REGISTER_MCTRL_REG3      = 0x5D, /**< 0x5D (default value = 0b00000000, read/write) */
}fxos8700Registers_t;

//Speed Settings optional
typedef enum
    {
      ACCEL_RANGE_2G                    = 0x00, /**< +/- 2g range */
      ACCEL_RANGE_4G                    = 0x01, /**< +/- 4g range */
      ACCEL_RANGE_8G                    = 0x02  /**< +/- 8g range */
    } fxos8700AccelRange_t;

//Raw data struct
typedef struct
    {
      int16_t x;    /**< Raw int16_t value from the x axis */
      int16_t y;    /**< Raw int16_t value from the y axis */
      int16_t z;    /**< Raw int16_t value from the z axis */
    } rawData_t;
//Processed data struct
typedef struct
    {
      float x;    /**< Raw int16_t value from the x axis */
      float y;    /**< Raw int16_t value from the y axis */
      float z;    /**< Raw int16_t value from the z axis */
    } sensorValue_t;

//Registers for FXAS21002 Sensor 2
typedef enum
    {
      GYRO_REGISTER_STATUS              = 0x00, /**< 0x00 */
      GYRO_REGISTER_OUT_X_MSB           = 0x01, /**< 0x01 */
      GYRO_REGISTER_OUT_X_LSB           = 0x02, /**< 0x02 */
      GYRO_REGISTER_OUT_Y_MSB           = 0x03, /**< 0x03 */
      GYRO_REGISTER_OUT_Y_LSB           = 0x04, /**< 0x04 */
      GYRO_REGISTER_OUT_Z_MSB           = 0x05, /**< 0x05 */
      GYRO_REGISTER_OUT_Z_LSB           = 0x06, /**< 0x06 */
      GYRO_REGISTER_WHO_AM_I            = 0x0C, /**< 0x0C (default value = 0b11010111, read only) */
      GYRO_REGISTER_CTRL_REG0           = 0x0D, /**< 0x0D (default value = 0b00000000, read/write) */
      GYRO_REGISTER_CTRL_REG1           = 0x13, /**< 0x13 (default value = 0b00000000, read/write) */
      GYRO_REGISTER_CTRL_REG2           = 0x14, /**< 0x14 (default value = 0b00000000, read/write) */
    } gyroRegisters_t;

//Optionally Speed settings for Gyro
typedef enum
    {
      GYRO_RANGE_250DPS  = 250,     /**< 250dps */
      GYRO_RANGE_500DPS  = 500,     /**< 500dps */
      GYRO_RANGE_1000DPS = 1000,    /**< 1000dps */
      GYRO_RANGE_2000DPS = 2000     /**< 2000dps */
    } gyroRange_t;


//Function declarations
void accel_function(int sensitivity, rawData_t* data1, rawData_t* data2, sensorValue_t* processed1, sensorValue_t* processed2 );
void gyro_function(int sensitivity, rawData_t* data, sensorValue_t* processed);

#endif
