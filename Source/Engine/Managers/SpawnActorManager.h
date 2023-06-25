#pragma once

#include <raylib.h>

class SpawnActorManager
{
public:
	static SpawnActorManager* GetInstance()
	{
		if (!mInstance)
		{
			mInstance = new SpawnActorManager();
		}
		return mInstance;
	}

	static void SpawnActor();

private:
	SpawnActorManager();
	static SpawnActorManager* mInstance;
};

