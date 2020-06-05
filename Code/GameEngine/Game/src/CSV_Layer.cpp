#include "CSV_Layer.h"

void CSV_Layer::OnLoad()
{
	bool loading;
	loading = CSVData.LoadCSV("src/TestCSV.csv", false);
	loading = CSVEnemyData.LoadCSV("src/TestEnemies.csv", false);
	loading = CSVData.WriteToCSV("src/WritingTest.csv");

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

	//CSVData.GetCurrentData()->PrintFullCSVData();

	ImGui::Begin("CSV_Test");

	CSVData.RenderGUI();
	CSVEnemyData.RenderGUI();



	ImGui::End();
}

void CSV_Layer::Option1()
{
	checkbox = !checkbox;
}
