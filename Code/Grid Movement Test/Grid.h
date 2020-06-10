#pragma once
#include "Maths.h"
#include <iostream>
#include <vector>

struct Tile
{
	Float2 Position;
	std::string TileType;


	void readTile()
	{
		std::cout << "Position = "<< Position.x << " x " << Position.y<< " TileType = "<< TileType << "\n";
	}
};

class Grid
{
public:

	void CreateGrid(int size);

	//Moves the Players location based on The Grid
	void MovePlayer(Float2& PlayerPos, std::string input);



private:
	std::vector<std::vector<Tile>>m_Grid;
	int MaxSize;



};

