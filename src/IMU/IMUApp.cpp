#include <iostream>
#include <errno.h>
#include <unistd.h>
#include "clogger.h"
#include <pigpio.h>

using namespace std;

int main(){

	int acc = 2;
	int gyro = 2000;
	rawData_t accel_raw;
	rawData_t mag_raw;
	rawData_t gyro_raw;
	sensorValue_t accel_values;
	sensorValue_t mag_values;
	sensorValue_t gyro_values;
	/*
	cout << "Enter Sensitivities:" << endl;
	cout << "Accel(2,4,8) and Gyro(250,500,1000,2000)" << endl;
	cin >> acc >> gyro;
	*/
	cout <<"Accel Sensitivity: " << acc << " Gyro Sensitivity: " << gyro << endl;
	
	gpioCfgSetInternals(1<<10);
	gpioInitialise();

	accel_function(acc,&accel_raw,&mag_raw,&accel_values,&mag_values);
	gyro_function(gyro,&gyro_raw,&gyro_values);

	gpioTerminate();

	clogger("testing",&accel_raw,&accel_values);
	compress("testing");
	
	decoder("testing_compressed");
	/*
	cout << "Accel Processed" << endl;
	printf("X: %f \n",accel_values.x);
	printf("Y: %f \n",accel_values.y);
	printf("Z: %f \n",accel_values.z);

	cout << "Gyro Processed" << endl;
	printf("X: %f \n",gyro_values.x);
	printf("Y: %f \n",gyro_values.y);
	printf("Z: %f \n",gyro_values.z);
	*/

	return 0;
}

