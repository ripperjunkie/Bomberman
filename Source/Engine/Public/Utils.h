#pragma once

// c++ standard libraries
#include <cmath>
#include <memory>
#include <thread>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

// raylib libraries
#include <raylib.h>
#include <raymath.h>

#define LOG(x) std::cout << x << std::endl
#define SCREEN_X 1280   
#define SCREEN_Y 720
#define TILE_WIDTH 15  //deprecated
#define TILE_HEIGHT 13  //deprecated
#define TILE_SIZE 32
#define LOG(x) std::cout << x << std::endl
#define PLAYER 17
#define ENEMY_A 25
#define BRICK 342
#define CLEAR_CLS system("cls");

