#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct Dialogue_Response_struct
{
	std::string ResponseText; //The text prompt that appears on the buttons
	int NextID; //The ID of the next piece of dialogue

	void PrintAsText()
	{
		std::cout << "Response Text: " << ResponseText << " Next ID: " << NextID << "\n";
	}

	const char* ResponseAsChar()
	{
		return ResponseText.c_str();
	}
};



struct Dialogue_struct
{
	int ID; //The location of the Dialogue within the Array
	std::string FileName; //The name of the person who is talking (or what dialogue option is being used)
	std::string Dialogue; //The Text that pops up in the main box

	std::vector<Dialogue_Response_struct> responses; //The options that the player can decide to make

	void PrintFullCSVData()
	{
		std::cout << "Name: " << FileName << " Price: " << Dialogue << "\n";
		for (int i = 0; i < responses.size(); i++)
		{
			responses[i].PrintAsText();
		}

		std::cout << "\n";

	}

};

class CSV_Base
{
public :
	virtual bool LoadCSV(std::string fileLocation) = 0;

protected:
	void ReadString(std::ifstream& _ip, std::string& _string); //Automaticlly reads string from CSV
	void ReadStringAndEndLine(std::ifstream& _ip, std::string& _string); //Automaticlly reads string from CSV and then moves on to next line

	void ReadInt(std::ifstream& _ip, int& _int); //Automaticly reads value as string then changes it into an int
	void ReadIntAndEndLine(std::ifstream& _ip, int& _int);
};

class CSV_Dialogue : CSV_Base
{
public:
	virtual bool LoadCSV(std::string fileLocation) override;
	Dialogue_struct* GetCurrentData() { return m_CurrentData; }
	std::string GetFileName() { return m_CurrentData->FileName; }
	std::string GetFileNameAsChar() { return m_CurrentData->FileName.c_str(); }
	std::string GetDialogue() { return m_CurrentData->Dialogue; }
	std::string GetDialogueAsChar() { return m_CurrentData->Dialogue.c_str(); }

	Dialogue_Response_struct& GetResponse() { return m_CurrentData->responses[0]; }
	Dialogue_Response_struct& GetResponse(int _specificResponse) { return m_CurrentData->responses[_specificResponse]; }
	std::string GetResponseText() { return m_CurrentData->responses[0].ResponseText; }
	std::string GetResponseText(int _specificResponse) { return m_CurrentData->responses[_specificResponse].ResponseText; }
	const char* GetResponseTextAsChar() { return m_CurrentData->responses[0].ResponseText.c_str(); }
	const char* GetResponseTextAsChar(int _specificResponse) { return m_CurrentData->responses[_specificResponse].ResponseText.c_str(); }
	int getNextID() { return m_CurrentData->responses[0].NextID; }
	int getNextID(int _specificResponse) { return m_CurrentData->responses[_specificResponse].NextID; }

	///Changes data based on input
	void ChangeCurrentData(int _dataIndex) { m_CurrentData = &m_CSVData[_dataIndex]; }


	
private:
	std::vector<Dialogue_struct> m_CSVData;
	Dialogue_struct* m_CurrentData; ///the current data being stored in 
	

};


struct CSV_Attack_struct
{
	std::string AttackName;
	int AttackDamage;
	std::string AttackSound; //Temporarily made a string until sound loading is understood
	int AttackRate; //How likely the attack is to be chosen
};

struct CSV_Enemy_struct
{
	int ID; //The location of the Enemy within the Array
	std::string Name;
	std::string Sprite; //(Temporarily made a string until image loading is added)
	std::string DeathSound; //Temporarily made a string until sound loading is understood
	int EncounterRate; //The likelyhood of encountering the enemy
	int Level; //Whether the enemy can be encountered (depending on players level)
	int HP;
	int Defence;
	int Speed; //Determins when the enemy will declare an attack against the player (might be changed to an attack specific speed)

	std::vector<CSV_Attack_struct> PossibleAttacks;
};



class CSV_Enemies : CSV_Base
{
public:
	virtual bool LoadCSV(std::string fileLocation) override;

private:
	std::vector<CSV_Enemy_struct> m_CSVData;
	CSV_Enemy_struct* m_CurrentData;
};
