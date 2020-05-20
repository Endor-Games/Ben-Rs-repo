#include "CSV_Reader.h"

using namespace std;


bool CSV_Reader::LoadCSV2(vector<CSV_OUT>& fileData, string fileLocation)
{
	ifstream ip(fileLocation);

	if (!ip.is_open())
	{
		cout << "ERROR: File has failed to Open" << '\n';
		return false;
	}


	int Index = 0;
	while (ip.peek() != EOF)
	{
		CSV_OUT out;
		string price;
		string NextID;
		out.ID = Index;
		getline(ip, out.FileName, ',');
		getline(ip, price, ',');

		out.Price = stoi(price);

		getline(ip, out.Description, ',');
		getline(ip, NextID, '\n');

		out.Next = stoi(NextID);

		fileData.push_back(out);
	}


	return true;
}
