#pragma once

#include "Engine/GameFramework/Actor.h"

class Environment : public Actor
{
public:
	Environment() : Actor()
	{		
		mEntityTexture.width = 512.f;
		mEntityTexture.height = 832.f;
		mRecCropEntityTexture.x = 160.f;
		mRecCropEntityTexture.y = 672.f;
		mRecCropEntityTexture.width = 32.f;
		mRecCropEntityTexture.height = 32.f;
		mCollisionType = ECollisionType::BLOCKING;
	}
};

