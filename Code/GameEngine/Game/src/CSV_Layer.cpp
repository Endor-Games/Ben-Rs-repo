#include "CSV_Layer.h"

void CSV_Layer::OnLoad()
{
	bool loading;
	loading = CSVData.LoadCSV("src/TestCSV.csv");
	loading = CSVEnemyData.LoadCSV("src/TestEnemies.csv");

	loading;
}

//void CSV_Layer::OnExit()
//{
//
//}
//
//void CSV_Layer::OnEvent(Event& event)
//{
//
//}
//
//void CSV_Layer::OnUpdate(const Timestep timeStep)
//{
//
//}

CSV_Layer::CSV_Layer()
{
}

void CSV_Layer::OnGuiDraw()
{

	CSVData.GetCurrentData()->PrintFullCSVData();

	ImGui::Begin("CSV_Test");

	if (ImGui::CollapsingHeader("Dialogue"))
	{
		ImGui::TextWrapped(CSVData.GetCurrentData()->FileName.c_str());

		//ImGui::Checkbox("TestCheckBox", &checkbox);


		ImGui::TextWrapped(CSVData.GetCurrentData()->Dialogue.c_str());


		const float spacing = ImGui::GetStyle().ItemSpacing.x;
		static float buttonWidth = 100;
		float pos = 0;

		ImGui::NewLine();
		for (int i = 0; i < CSVData.GetCurrentData()->responses.size(); i++)
		{
			pos += buttonWidth + spacing;

			ImGui::SameLine(0, 50);
			if (ImGui::Button(CSVData.GetCurrentData()->responses[i].ResponseAsChar(), ImVec2(100, 50)))
				CSVData.ChangeCurrentData(CSVData.GetCurrentData()->responses[i].NextID);

			buttonWidth = ImGui::GetItemRectSize().x;
			
		}
	}

	int LineSpacing = 0;
	

	if (ImGui::CollapsingHeader("Enemy"))
	{
		for (int i = 0; i < CSVEnemyData.GetNumberOfEnemiesInData(); i++)
		{
			if (ImGui::CollapsingHeader(CSVEnemyData.GetSpecificData(i)->Name.c_str()))
			{
				ImGui::TextWrapped(CSVEnemyData.GetSpecificData(i)->Sprite.c_str());
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(CSVEnemyData.GetSpecificData(i)->DeathSound.c_str());

				ImGui::TextWrapped("Encounter Rate: ");
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(std::to_string(CSVEnemyData.GetSpecificData(i)->EncounterRate).c_str());

				ImGui::TextWrapped("Level: ");
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(std::to_string(CSVEnemyData.GetSpecificData(i)->Level).c_str());

				ImGui::TextWrapped("HP: ");
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(std::to_string(CSVEnemyData.GetSpecificData(i)->HP).c_str());

				ImGui::TextWrapped("Defence: ");
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(std::to_string(CSVEnemyData.GetSpecificData(i)->Defence).c_str());

				ImGui::TextWrapped("Speed: ");
				ImGui::SameLine(0, LineSpacing);
				ImGui::TextWrapped(std::to_string(CSVEnemyData.GetSpecificData(i)->Speed).c_str());

				ImGui::NewLine();
				for (int j = 0; j < CSVEnemyData.GetSpecificData(i)->PossibleAttacks.size(); j++)
				{
					ImGui::SameLine(0, 50);
					std::string AppendString = CSVEnemyData.GetSpecificData(i)->PossibleAttacks[j].AttackName;
					AppendString.append("\n Damage: ");
					AppendString.append(std::to_string(CSVEnemyData.GetSpecificData(i)->PossibleAttacks[j].AttackDamage));
					AppendString.append("\n Attack Sound: ");
					AppendString.append(CSVEnemyData.GetSpecificData(i)->PossibleAttacks[j].AttackSound);
					AppendString.append("\n Attack Rate: ");
					AppendString.append(std::to_string(CSVEnemyData.GetSpecificData(i)->PossibleAttacks[j].AttackRate));

					if (ImGui::Button(AppendString.c_str(), ImVec2(150, 75)));

					
				}
			}
		}


	}



	ImGui::End();
}

void CSV_Layer::Option1()
{
	checkbox = !checkbox;
}
