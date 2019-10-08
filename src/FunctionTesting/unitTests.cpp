//Function testing Application
//Unit tests for functions utilised (ensure basic behaviour from base functions)

#define CATCH_CONFIG_MAIN //Catch provides a main()

#include "../IMU/huff.h"
#include "../IMU/IMUSensor.h"
#include "catch.hpp"

TEST_CASE( "Huff.h : freq_generator Tests - Checking that function generates the expected map" ){

	std::vector<char> test_sample ={'a','a','a','b','c','c','c','c','d','d'};
	std::map<char, int> control ={
		{'a',3},
		{'b',1},
		{'c',4},
		{'d',2}

	};
	std::map<char, int> generatored = freq_generator(test_sample);

	SECTION( "Equality that char match their frequencies" ){

		REQUIRE(generatored.find('a')->second == control.find('a')->second);

		REQUIRE(generatored.find('b')->second == control.find('b')->second);

		REQUIRE(generatored.find('c')->second == control.find('c')->second);

		REQUIRE(generatored.find('d')->second == control.find('d')->second);

	}

	SECTION( "Inequality checking that no char has another char frequency" ){

		REQUIRE(generatored.find('a')->second != control.find('c')->second);

		REQUIRE(generatored.find('b')->second != control.find('c')->second);

		REQUIRE(generatored.find('d')->second != control.find('c')->second);
	}
}

TEST_CASE("Huff.h : char_reader Tests - Checking that function reads in txt files and stores them correctly"){

	std::vector<char> control = {'a','b','c','d','e','f'};
	std::vector<char> generatored = char_reader("/home/pi/TestingSensors/src/FunctionTesting/Unit_test_folder/test_file");

	SECTION("Checking that characters between read in vector and control match"){

		REQUIRE(control.at(0) == generatored.at(0));
		REQUIRE(control.at(1) == generatored.at(1));
		REQUIRE(control.at(2) == generatored.at(2));
		REQUIRE(control.at(3) == generatored.at(3));
		REQUIRE(control.at(4) == generatored.at(4));
		REQUIRE(control.at(5) == generatored.at(5));

	}
}

TEST_CASE("Huff.h : encoder Tests - Checking that encoder compresses the data accordingly with a given mapping"){

	std::vector<char> test_sample = {'a','b','a','a','b','c','d'};
	std::unordered_map<char, std::string> test_table = {

		{'a',"001"},
		{'b',"100"},
		{'c',"111"},
		{'d',"101"}
	};
	std::string control = "001100001001100111101";
	std::string generated = encoder(test_sample,test_table);
	REQUIRE(control.compare(generated) == 0);
}

