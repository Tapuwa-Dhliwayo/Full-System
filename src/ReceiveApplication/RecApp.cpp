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

bool OnMail(void *pParam){
	CMOOSCommClient* pC = reinterpret_cast<CMOOSCommClient*>(pParam);

	MOOSMSG_LIST M; //get the mail
	pC->Fetch(M);

	MOOSMSG_LIST::iterator q; //process it
	for(q=M.begin();q!=M.end();q++){
		gPrinter.SimplyPrintTimeAndMessage("mail:"+q->GetSource(), MOOS::ThreadPrint::GREEN);
	}
	return true;
}

bool funcX(CMOOSMsg & M, void * TheParameterYouSaidtoPassOnToCallback)
{

	gPrinter.SimplyPrintTimeAndMessage("call back for Rows", MOOS::ThreadPrint::CYAN);
	int rows = (int)M.GetDouble();
	for(int i = 1; i <= rows; ++i){
        	for(int j = 1; j <= i; ++j){
            		std::cout << "* ";
       	 	}
        	std::cout << "\n";
    	}	

	return true;
}

bool funcY(CMOOSMsg & M, void * TheParameterYouSaidtoPassOnToCallback)
{
	gPrinter.SimplyPrintTimeAndMessage(M.GetString(), MOOS::ThreadPrint::MAGENTA);
	return true;
}


int main(int argc, char * argv[]){

	//understand the command line
	MOOS::CommandLineParser P(argc,argv);

	std::string db_host="localhost";
	P.GetVariable("--moos_host",db_host);

	int db_port=9000;
	P.GetVariable("--moos_port",db_port);

	std::string my_name ="ReceiveApp";
	P.GetVariable("--moos_name",my_name);

	//configure the comms
	MOOS::MOOSAsyncCommClient Comms;
	Comms.SetOnMailCallBack(OnMail,&Comms);
	Comms.SetOnConnectCallBack(OnConnect,&Comms);

	//here we add per message callbacks
	//first parameter is the channel nick-name, then the function
	//to call, then a parameter we want passed when callback is
	//invoked
	Comms.AddMessageCallBack("callback_X","Rows",funcX,NULL);
	Comms.AddMessageCallBack("callback_Y","Y",funcY,NULL);

	//start the comms running
	Comms.Run(db_host,db_port,my_name);

	//for ever loop sending data
	std::vector<unsigned char> X(1000);
	for(;;){
		
	}
	return 0;
}
