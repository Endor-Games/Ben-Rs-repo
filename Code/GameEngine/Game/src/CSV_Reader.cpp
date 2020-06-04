#include "CSV_Reader.h"
#include <random>
using namespace std;

void CSV_Base::ReadString(std::ifstream& _ip, std::string& _string)
{
	
	_ip.ignore(2, '<'); //ignores all characters until it reaches the start of the string

	getline(_ip, _string, '>'); 	//reads string
	
	_ip.ignore(2, ','); //sets to next collumn
}

void CSV_Base::ReadStringAndEndLine(std::ifstream& _ip, std::string& _string)
{
	
	_ip.ignore(2, '<'); //ignores all characters until it reaches the start of the string
	
	getline(_ip, _string, '>'); //reads string

	_ip.ignore(2, '\n'); //sets to next collumn
}

void CSV_Base::ReadInt(std::ifstream& _ip, int& _int)
{
	string TempString;

	getline(_ip, TempString, ','); //Reads Line up to the next comma as String

	_int = stoi(TempString); //Changes String Value read in from file to an int
	
}

void CSV_Base::ReadIntAndEndLine(std::ifstream& _ip, int& _int)
{
	string TempString;

	getline(_ip, TempString, '\n'); 

	_int = stoi(TempString); //Changes String Value read in from file to an int
}

bool CSV_Dialogue::LoadCSV(std::string fileLocation)
{
	ifstream ip(fileLocation);

	if (!ip.is_open())
	{
		cout << "ERROR: File has failed to Open" << '\n';
		return false;
	}

	//Clears data before 
	m_CSVData.clear();
	m_CurrentData = nullptr;

	
	ip.ignore(5000, '\n'); //ignores first line which explains what each collumn does (until 5000 characters is met or it gets to the end of the line)

	int Index = 0;
	while (ip.peek() != EOF)
	{
		Dialogue_struct out;
		string ResponseCheck;

		out.ID = Index;
		ReadString(ip, out.FileName);

		ReadString(ip, out.Dialogue);


		for (int i = 0; i < 4; i++)
		{
			Dialogue_Response_struct Response;
			ReadString(ip, ResponseCheck);

			if (ResponseCheck == "n/a" || ResponseCheck == "") //If there is  no valid Response skip the rest of the line
			{
				if (i == 0) //If the invalid line is the first line, set it to a default response
				{
					Response.ResponseText = "Next";
					Response.NextID = Index + 1;

					out.responses.push_back(Response);
				}


				ip.ignore(5000, '\n');
				
				i = 10; //End the Loop
			}
			else
			{

				Response.ResponseText = ResponseCheck;

				if (i == 3) //Checks whether it is the last possible option then ends the line if it is
					ReadIntAndEndLine(ip, Response.NextID);
				else
					ReadInt(ip, Response.NextID);

				out.responses.push_back(Response);

				Response.NextID = 0;
				Response.ResponseText = "";
			}
			
		}

		m_CSVData.push_back(out);
		Index++;
	}

	//sets current data to the first part of the array
	m_CurrentData = &m_CSVData[0];




	ip.close();
	ip.clear();

	return true;
}

bool CSV_Dialogue::WriteToCSV(std::string fileName)
{
	ofstream myFile(fileName);

	myFile << "Name,Dialogue,Response_Text_0,Response_ID_0,Response_Text_1,Response_ID_1,Response_Text_2,Response_ID_2,Response_Text_3,Response_ID_3 \n"; //Writes the first line

	for (Dialogue_struct& Dialogue : m_CSVData)
	{
		string CSVLine = "";

		CSVLine.append(ReturnStringForWriting(Dialogue.FileName, false));
		CSVLine.append(ReturnStringForWriting(Dialogue.Dialogue, false));
		

		int index = 0;
		for (Dialogue_Response_struct& Response : Dialogue.responses)
		{

			if (Response.ResponseText != "Next")
			{
				CSVLine.append(ReturnStringForWriting(Response.ResponseText, false));
				CSVLine.append(ReturnIntForWriting(Response.NextID, index == 3));
			}
			else
			{
				CSVLine.append(ReturnStringForWriting("n/a", false));
				CSVLine.append(ReturnIntForWriting(0, index == 3));
			}
				

			index++;

		}

				while (index < 4)
				{
					CSVLine.append("\"<n/a>\",");

					if (index != 3)
						CSVLine.append("0,");
					else
						CSVLine.append("0\n");

					index++;
				}


		
		myFile << CSVLine;
	}

	return false;
}

string CSV_Dialogue::ReturnStringForWriting(std::string _string, bool endLine)
{
	std::string appendString = "\"<";
	appendString.append(_string);
	appendString.append(">\"");

	if (endLine)
		appendString.append("\n");
	else
		appendString.append(",");

	return appendString;

}

string CSV_Dialogue::ReturnIntForWriting(int _int, bool endLine)
{
	std::string appendString = std::to_string(_int);

	if (endLine)
		appendString.append("\n");
	else
		appendString.append(",");

	return appendString;
}



bool CSV_Enemies::LoadCSV(std::string fileLocation)
{
	ifstream ip(fileLocation);

	if (!ip.is_open())
	{
		cout << "ERROR: File has failed to Open" << '\n';
		return false;
	}

	//Clears data before 
	m_CSVData.clear();
	m_CurrentData = nullptr;

	//ignores first line which explains what each collumn does (until 5000 characters is met or it gets to the end of the line)
	ip.ignore(5000, '\n');

	int Index = 0;
	while (ip.peek() != EOF)
	{
		CSV_Enemy_struct out;
		string SpriteLocation;
		string DeathSoundLocation;

		out.ID = Index;
		ReadString(ip, out.Name);

		//Loading The Enemy Sprite
		ReadString(ip, SpriteLocation);
		out.Sprite = SpriteLocation; //Replace with loading in the sprite

		//Loading the Enemy's Death Sound
		ReadString(ip, DeathSoundLocation);
		out.DeathSound = DeathSoundLocation; //Replace with loading in the Sound file

		ReadInt(ip, out.EncounterRate);
		ReadInt(ip, out.Level);
		ReadInt(ip, out.HP);
		ReadInt(ip, out.Defence);
		ReadInt(ip, out.Speed);


		for (int i = 0; i < 3; i++)
		{
			CSV_Attack_struct Attack;
			string AttackName;
			ReadString(ip, AttackName);

			if (AttackName == "n/a" || AttackName == "")
			{
				if (i == 0)
				{
					Attack.AttackName = "Name Not Applicable";
					Attack.AttackDamage = 0;
					Attack.AttackSound = "Non Applicable";
					Attack.AttackRate = 0;

					out.PossibleAttacks.push_back(Attack);
				}

				ip.ignore(5000, '\n');
			}
			else
			{
				Attack.AttackName = AttackName;

				ReadInt(ip, Attack.AttackDamage);

				//Load Attack Sound
				string AttackSound;
				ReadString(ip, AttackSound);
				Attack.AttackSound = AttackSound; //Replace with loading in the Sound file


				if (i == 2)
					ReadIntAndEndLine(ip, Attack.AttackRate);
				else
					ReadInt(ip, Attack.AttackRate);

				out.PossibleAttacks.push_back(Attack);
			}

		}


		m_CSVData.push_back(out);
		Index++;
	}

	//sets current data to the first part of the array
	m_CurrentData = &m_CSVData[0];

	ip.close();
	ip.clear();

	return true;


}

void CSV_Enemies::CalculateAttack()
{
	vector<int> AttackRates;

	for (CSV_Attack_struct Attacks : m_CurrentData->PossibleAttacks)
	{
		AttackRates.push_back(Attacks.AttackRate);
	}

	int totalAttackRate = 0;

	for (int i = 0; i < AttackRates.size(); i++)
	{
		totalAttackRate += AttackRates[i];
	}


	int generatedNumber = rand() % (totalAttackRate + 1);

	cout << "rand Attack = " << generatedNumber << "\n";


	
	int MaxAttackChance = 0;

	for (int i = 0; i < AttackRates.size(); i++)
	{
		MaxAttackChance += AttackRates[i];
		if (generatedNumber <= MaxAttackChance)
		{
			cout << "Attack Decleared: " << m_CurrentData->PossibleAttacks[i].AttackName << "\n";

			i = 9999;
		}

	}

}
