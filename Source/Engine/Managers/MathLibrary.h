#pragma once

#include <iostream>
#include "Engine/GameFramework/Actor.h"

namespace MathLibrary
{
	float length(TileMapCoordinates& one)
	{
		return static_cast<float>(sqrt((one.x * one.x) + (one.y * one.y)));
	}




}
