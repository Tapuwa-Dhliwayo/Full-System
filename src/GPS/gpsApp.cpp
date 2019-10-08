//Simple C++ to read GPS data

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <pigpio.h>

#define TXD 14
#define RXD 15
#define BAUDRATE 9600
#define DATABITS 8
#define BUFSIZE 10000

void printStruct(char buffer[], int bufsize); //prints out the contents of the buffer

int main(){

	int read = 0;
	char buffer[BUFSIZE];
	char test[] = {'5','6','8','3','7'};
	//printf("Buffer before read: %d\n", buffer);
	//usleep(2000000);
	//
	gpioCfgSetInternals(1<<10); //Signal 11 error
	if(gpioInitialise() < 0){
		std::cout << "Failed to Initialise.";
	}

	//Set the GPIO PINs to TXD and RXD
	gpioSetMode(TXD, PI_ALT0); //Setting pin 14 to TXD mode
	gpioSetMode(RXD, PI_ALT0); //Setting pin 15 to RXD mode
	gpioSerialReadOpen(RXD,BAUDRATE,DATABITS); //Open up a serial read on RXD line
	while(read < 1){

		int i = 0;
		std::cout <<"Read count:"<<read<<std::endl;
		gpioSerialRead(RXD, &buffer, BUFSIZE);
		printf("RXD buffer: \n");
		std::cout<<sizeof(buffer)<<std::endl;
		printStruct(buffer, BUFSIZE);
		printf("\n");
		usleep(2000000);
		read++;
	}
	gpioSerialReadClose(RXD); //Close serial read
	gpioTerminate(); //Terminate the GPIO pins
	//
	return(0);

}


void printStruct(char buffer[], int bufsize){

	int i = 0;
	while(i < bufsize){

		if( (int)buffer[i] == 36 ){

			printf("%c", buffer[i]); //$ start of message

		}/*
		else if( (int)buffer[i] == 32){

			printf("%c", buffer[i]); // SPACE 
		}*/
		else if( (int)buffer[i] == 44){

			printf("%c", buffer[i]); // COMMA
		}
		else if( (int)buffer[i] == 42){

			printf("%c", buffer[i]); // *
		}

		else if( (int)buffer[i] > 64 && (int)buffer[i] < 91){

			printf("%c", buffer[i]); // Letters from A - Z
		}
		else if( (int)buffer[i] > 47 && (int)buffer[i] < 58){

			printf("%c", buffer[i]); // Numbers from 0 - 9
		}
		else{
			//Do nothing
		}//

	i++;
	}
}
