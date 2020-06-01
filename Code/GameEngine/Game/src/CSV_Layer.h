#pragma once

#include <Engine.h>
#include <Graphics.h>
#include "CSV_Reader.h"

using namespace Engine;
using namespace Engine::Graphics;

class CSV_Layer : public Layer
{
public:
	CSV_Layer();
	virtual ~CSV_Layer() = default;;

	virtual void OnLoad() override;
	//virtual void OnEvent(Event& event) override;
	//virtual void OnUpdate(const Timestep timeStep) override;
	virtual void OnGuiDraw() override;
	//virtual void OnExit() override;

private:
	bool checkbox = true;

	void Option1();

	
	CSV_Reader CSVData; ///The Current data being used by the UI
};

