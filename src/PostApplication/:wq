//Header file for the PostApp

#include "MOOS/libMOOS/Comms/MOOSAsyncCommClient.h"
#include "MOOS/libMOOS/Utils/CommandLineParser.h"
#include "MOOS/libMOOS/Utils/ConsoleColours.h"
#include "MOOS/libMOOS/Utils/ThreadPrint.h"

#include <iostream>
#include <thread>
#include <pigpio.h>

#include "../IMU/clogger.h"

//IMU struct with all the data
struct IMU_data{

	float acc_x;
	float acc_y;
	float acc_z;

	float gyro_x;
	float gyro_y;
	float gyro_z;
};


//Function Declarations

void sampleIMU(int freq,int sensitivityA,rawData_t* dataA,sensorValue_t* processedA,int sensitivityG,rawData_t* dataG,sensorValue_t* processedG);


