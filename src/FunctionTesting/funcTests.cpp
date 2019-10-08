//This application is for testing functions in the clogger.h, IMUSensor.h libraries
//Tapuwa Dhliwayo
//07/10/2019

#include "/home/pi/TestingSensors/src/IMU/clogger.h"
#include "/home/pi/TestingSensors/src/IMU/IMUSensor.h"

int main(){

	//Setting the test values based on the control files values
	rawData_t test_r;
	sensorValue_t test_s;
	test_r.x = 1000;
	test_r.y = 2000;
	test_r.z = 2000;

	test_s.x = 10;
	test_s.y = 20;
	test_s.z = 30;
	//The test is gonna be run 10 times 
	for(int i = 0; i < 10; i++){
		//The test will be to create a file using clogger based on these values
		//Then compressing and deleting original file
		//Then decompressing it with a new name
		//Success - is a new file that matches the control after decompression
		std::string filename ="/home/pi/TestingSensors/src/FunctionTesting/Func_test_folder/test"+std::to_string(i);
		std::cout<<filename<<std::endl;

		clogger(filename,&test_r,&test_s);
		compress(filename);
		decoder(filename);

	}
}
