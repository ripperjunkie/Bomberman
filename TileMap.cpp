#include "TileMap.h"

#include "Entity.h"


TileMap::TileMap(int amountX_, unsigned int amountY_, unsigned int size_)
{
	amount_x = amountX_;
	amount_y = amountY_;
	size = size_;
	tile_number = '0';

	for (size_t i = 0; i < amount_x * amount_y; i++)
	{
		tiles.push_back(Rectangle());
		tiles[i].width = size;
		tiles[i].height = size;
		tiles[i].x = 0.f;
		tiles[i].y = 0.f;
	}

	float store_y = 0.f;

	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (i != 0)
		{
			tiles[i].x = tiles[i - 1].x + size + 1.f;
			tiles[i].y = store_y;
		}
		if (i % amount_x == 0 && i != 0)
		{
			store_y = tiles[i - 1].y + size + 1.f;
			tiles[i].x = 0;
			tiles[i].y = store_y;
		}
	}
}

void TileMap::Draw()
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		DrawRectangleRec(tiles[i], RED);
		if (i % 2 == 0 && i != 0)
		{
			DrawRectangleRec(tiles[i], BLUE);
		}
		if (i == 0)
		{
			DrawRectangleRec(tiles[i], BLUE);
		}
		tile_number = std::to_string(i);
		//DrawText(tile_number.c_str(), tiles[i].x, tiles[i].y, 20, WHITE);
	}


}
