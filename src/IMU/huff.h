//Function definitions for Custom logging Application
//Utilizing Huffman compression for storing logging data

#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>

#ifndef _HUFF_H_
#define _HUFF_H_

//Function declaractions for auxilary functions to be used by HUffman Compression
//Generates a char vector from a string 
std::vector<char> char_reader(std::string input);

//Generates an unordered map of chars and their frequencies(how often they occur) in a char vector(input)
std::map<char, int> freq_generator(std::vector<char> characters);

//Generates encoded data as a string using unordered map to map characters in char vector 
std::string encoder(std::vector<char> charater_order, std::unordered_map<char , std::string> code_table);

//Generates a hdr file with code table and txt file with encoded data
void writer(std::string output, std::string encoded_data,std::map<char , int> freq_table);

//Node structure for building the HuffmanTree
struct HuffmanNode{

	char data;

	unsigned freq;

	std::shared_ptr<HuffmanNode> left;

	std::shared_ptr<HuffmanNode> right;

	HuffmanNode(char data, unsigned freq){

		this->data = data;
		this->freq = freq;
	}

};

//For comparison of two heap nodes
struct compare{

	bool operator()(std::shared_ptr<HuffmanNode> l, std::shared_ptr<HuffmanNode> r){

		return(l->freq > r->freq);
	}
};

//HuffmanTree class
class HuffmanTree{

private:

	//Priority queue for building the tree
	std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, compare> minHeap;

public:

	//Default empty
	HuffmanTree();
	//Default with intialisation values from unordered_map
	HuffmanTree(std::map<char,int> table);
	//Copy constructor
	HuffmanTree(const HuffmanTree & H);
	//Move constructor
	HuffmanTree(HuffmanTree && H);
	//Destructor
	~HuffmanTree();


	//Copy operator override
	HuffmanTree& operator=(const HuffmanTree &H);

	//Move operator override
	HuffmanTree& operator=(HuffmanTree &&H);

	//Checking state of tree
	bool isempty();

	//Generates the code table for the tree
	std::unordered_map<char , std::string > code();

	//Provides the minHeap for the tree
	std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, compare> getHeap();

};

//generate code function that is used by the code() func
void generateCodes(std::shared_ptr<HuffmanNode> root, std::string str,std::unordered_map<char , std::string> *code_table);


#endif
