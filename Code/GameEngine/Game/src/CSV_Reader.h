#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct Dialogue_Response_struct
{
	std::string ResponseText; //The text prompt that appears on the buttons
	int NextID; //The ID of the next piece of dialogue

	//Prints the contents of the structure to console, used for testing purposes
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

	//Prints the contents of the structure to console, used for testing purposes
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
	virtual bool LoadCSV(std::string fileLocation, bool removeSep) = 0;
	virtual void RenderGUI() = 0;
	virtual bool WriteToCSV(std::string fileName) = 0;
	//virtual bool WriteToCSV(std::string fileName) = 0;

protected:
	void ReadString(std::ifstream& _ip, std::string& _string); //Automaticlly reads string from CSV
	void ReadStringAndEndLine(std::ifstream& _ip, std::string& _string); //Automaticlly reads string from CSV and then moves on to next line

	void ReadInt(std::ifstream& _ip, int& _int); //Automaticly reads value as string then changes it into an int
	void ReadIntAndEndLine(std::ifstream& _ip, int& _int);

	//Adds CSV specific cases to string for writing it to the file
	std::string ReturnStringForWriting(std::string _string, bool endLine);
	//Changes int value to string then adds CSV specific cases for it to write to file
	std::string ReturnIntForWriting(int _int, bool endLine);


};

class CSV_Dialogue : CSV_Base
{
public:
	virtual bool LoadCSV(std::string fileLocation, bool removeSep) override;
	virtual void RenderGUI();

	//CSV Writing Begin
	//Takes the contents of the dialogue and writes it to a CSV (Used mainly for testing)
	virtual bool WriteToCSV(std::string fileName) override;


	//CSV Writing End

	Dialogue_struct* GetCurrentData() { return m_CurrentData; }
	const std::string GetFileName() { return m_CurrentData->FileName; }
	const std::string GetFileNameAsChar() { return m_CurrentData->FileName.c_str(); }
	const std::string GetDialogue() { return m_CurrentData->Dialogue; }
	const std::string GetDialogueAsChar() { return m_CurrentData->Dialogue.c_str(); }

	const Dialogue_Response_struct GetResponse() { return m_CurrentData->responses[0]; }
	const Dialogue_Response_struct GetResponse(int _specificResponse) { return m_CurrentData->responses[_specificResponse]; }


	const int getNextID() { return m_CurrentData->responses[0].NextID; }
	const int getNextID(int _specificResponse) { return m_CurrentData->responses[_specificResponse].NextID; }

	///Changes data based on input
	void ChangeCurrentData(int _dataIndex)
	{ 
		if(_dataIndex < m_CSVData.size())
			m_CurrentData = &m_CSVData[_dataIndex]; 
	}


	
private:
	std::vector<Dialogue_struct> m_CSVData; //Contains all the Dialogue loaded from the CSV File
	Dialogue_struct* m_CurrentData; //The current data being used by the UI
	

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
	int Attack;
	int Defence;
	int Speed; //Determins when the enemy will declare an attack against the player (might be changed to an attack specific speed)

	std::vector<CSV_Attack_struct> PossibleAttacks; //An array of all the possible attacks the enemy can make
};



class CSV_Enemies : CSV_Base
{
public:
	virtual bool LoadCSV(std::string fileLocation, bool removeSep) override;
	virtual void RenderGUI();
	virtual bool WriteToCSV(std::string fileName) override;

	//Returns data currently being used
	CSV_Enemy_struct* GetCurrentData() { return m_CurrentData; } 
	//Gets Data from array
	CSV_Enemy_struct* GetSpecificData(int _dataIndex) { return &m_CSVData[_dataIndex]; }
	//returns the name of the enemy
	std::string GetName() { return m_CurrentData->Name; }
	//Returns the name of the enemy as a "const char*"
	const char* GetNameAsChar() { return m_CurrentData->Name.c_str(); }
	//Returns the enemy's sprite (Currently returns the file location as a string however it will be replaced by the actual sprite)
	std::string GetSprite() { return m_CurrentData->Sprite; }
	//Returns the file location of the sprite (as a "const char*") used for test purposes
	const char* GetSpriteAsChar() { return m_CurrentData->Sprite.c_str(); }

	std::string GetDeathSound() { return m_CurrentData->DeathSound; }
	const char* GetDeathSoundAsChar() { return m_CurrentData->DeathSound.c_str(); }
	const int GetEncounterRate() { return m_CurrentData->EncounterRate; }
	const int GetLevel() { return m_CurrentData->Level; }
	const int GetHP() { return m_CurrentData->HP; }
	const int GetDefence() { return m_CurrentData->Defence; }
	const int GetSpeed() { return m_CurrentData->Speed; }

	CSV_Attack_struct GetAttack() { return m_CurrentData->PossibleAttacks[0]; }
	CSV_Attack_struct GetAttack(int _specificAttack) { return m_CurrentData->PossibleAttacks[_specificAttack]; }

	const int GetNumberOfEnemiesInData() { return m_CSVData.size(); }

	//A test function to determin what attack the enemy will use against the player using the total attack rate
	void CalculateAttack(int AttackingEnemy);

private:
	std::vector<CSV_Enemy_struct> m_CSVData;
	CSV_Enemy_struct* m_CurrentData;
};
