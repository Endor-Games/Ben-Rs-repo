#include "CSV_Reader.h"
#include <random>
#include <imgui.h>
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

string CSV_Base::ReturnStringForWriting(std::string _string, bool endLine)
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

string CSV_Base::ReturnIntForWriting(int _int, bool endLine)
{
	std::string appendString = std::to_string(_int);

	if (endLine)
		appendString.append("\n");
	else
		appendString.append(",");

	return appendString;
}



bool CSV_Dialogue::LoadCSV(std::string fileLocation, bool removeSep)
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

	if(removeSep)
		ip.ignore(5000, '\n'); //Removes sep=, from loading

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

void CSV_Dialogue::RenderGUI()
{
	if (ImGui::CollapsingHeader("Dialogue"))
	{
		ImGui::TextWrapped(GetCurrentData()->FileName.c_str());

		//ImGui::Checkbox("TestCheckBox", &checkbox);


		ImGui::TextWrapped(GetCurrentData()->Dialogue.c_str());


		const float spacing = ImGui::GetStyle().ItemSpacing.x;
		static float buttonWidth = 100;
		float pos = 0;

		ImGui::NewLine();
		for (int i = 0; i < GetCurrentData()->responses.size(); i++)
		{
			pos += buttonWidth + spacing;

			ImGui::SameLine(0, 50);
			if (ImGui::Button(GetCurrentData()->responses[i].ResponseAsChar(), ImVec2(100, 50)))
				ChangeCurrentData(GetCurrentData()->responses[i].NextID);

			buttonWidth = ImGui::GetItemRectSize().x;

		}
	}


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




bool CSV_Enemies::LoadCSV(std::string fileLocation, bool removeSep)
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

	
	if(removeSep) //use if files include "sep=," this will remove it (because hannahs computer is wierd)
		ip.ignore(5000, '\n'); //Removes sep=, from loading
	
	ip.ignore(5000, '\n');//ignores first line which explains what each collumn does (until 5000 characters is met or it gets to the end of the line)

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
		ReadInt(ip, out.Attack);
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

void CSV_Enemies::RenderGUI()
{
	int LineSpacing = 0;

	if (ImGui::CollapsingHeader("Enemy"))
	{
		for (int i = 0; i < GetNumberOfEnemiesInData(); i++)
		{
			if (ImGui::CollapsingHeader(GetSpecificData(i)->Name.c_str()))
			{
				ImGui::TextWrapped(GetSpecificData(i)->Sprite.c_str());
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(GetSpecificData(i)->DeathSound.c_str());

				ImGui::TextWrapped("Encounter Rate: ");
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(std::to_string(GetSpecificData(i)->EncounterRate).c_str());

				ImGui::TextWrapped("Level: ");
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(std::to_string(GetSpecificData(i)->Level).c_str());

				ImGui::TextWrapped("HP: ");
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(std::to_string(GetSpecificData(i)->HP).c_str());

				ImGui::TextWrapped("Attack: ");
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(std::to_string(GetSpecificData(i)->Attack).c_str());

				ImGui::TextWrapped("Defence: ");
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(std::to_string(GetSpecificData(i)->Defence).c_str());

				ImGui::TextWrapped("Speed: ");
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(std::to_string(GetSpecificData(i)->Speed).c_str());

				ImGui::NewLine();
				for (int j = 0; j < GetSpecificData(i)->PossibleAttacks.size(); j++)
				{
					ImGui::SameLine(0, 50);
					std::string AppendString = GetSpecificData(i)->PossibleAttacks[j].AttackName;
					AppendString.append("\n Damage: ");
					AppendString.append(std::to_string(GetSpecificData(i)->PossibleAttacks[j].AttackDamage));
					AppendString.append("\n Attack Sound: ");
					AppendString.append(GetSpecificData(i)->PossibleAttacks[j].AttackSound);
					AppendString.append("\n Attack Rate: ");
					AppendString.append(std::to_string(GetSpecificData(i)->PossibleAttacks[j].AttackRate));

					if (ImGui::Button(AppendString.c_str(), ImVec2(150, 75)))
						CalculateAttack(i);

				}
			}
		}


	}



}

bool CSV_Enemies::WriteToCSV(std::string fileName)
{
	ofstream myFile(fileName);

	myFile << "Name (String),Sprite (String),Death Sound (String),Encounter rate (Int),Level (int),HP (int),Attack (int),Defence (int),Speed (int)"
		<<",Attack Name_0 (String),Attack Damage_0 (int),Attack Sound_0 (String),AttackRate_0 (int)"
		<<",Attack Name_1 (String),Attack Damage_1 (int),Attack Sound_1 (String),AttackRate_1 (int)"
		<<",Attack Name_2 (String),Attack Damage_2 (int),Attack Sound_2 (String),AttackRate_2 (int)\n"; //Writes the first line

	for (CSV_Enemy_struct& Enemy : m_CSVData)
	{
		string CSVLine = "";

		CSVLine.append(ReturnStringForWriting(Enemy.Name, false));
		CSVLine.append(ReturnStringForWriting(Enemy.Sprite, false));
		CSVLine.append(ReturnStringForWriting(Enemy.DeathSound, false));
		CSVLine.append(ReturnIntForWriting(Enemy.EncounterRate, false));
		CSVLine.append(ReturnIntForWriting(Enemy.Level, false));
		CSVLine.append(ReturnIntForWriting(Enemy.HP, false));
		CSVLine.append(ReturnIntForWriting(Enemy.Attack, false));
		CSVLine.append(ReturnIntForWriting(Enemy.Defence, false));
		CSVLine.append(ReturnIntForWriting(Enemy.Speed, false));



		int index = 0;

		for (CSV_Attack_struct& Attack : Enemy.PossibleAttacks)
		{

			if (Attack.AttackName != "Name Not Applicable")
			{
				CSVLine.append(ReturnStringForWriting(Attack.AttackName, false));
				CSVLine.append(ReturnIntForWriting(Attack.AttackDamage, false));
				CSVLine.append(ReturnStringForWriting(Attack.AttackSound, false));


				CSVLine.append(ReturnIntForWriting(Attack.AttackRate, index == 2));
			}
			else
			{
				CSVLine.append(ReturnStringForWriting("n/a", false));
				CSVLine.append(ReturnIntForWriting(0, index == 2));
			}
			index++;
		}

		while (index < 3)
		{
			CSVLine.append("\"<n/a>\",0,\"<n/a>\",");

			if (index != 2)
				CSVLine.append("0,");
			else
				CSVLine.append("0\n");

			index++;
		}



		myFile << CSVLine;
	}

	return false;
}

void CSV_Enemies::CalculateAttack(int AttackingEnemy)
{
	vector<int> AttackRates;

	for (CSV_Attack_struct Attacks : m_CSVData[AttackingEnemy].PossibleAttacks)
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
			cout << "Attack Decleared: " << m_CSVData[AttackingEnemy].PossibleAttacks[i].AttackName << "\n";

			i = 9999;
		}

	}

}
