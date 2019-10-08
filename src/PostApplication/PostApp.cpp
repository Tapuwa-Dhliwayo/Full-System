/*
 * A simple example showing how to use a comms client
 */
#include "MOOS/libMOOS/Comms/MOOSAsyncCommClient.h"
#include "MOOS/libMOOS/Utils/CommandLineParser.h"
#include "MOOS/libMOOS/Utils/ConsoleColours.h"
#include "MOOS/libMOOS/Utils/ThreadPrint.h"

#include <iostream>

MOOS::ThreadPrint gPrinter(std::cout);

bool OnConnect(void * pParam){
	CMOOSCommClient* pC =  reinterpret_cast<CMOOSCommClient*> (pParam);
	pC->Register("Rows",0.0);
	pC->Register("Y",0.0);
	pC->Register("Z",0.0);

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

	//for ever loop sending data
	std::vector<unsigned char> X(1000);

	int rows = 5;




	for(;;){
		MOOSPause(10000);
		Comms.Notify("Rows",rows); //for callback_X
		//Comms.Notify("Y","This is Y"); //for callback_Y
		//Comms.Notify("Z",7.0); //no callback
	}
	return 0;
}
