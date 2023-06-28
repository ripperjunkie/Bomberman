#pragma once
#include "Engine/Public/Utils.h"

class Grid
{
public:
	Grid(unsigned int start_pos_x_, unsigned int start_pos_y_, int amountX_, unsigned int amountY_, unsigned int size_);

	int amount_x;
	int amount_y;
	int size;

	//why allocating Rectangles instead of actual vectors and such? Because rectangles already holds vectors and have enough
	//necessary information such as anchor point, position(X,Y), size which can act as a tile set
	std::vector<Rectangle> tiles;
	std::string tile_number;

	void Draw();

	/*Pass the row and column number and returns the position of both */
	Vector2 GetGrid(int row, int column) const
	{
		return { tiles[column].x, tiles[(amount_x * row) + column].y };
	}
};

