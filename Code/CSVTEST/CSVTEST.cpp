// CSVTEST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CSV_Reader.h"
#include <Windows.h>



int main()
{
    
	std::vector<CSV_OUT> outVec;
	if (!CSV_Reader::LoadCSV2(outVec, "CSV_FILES/TestCSV.csv"))
		return false;


	int Index = 0;
	int TickIndex = 10;
	while (true)
	{


		if (GetAsyncKeyState(VK_SPACE))
		{
			outVec[Index].ReadFullCSV();

			Index = outVec[Index].Next;
		}

		if (GetAsyncKeyState(VK_BACK))
		{
			return true;
		}


	}



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
