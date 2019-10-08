/*
 * A simple example showing how to use a comms client
 */

#include "PostApp.h"

MOOS::ThreadPrint gPrinter(std::cout);

bool OnConnect(void * pParam){
	CMOOSCommClient* pC =  reinterpret_cast<CMOOSCommClient*> (pParam);
	pC->Register("IMU",0.0);
	//pC->Register("Y",0.0);
	//pC->Register("Z",0.0);

	return true;
}


int main(int argc, char * argv[]){

	//understand the command line
	MOOS::CommandLineParser P(argc,argv);

	std::string db_host="localhost";
	P.GetVariable("--moos_host",db_host);

	int db_port=9000;
	P.GetVariable("--moos_port",db_port);

	std::string my_name ="PostApp";
	P.GetVariable("--moos_name",my_name);

	//Configure Comms
	MOOS::MOOSAsyncCommClient Comms;

	//start the comms running
	Comms.Run(db_host,db_port,my_name);
	
	//IMU variable initialisation
	int acc = 2;
	int gyro = 2000;
	rawData_t accel_raw;
	rawData_t gyro_raw;

	sensorValue_t accel_values;
	sensorValue_t gyro_values;

	std::cout<<"Program started"<<std::endl;
	sampleIMU(50,acc,&accel_raw,&accel_values,gyro,&gyro_raw,&gyro_values);
	
	/*
	for(;;){
		MOOSPause(10000);
		Comms.Notify("Rows",rows); //for callback_X
		
	}*/

	gpioTerminate();
	return 0;
}

void sampleIMU(int freq,int sensitivityA,rawData_t* dataA,sensorValue_t* processedA,int sensitivityG,rawData_t* dataG,sensorValue_t* processedG){

	float time = 1/freq;
	std::cout<<time<<std::endl;
	IMU_data extracted;

	//for(int i = 0; i < 10; i++){
	
		gpioCfgSetInternals(1<<10);
		gpioInitialise();	
		accel_function(sensitivityA,dataA,processedA);
		gyro_function(sensitivityG,dataG,processedG);
		
		extracted.acc_x = processedA->x;
		extracted.acc_y = processedA->y;
		extracted.acc_z = processedA->z;
		
		std::cout<<extracted.acc_x<<std::endl;
		std::cout<<extracted.acc_y<<std::endl;
		std::cout<<extracted.acc_z<<std::endl;

		extracted.gyro_x = processedG->x;
		extracted.gyro_y = processedG->y;
		extracted.gyro_z = processedG->z;

		std::cout<<extracted.gyro_x<<std::endl;
		std::cout<<extracted.gyro_y<<std::endl;
		std::cout<<extracted.gyro_z<<std::endl;
	
		//MOOSPause(time);
	
	//}

}
