#include "Engine.h"
#include "CustomLayer.h"
#include "CSV_Layer.h"

using namespace Engine;

class Tatooine : public Application
{
public:
	Tatooine() : Application("Tatooine")
	{ 
		PushLayer(new CustomLayer()); 
		PushLayer(new CSV_Layer());

	}
};

int main()
{
	std::unique_ptr<Tatooine> app = std::make_unique<Tatooine>();
	app->Run();
}
