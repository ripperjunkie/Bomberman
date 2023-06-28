#pragma once

#include "Engine/GameFramework/Actor.h"

class Brick : public Actor
{
public:
	Brick() : Actor()
	{
		entity_texture = LoadTexture("resources/133670.png");
		entity_texture.width = 512.f;
		entity_texture.height = 832.f;
		rec_crop_entity_texture.x = 192.f;
		rec_crop_entity_texture.y = 672.f;
		rec_crop_entity_texture.width = 32.f;
		rec_crop_entity_texture.height = 32.f;
		collision_type = ECollisionType::BLOCKING;
	}
	virtual void OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor) override;
};

