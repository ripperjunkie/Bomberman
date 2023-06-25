#pragma once

#include <vector>
#include <string>
#include <unordered_map>

//Simple struct that holds two values for rec crop location when cycling between animation
struct RecCropLocation
{
	float x;
	float y;
};

struct AnimationData
{
	std::vector<RecCropLocation>& rec_crop_location;
};

struct TileMapCoordinates
{
public:
	int x;
	int y;

	TileMapCoordinates(int tileMapX_, int tileMapY_)
	{
		x = tileMapX_;
		y = tileMapY_;
	}

};

inline TileMapCoordinates operator+(const TileMapCoordinates& one, const TileMapCoordinates& second)
{
	const int x = one.x + second.x;
	const int y = one.y + second.y;
	return TileMapCoordinates(x, y);
}

inline TileMapCoordinates operator-(const TileMapCoordinates& one, const TileMapCoordinates& second)
{
	const int x = one.x - second.x;
	const int y = one.y - second.y;
	return TileMapCoordinates(x, y);
}

inline TileMapCoordinates operator/(const TileMapCoordinates& one, const float second)
{
	const int x = one.x / second;
	const int y = one.y / second;
	return TileMapCoordinates(x, y);
}


//Acting as collision filter
enum class ECollisionType : uint8_t
{
	IGNORE,
	BLOCKING,
	OVERLAP
};

enum class EObjectMovType : uint8_t
{
	STATIC,
	MOVABLE
};