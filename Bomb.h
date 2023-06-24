#pragma once

#include "Entity.h"

class Bomb : public Entity
{
public:
	Bomb(TileMap& tile_map_, ECollisionType collision_type_ = ECollisionType::OVERLAP, EObjectMovType object_mov_type = EObjectMovType::MOVABLE,
		bool bShow_collision_ = true, Texture2D shared_sprite_sheet_ = Texture2D()) :
		Entity(tile_map_, collision_type_, object_mov_type, bShow_collision_, shared_sprite_sheet_)
	{
		CropSprite(224.f, 704.f);
		name = "bomb";
		Start();
	}

	virtual void Start() override;
	virtual void Update() override;
	virtual void OnCollisionEndOverlap(Entity& other_actor) override;
	virtual void Destroy() override;


	void Explode();




	std::vector<std::reference_wrapper<class Explosion>> explosion;
	int explosionRange; // controls the range of this bomb when it explodes
}; 
