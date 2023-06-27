#pragma once

#include "Engine/GameFramework/Actor.h"

enum class EBlockType : uint8_t
{
    DESTRUCTIBLE,
    NON_DESTRUCTIBLE
};


class Environment : public Actor
{
public:
	Environment() : Actor()
	{
		entity_texture = LoadTexture("resources/133670.png");
		entity_texture.width = 512.f;
		entity_texture.height = 832.f;
		rec_crop_entity_texture.x = 160.f;
		rec_crop_entity_texture.y = 672.f;
		rec_crop_entity_texture.width = 32.f;
		rec_crop_entity_texture.height = 32.f;
		collision_type = ECollisionType::BLOCKING;
	}
    virtual void OnCollisionBeginOverlap(Actor& overlapped_actor_) override;
	std::shared_ptr<class Grid> tileMap = nullptr;

protected:

};

