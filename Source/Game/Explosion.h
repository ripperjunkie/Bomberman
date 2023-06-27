#pragma once

#include "Engine/GameFramework/Actor.h"

class Explosion : public Actor
{
public:
	Explosion() : Actor()
	{
		CropSprite(224.f, 704.f);

		name = "explosion";

	}

	virtual void Start() override;
	virtual void Update() override;
	virtual void Destroy() override;

	float timer;
	bool bStartTimer;
	std::shared_ptr<class Grid> tileMap = nullptr;
};

