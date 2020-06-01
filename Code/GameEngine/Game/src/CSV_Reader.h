#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct CSV_Response
{
	std::string ResponseText;
	int NextID;

	void ReadAsText()
	{
		std::cout << "Response Text: " << ResponseText << " Next ID: " << NextID << "\n";
	}

	const char* ResponseAsChar()
	{
		return ResponseText.c_str();
	}
};



struct CSV_OUT
{
	int ID;
	std::string FileName;
	std::string Dialogue;

	std::vector<CSV_Response> responses;

	void ReadFullCSV()
	{
		std::cout << "Name: " << FileName << " Price: " << Dialogue << "\n";
		for (int i = 0; i < responses.size(); i++)
		{
			responses[i].ReadAsText();
		}

		std::cout << "\n";

	}

};

class CSV_Reader
{
public:
	bool LoadCSV(std::string fileLocation);
	CSV_OUT* GetCurrentData() { return m_CurentData; }
	///Changes data based on input
	void ChangeCurrentData(int _dataIndex) { m_CurentData = &m_CSVData[_dataIndex]; }
	///Changes data based on current data
	//void ChangeCurrentData(int ResponseIndex) { m_CurentData.responses[ResponseIndex].NextID; }
	
private:
	std::vector<CSV_OUT> m_CSVData;
	CSV_OUT* m_CurentData; ///the current data being stored in 
	

};

