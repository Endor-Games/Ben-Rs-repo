#include "CSV_Layer.h"

void CSV_Layer::OnLoad()
{
	bool loading;
	loading = CSVData.LoadCSV("src/TestCSV.csv");

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

	CSVData.GetCurrentData()->ReadFullCSV();

	ImGui::Begin("CSV_Test");
	ImGui::TextWrapped(CSVData.GetCurrentData()->FileName.c_str());
	
	ImGui::Checkbox("TestCheckBox", &checkbox);


	ImGui::TextWrapped(CSVData.GetCurrentData()->Dialogue.c_str());




	const float spacing = ImGui::GetStyle().ItemSpacing.x;
	static float buttonWidth = 100;
	float pos = 0;

	//ImGui::
	for (int i = 0; i < CSVData.GetCurrentData()->responses.size(); i++)
	{
		 pos += buttonWidth + spacing;
		 

		if (ImGui::Button(CSVData.GetCurrentData()->responses[i].ResponseAsChar(), ImVec2(100, 50)))
			CSVData.ChangeCurrentData(CSVData.GetCurrentData()->responses[i].NextID);

		buttonWidth = ImGui::GetItemRectSize().x;
		ImGui::SameLine(0, 50);
	}


	ImGui::End();
}

void CSV_Layer::Option1()
{
	checkbox = !checkbox;
}
