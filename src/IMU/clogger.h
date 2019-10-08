//Function definitions for Custom logging Application
//Utilizing Huffman compression for storing logging data

#include "IMUSensor.h"
#include "huff.h"
#include <string>
#include <iostream>
#include <stdio.h>

#ifndef _CLOGGER_H_
#define _CLOGGER_H_

//This cloggers data from raw data and processed data into a .txt file
void clogger(std::string filename, rawData_t* data, sensorValue_t* processed);
//This compresses a .txt file and deletes it using huffman compression
void compress(std::string filename);
//Decoder function for reconstructing original file from a file and its .hdr file
void decoder(std::string filename);

#endif
