#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct CSV_OUT
{
	int ID;
	std::string FileName;
	int Price;
	std::string Description;
	int Next;

	void ReadFullCSV()
	{
		std::cout << "Name: " << FileName << " Price: " << Price << "\n Description: " << Description << " Next Entry: " << Next << "\n \n";
	}
};

namespace CSV_Reader
{

	bool LoadCSV2(std::vector<CSV_OUT>& fileData, std::string fileLocation);
};

