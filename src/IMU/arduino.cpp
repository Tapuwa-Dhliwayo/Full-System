  
//Simple C++ to read and write to the Arduino

//C Libraries

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "rs232.h"

#define BUF_SIZE 128

int main(){

	int i=0;
	int cport_nr=24; /* /dev/ttyACM0 */
  	int bdrate=115200; /* 9600 baud */
 
  	char mode[]={'8','N','1',0}; // 8 data bits, no parity, 1 stop bit
  	char str_send[2][BUF_SIZE]; // send data buffer
  	unsigned char str_recv[BUF_SIZE]; // recv data buffer
  	strcpy(str_send[0], "This is a test string.\n");
  	strcpy(str_send[1], "This is another test string.\n");
  
  	if(RS232_OpenComport(cport_nr, bdrate, mode,0)) {

		printf("Can not open comport\n");
    		return(0);
  	}

	char check[] = "This is a test string.\n";	
	int bits = sizeof(check);
	
    	//RS232_cputs(cport_nr, check); // sends string on serial
	//RS232_CloseComport(cport_nr);

  	usleep(2000000);  // waits 2000ms for stable condition 
  	while(1){
    		RS232_cputs(cport_nr, str_send[i]); // sends string on serial
		usleep(1000000); //Delay for a second
		//printf("Sent to Arduino: '%s'\n", str_send[i]);
		//usleep(2000000); /* waits for reply 2000ms */
		std::cout<<RS232_GetPortnr("ttyACM0")<<std::endl; 
		int n = RS232_PollComport(cport_nr, str_recv, (int)BUF_SIZE); 
		std::cout<<n<<std::endl; 
		if(n > 0){

			str_recv[n] = 0;   // always put a "null" at the end of a string! 
      			printf("Received %i bytes: '%s'\n", n, (char *)str_recv);
		}
		i++;
    		i %= 2;
    		usleep(5000000);  // sleep for 5 Second 
 
  	}
  	return(0);
}
