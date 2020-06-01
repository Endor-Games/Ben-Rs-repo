#include "CSV_Reader.h"

using namespace std;


bool CSV_Reader::LoadCSV(string fileLocation)
{
	ifstream ip(fileLocation);

	if (!ip.is_open())
	{
		cout << "ERROR: File has failed to Open" << '\n';
		return false;
	}


	m_CSVData.clear();
	m_CurentData = nullptr;

	//ignores first line which explains what each collum does (until 500 characters is met or it gets to the end of the line)
	ip.ignore(500, '\n');

	int Index = 0;
	while (ip.peek() != EOF)
	{
		CSV_OUT out;
		string NextID;
		string ResponseCheck;

		out.ID = Index;
		getline(ip, out.FileName, ',');
		getline(ip, out.Dialogue, ',');


		CSV_Response Response;
		for (int i = 0; i < 4; i++)
		{

			getline(ip, ResponseCheck, ',');

			if (ResponseCheck == "n/a")
			{
				if (i == 0)
				{
					Response.ResponseText = "Next";
					if (i == 3)
						getline(ip, NextID, '\n');
					else
						getline(ip, NextID, ',');


					Response.NextID = stoi(NextID);

					out.responses.push_back(Response);
				}


				ip.ignore(500, '\n');
				
				i = 10;
			}
			else
			{

				Response.ResponseText = ResponseCheck;
				if (i == 3)
					getline(ip, NextID, '\n');
				else
					getline(ip, NextID, ',');

				Response.NextID = stoi(NextID);
				out.responses.push_back(Response);
			}
			
		}


		//getline(ip, NextID, );
		//out.Next = stoi(NextID);






		m_CSVData.push_back(out);
	}

	m_CurentData = &m_CSVData[0];

	return true;
}

