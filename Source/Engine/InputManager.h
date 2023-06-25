#pragma once

#include <raylib.h>
#include <vector>

class InputManager
{
public:
	InputManager();
	float Input(int key_code);

	std::vector <int> inputs;
protected:
private:
};
	