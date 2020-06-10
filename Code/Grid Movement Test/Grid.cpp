#include "Grid.h"
#include <random>
using namespace std;

void Grid::CreateGrid(int size)
{

	MaxSize = size;

	m_Grid.resize(size);
	for (int i = 0; i < m_Grid.size(); i++)
	{
		m_Grid[i].resize(size);

	}

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			Tile tile;

			tile.Position = Float2(x, y);
			
			bool random = rand() % 2;


			if (random)
				tile.TileType = "Ground";
			else
				tile.TileType = "Ground"; //"Water" can be used to prevent player movement


			tile.readTile();

			m_Grid[x][y] = tile;
			
		}
	}

}

void Grid::MovePlayer(Float2& PlayerPos, string input)
{
	Tile* tile;


	if (input == "W")
	{
		if (PlayerPos.y + 1 >= MaxSize)
			cout << "Cannot Move in this Direction. The World Has Ended";
		else
		{
			tile = &m_Grid[PlayerPos.x][PlayerPos.y + 1];

			if (tile->TileType == "Water")
			{
				cout << "Cannot Move in this Direction. The Player Cannot Swim";
			}
			else
			{
				PlayerPos = tile->Position;
				cout << "Player has moved";
			}
		}

	}
	else if (input == "S")
	{
		if (PlayerPos.y - 1 < 0)
			cout << "Cannot Move in this Direction. The World Has Ended";
		else
		{
			tile = &m_Grid[PlayerPos.x][PlayerPos.y - 1];

			if (tile->TileType == "Water")
			{
				cout << "Cannot Move in this Direction. The Player Cannot Swim";
			}
			else
			{
				PlayerPos = tile->Position;
				cout << "Player has moved";
			}
		}
	}
	else if (input == "A")
	{
		if (PlayerPos.x - 1 < 0)
			cout << "Cannot Move in this Direction. The World Has Ended";
		else
		{
			tile = &m_Grid[PlayerPos.x - 1][PlayerPos.y];

			if (tile->TileType == "Water")
			{
				cout << "Cannot Move in this Direction. The Player Cannot Swim";
			}
			else
			{
				PlayerPos = tile->Position;
				cout << "Player has moved";
			}
		}
	}
	else if (input == "D")
	{
		if (PlayerPos.x + 1 >= MaxSize)
			cout << "Cannot Move in this Direction. The World Has Ended";
		else
		{
			tile = &m_Grid[PlayerPos.x + 1][PlayerPos.y];

			if (tile->TileType == "Water")
			{
				cout << "Cannot Move in this Direction. The Player Cannot Swim";
			}
			else
			{
				PlayerPos = tile->Position;
				cout << "Player has moved";
			}
		}
	}
	else
		cout << "Bad input. Player Has Not moved";
}
