
#include "IMUSensor.h" //FXOS8700 and FXAS21002 definitions required for setting up the sensor

using namespace std;

void accel_function(int sensitivity,rawData_t* data1,rawData_t* data2,sensorValue_t* processed1,sensorValue_t* processed2){

	char buffer[13];
	uint8_t data_cfg = 0x00;
	float accel_mg_lsb = 0.0;

	switch(sensitivity)
	{
		case 2:
		data_cfg = 0x00;
		accel_mg_lsb = ACCEL_MG_LSB_2G;
		break;
		case 4:
		data_cfg = 0x01;
		accel_mg_lsb = ACCEL_MG_LSB_4G;
		break;
		case 8:
		data_cfg = 0x02;
		accel_mg_lsb = ACCEL_MG_LSB_8G;
		break;

	}

	//Open up the i2c device FXOS8700
	int handle = i2cOpen(1,SENSOR1,0);

	int temp = i2cReadByteData(handle,FXOS8700_REGISTER_WHO_AM_I);
	//Checking that the device ID is accurate
	if(temp != SENSOR1_ID){
		cout << "There is an error with the device" <<endl;
		temp = i2cClose(handle);
		gpioTerminate();
		return ;
	}
	//Set device to standby mode : Enables data readings
	i2cWriteWordData(handle,FXOS8700_REGISTER_CTRL_REG1,0);

	//Configure the accelerometer speed
	//Use one speed for now
	i2cWriteWordData(handle,FXOS8700_REGISTER_XYZ_DATA_CFG,data_cfg);
	//High Resolution
	i2cWriteWordData(handle,FXOS8700_REGISTER_CTRL_REG2, 0x02);
	//Active Normal Mode low Noise 100Hz in Hybrid Mode
	i2cWriteWordData(handle,FXOS8700_REGISTER_CTRL_REG1, 0x15);

	//Configure the magnetometer
	//Hybrid Mode, Over sampling = 16
	i2cWriteWordData(handle,FXOS8700_REGISTER_MCTRL_REG1, 0x1F);
	//Jump to reg 0x33 after reading 0x06
	i2cWriteWordData(handle,FXOS8700_REGISTER_MCTRL_REG2, 0x20);

	//Read 13 bytes of the sensor
	temp = i2cReadDevice(handle,buffer,13);

	//Creating proper integer values from the sensors
	float acc_x = (int16_t)((buffer[1] << 8) | buffer[2]) >> 2;
	float acc_y = (int16_t)((buffer[3] << 8) | buffer[4]) >> 2;
	float acc_z = (int16_t)((buffer[5] << 8) | buffer[6]) >> 2;
	float mag_x = (int16_t)((buffer[7] << 8) | buffer[8]);
	float mag_y = (int16_t)((buffer[9] << 8) | buffer[10]);
	float mag_z = (int16_t)((buffer[11] << 8) | buffer[12]);

	data1->x = acc_x;
	data1->y = acc_y;
	data1->z = acc_z;

	data2->x = mag_x;
	data2->y = mag_y;
	data2->z = mag_z;

	acc_x *= accel_mg_lsb * SENSORS_GRAVITY_STANDARD;
	acc_y *= accel_mg_lsb * SENSORS_GRAVITY_STANDARD;
	acc_z *= accel_mg_lsb * SENSORS_GRAVITY_STANDARD;

	mag_x *= MAG_UT_LSB;
	mag_y *= MAG_UT_LSB;
	mag_z *= MAG_UT_LSB;

	processed1->x = acc_x;
	processed1->y = acc_y;
	processed1->z = acc_z;

	processed2->x = mag_x;
	processed2->y = mag_y;
	processed2->z = mag_z;

	temp = i2cClose(handle);

}

void gyro_function(int sensitivity,rawData_t* data,sensorValue_t* processed){

	char buffer[7];
	uint8_t ctrlReg = 0x00;
	float gyro_sensitivity = 0.0;
	switch(sensitivity)
	{
		case 250:
		ctrlReg = 0x03;
		gyro_sensitivity = GYRO_SENSITIVITY_250DPS;
		break;
		case 500:
		ctrlReg = 0x02;
		gyro_sensitivity = GYRO_SENSITIVITY_500DPS;
		break;
		case 1000:
		ctrlReg = 0x01;
		gyro_sensitivity = GYRO_SENSITIVITY_1000DPS;
		break;
		case 2000:
		ctrlReg = 0x00;
		gyro_sensitivity = GYRO_SENSITIVITY_2000DPS;
		break;

	}

	//Open up the i2c device FXAS21002
	int handle = i2cOpen(1,SENSOR2,0);

	int temp = i2cReadByteData(handle,GYRO_REGISTER_WHO_AM_I);
	//Checking that the device ID is accurate
	if(temp != SENSOR2_ID){
		cout << "There is an error with the device" <<endl;
		temp = i2cClose(handle);
		gpioTerminate();
		return ;
	}

	//Configuring Sensor
	/* Reset then switch to active mode with 100Hz output */
  	i2cWriteWordData(handle,GYRO_REGISTER_CTRL_REG1, 0x00);     // Standby
 	i2cWriteWordData(handle,GYRO_REGISTER_CTRL_REG1, (1<<6));   // Reset
  	i2cWriteWordData(handle,GYRO_REGISTER_CTRL_REG0, ctrlReg); // Set sensitivity
  	i2cWriteWordData(handle,GYRO_REGISTER_CTRL_REG1, 0x0E);     // Active
	usleep(1000);

	temp = i2cReadDevice(handle,buffer,7);

	float gyro_x = (int16_t)((buffer[1] << 8) | buffer[2]);
	float gyro_y = (int16_t)((buffer[3] << 8) | buffer[4]);
	float gyro_z = (int16_t)((buffer[5] << 8) | buffer[6]);

	data->x = gyro_x;
	data->y = gyro_y;
	data->z = gyro_z;

	gyro_x *= gyro_sensitivity;
	gyro_y *= gyro_sensitivity;
	gyro_z *= gyro_sensitivity;

	gyro_x *= SENSORS_DPS_TO_RADS;
	gyro_y *= SENSORS_DPS_TO_RADS;
	gyro_z *= SENSORS_DPS_TO_RADS;

	processed->x = gyro_x;
	processed->y = gyro_y;
	processed->z = gyro_z;

	temp = i2cClose(handle);

}
