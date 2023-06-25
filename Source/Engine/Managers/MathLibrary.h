#pragma once

#include <iostream>
#include "Engine/GameFramework/Actor.h"

namespace MathLibrary
{
	void test(int a = 0)
	{
		std::cout << a << std::endl;
	}


	float length(TileMapCoordinates& one)
	{
		return static_cast<float>(sqrt((one.x * one.x) + (one.y * one.y)));
	}




}
