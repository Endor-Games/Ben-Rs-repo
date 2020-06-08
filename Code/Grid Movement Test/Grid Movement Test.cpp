// Grid Movement Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Grid.h"

int main()
{
	bool programRuning = true;

    std::cout << "Hello World!\n";

	Grid grid;

	grid.CreateGrid(5);
	Float2 Position(0, 0);

	std::string input;

	while (programRuning)
	{
		std::cout << "\n Player Location = " << Position.x << " X " << Position.y << " Please Enter direction for movement   ";

		std::cin >> input;

		grid.MovePlayer(Position, input);
	}

}
