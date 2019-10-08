//Logging function utilising huffman algorithm for compression
//Sorted

#include "clogger.h"

void clogger(std::string filename, rawData_t* data, sensorValue_t* processed){

	std::ofstream logfile;
	logfile.open(filename+".txt");
	logfile << "Raw Data \n";
	logfile << "x: "<< data->x <<"\n";
	logfile << "y: "<< data->y <<"\n";
	logfile << "z: "<< data->z <<"\n";
	logfile << "Processed Data \n";
	logfile << "x: "<< processed->x <<"\n";
	logfile << "y: "<< processed->y <<"\n";
	logfile << "z: "<< processed->z <<"\n";
	logfile.close();

}

void compress(std::string filename){

	std::vector<char> char_vector = char_reader(filename);
	std::map<char, int> freq_table = freq_generator(char_vector);
	HuffmanTree tree(freq_table);
	std::unordered_map<char , std::string > code_table = tree.code();
	std::string encoded_data = encoder(char_vector,code_table);
	writer(filename,encoded_data,freq_table);
	if(std::remove((filename+".txt").c_str()) != 0){
		perror("Error deleting file");
	}
	else{
		puts("File successfully deleted");
	}
}

void decoder(std::string filename){

	std::map<char , int> freq_table;
	std::ifstream file(filename+".hdr");
	int swap = 0;
	char character;
	char keep;
	int frequency;
	while(!file.eof()){

		file>>std::noskipws;
		file>>character;
		if(character != '&'){
			keep = character;
			swap = 0;
		}
		else if(character == '&' && swap == 0){
			file>>frequency;
			freq_table.insert(std::make_pair(keep,frequency));
			swap = 1;
		}
	}
	file.close();

	std::ifstream file2(filename);
	std::string encoded_data;
	std::getline(file2,encoded_data);
	file2.close();

	writer("Checking",encoded_data,freq_table);

	HuffmanTree tree(freq_table);
	std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>,compare> minHeap = tree.getHeap();
	std::shared_ptr<HuffmanNode> root = minHeap.top();
	std::shared_ptr<HuffmanNode> curr = root;

	std::ofstream decodedfile;
	decodedfile.open(filename+"_decoded.txt");
	std::string ans = "";
	for(int i = 0; i < encoded_data.size(); i++){

		if(encoded_data[i] == '0'){
			curr = curr->left;
		}
		else{
			curr = curr->right;
		}
		//Reach the leaf
		if(curr->left==NULL && curr->right==NULL){

			ans += curr->data;
			curr = root;
		}
	}
	decodedfile<<ans;
	decodedfile.close();
}

