#pragma once
#include <raylib.h>


class PoolManager
{
public:
	static PoolManager* GetInstance()
	{
		if (!mInstance)
		{
			mInstance = new PoolManager();
		}
		return mInstance;
	}

private:
	PoolManager();
	static PoolManager* mInstance;
};
