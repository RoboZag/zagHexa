/*
*	In this code we can manipulate of string in diffrent ways:
*	- Input a string and divid it by the comma into file with new lines for each.
*	- Read from file a specific line and store it to some intgere or float or string variable.
*	- Read all the sensor values from the file as a float.
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <vector>

#define Debug true	

int num_of_lines = 0;
std::string::size_type sz;

void Data_to_file()
{
	std::ofstream index;
	std::string str;
	std::string line;

	// Open new file each time and delete the old one
	index.open("Index.txt");

	if (index) {
		
		std::cin >> str;		// Replace with data from App 
		size_t stln = str.size();
		for (unsigned i = 0; i < stln; i++) {
			if (str[i] != 0x2C)
				index << str[i];
			else {
				index << "\n";
				num_of_lines++;
			}
				
		}

	}
	else
		std::cout << "File could not be created" << std::endl;
	index.close();
}

std::string read_from_specific_line(int linen)
{
	std::ifstream index("Index.txt");
	std::string line;
	if (index) {
		for (int lineno = 0; getline(index, line) && lineno < linen + 1; lineno++)
			if (lineno == linen)
				return line;  
	}
	index.close();
}

std::vector<float> All_sensor_reading() {

	std::vector<float> sensor_reading;
	std::ifstream index("index.txt");
	std::string line;

	
	if (index)
	{
		// If we don't know the number of lines 
		if (num_of_lines == 0) {
			while (std::getline(index, line))
				num_of_lines++;
			// If file is Empty 
			if (num_of_lines == 0) {
				sensor_reading.push_back(0);
				return sensor_reading;
			}
				
			// Return to the beginning of the file
			index.clear();
			index.seekg(0, std::ios::beg);

		}
		
		// Extract the sensor values only
		for (int lineno = 0; std::getline(index, line) && lineno < num_of_lines; lineno++)
			if (lineno % 2 != 0) 
					sensor_reading.push_back(atof(line.c_str()));
	}

	index.close();
	return sensor_reading;
}


void main()
{
	int linen = 6;							// Replace with the wanted numbers
	std::string buff;
	std::vector<float> sensor_reading;
	//Data_to_file();
	sensor_reading = All_sensor_reading();
	if(Debug)
		for (std::vector<float>::iterator it = sensor_reading.begin(); it != sensor_reading.end(); it++)
			std::cout << *it << "\n";
	buff = read_from_specific_line(linen);	// to receive a string 
	int x = atoi(buff.c_str());				// to receive a number as integer
	float y = atof(buff.c_str());				// to receive a number as float
}