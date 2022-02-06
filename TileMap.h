#pragma once
// tile map will act as the world only then we will place actual 
// entities in thereto perform some sort of role

#include <raylib.h>
#include <vector>
#include <string>

class Entity;

class TileMap
{
public:
	TileMap(int amountX_, unsigned int amountY_, unsigned int size_);

	int amount_x;
	int amount_y;
	int size;

	//why allocating Rectangles instead of actual vectors and such? Because rectangles already holds vectors and have enough
	//necessary information such as anchor point, position(X,Y), size which can act as a tile set
	std::vector<Rectangle> tiles;
	std::vector<Entity> entities;
	std::string tile_number;

	void Draw();
};

