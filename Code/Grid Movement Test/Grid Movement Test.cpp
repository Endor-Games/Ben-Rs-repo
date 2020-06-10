// Grid Movement Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Grid.h"

int main()
{
	bool programRuning = true;

    std::cout << "Hello World!\n";

	Grid grid;
	Float2 Position(0, 0);
	std::string input;
	int gridSize;

	std::cout << "How Large is the Grid??:      ";
	std::cin >> gridSize;

	grid.CreateGrid(gridSize);


	while (programRuning)
	{
		std::cout << "\n Player Location = " << Position.x << " X " << Position.y << " Please Enter direction for movement   ";

		std::cin >> input; //Read Player Input

		grid.MovePlayer(Position, input);
	}

}
