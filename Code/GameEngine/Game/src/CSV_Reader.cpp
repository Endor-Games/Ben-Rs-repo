#include "CSV_Reader.h"

using namespace std;

void CSV_Base::ReadString(std::ifstream& _ip, std::string& _string)
{
	//ignores all characters until it reaches the start of the string
	_ip.ignore(2, '<');
	//reads string
	getline(_ip, _string, '>');
	//sets to next collumn
	_ip.ignore(2, ',');
}

void CSV_Base::ReadStringAndEndLine(std::ifstream& _ip, std::string& _string)
{
	//ignores all characters until it reaches the start of the string
	_ip.ignore(2, '<');
	//reads string
	getline(_ip, _string, '>');
	//sets to next collumn
	_ip.ignore(2, '\n');
}

void CSV_Base::ReadInt(std::ifstream& _ip, int& _int)
{
	string TempString;

	getline(_ip, TempString, ',');
	
}

void CSV_Base::ReadIntAndEndLine(std::ifstream& _ip, int& _int)
{
	string TempString;

	getline(_ip, TempString, '\n');
}

bool CSV_Dialogue::LoadCSV(string fileLocation)
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
		Dialogue_struct out;
		string ResponseCheck;

		out.ID = Index;
		ReadString(ip, out.FileName);


		ReadString(ip, out.Dialogue);


		for (int i = 0; i < 4; i++)
		{
			Dialogue_Response_struct Response;
			ReadString(ip, ResponseCheck);

			if (ResponseCheck == "n/a" || ResponseCheck == "")
			{
				if (i == 0)
				{
					Response.ResponseText = "Next";
					if (i == 3)
						ReadIntAndEndLine(ip, Response.NextID);
					else
						ReadInt(ip, Response.NextID);


					out.responses.push_back(Response);
				}


				ip.ignore(5000, '\n');
				
				i = 10;
			}
			else
			{

				Response.ResponseText = ResponseCheck;
				if (i == 3)
					ReadIntAndEndLine(ip, Response.NextID);
				else
					ReadInt(ip, Response.NextID);

				out.responses.push_back(Response);
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
