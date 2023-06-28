#pragma once

#include "Engine/GameFramework/Actor.h"

class Brick : public Actor
{
public:
	Brick() : Actor()
	{
		mEntityTexture = LoadTexture("resources/133670.png");
		mEntityTexture.width = 512.f;
		mEntityTexture.height = 832.f;
		mRecCropEntityTexture.x = 192.f;
		mRecCropEntityTexture.y = 672.f;
		mRecCropEntityTexture.width = 32.f;
		mRecCropEntityTexture.height = 32.f;
		mCollisionType = ECollisionType::BLOCKING;
	}
	virtual void OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor) override;
};

