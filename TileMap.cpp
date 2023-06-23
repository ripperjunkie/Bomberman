#include "TileMap.h"
#include "Entity.h"
#include "iostream"
#include "raymath.h"

#undef DEBUG

TileMap::TileMap(unsigned int start_pos_x_, unsigned int start_pos_y_, int amountX_, unsigned int amountY_, unsigned int size_)
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
		tiles[i].x = start_pos_x_;
		tiles[i].y = start_pos_y_;
	}

	float store_y = start_pos_y_;

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
			tiles[i].x = start_pos_x_;
			tiles[i].y = store_y;
		}
	}
}

void TileMap::Draw()
{
#ifdef DEBUG
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
		DrawText(tile_number.c_str(), tiles[i].x, tiles[i].y, 20, WHITE);
	}
#endif
	GetFrameRate();
}


void TileMap::GetFrameRate()
{
	std::string frame = "FPS: ";
	frame += std::to_string(GetFPS());
	DrawText(frame.c_str(), 0, 0, 24, YELLOW);
}

void TileMap::Update()
{
	Draw();
		
	for (auto element : entities)
	{
		element->Update();
	}

}

void TileMap::RegisterEntity(Entity& entityToRegister)
{
	entities.push_back(&entityToRegister);
}