#include "Entity.h"
#include <iostream>
#include <cmath>
#include "raymath.h"


#define PRINT(x) std::cout << "\n";  printf(x) ; std::cout << "\n";

Entity::Entity(TileMap& tile_map_, ECollisionType collision_type_, EObjectMovType object_mov_type_, bool bShow_collision_, Texture2D shared_sprite_sheet_)
{
	speed = 30;
	bActive = true;
	row = 1;
	column = 1; 
	tile_map = &tile_map_;
	collision_type = collision_type_;
	object_mov_type = object_mov_type_;
	bShow_collision = bShow_collision_;
	shared_sprite_sheet = shared_sprite_sheet_;

	if (tile_map)
	{
		entity_collision.width = (float)tile_map->size;
		entity_collision.height = (float)tile_map->size;			
	}

	entity_collision.x = 0.f;
	entity_collision.y = 0.f;
	color = GREEN;
	lerp_speed = 4.f;
}

Entity::~Entity()
{
	//printf("\n I'm going to space!\n");
}

//This is turning into our tick/update methods
void Entity::Update()
{
	if (!bActive) return;
	if (bShow_collision)
	{
		DrawRectangleLinesEx(entity_collision, 1.f, color);
	}

	Vector2 text_pos;
	text_pos.x = entity_collision.x;
	text_pos.y = entity_collision.y;
	DrawTextureRec(entity_texture, rec_crop_entity_texture, text_pos, WHITE);
	UpdateAnimation();
}

void Entity::Destroy()
{
	bActive = false;
}

void Entity::UpdateAnimation()
{
	if (animations.size() == 0)
		return;

	const AnimationData current_anim = animations[current_animation];

	frame_counter++;
	if (frame_counter >= (60/frame_speed))
	{
		frame_counter = 0;
		current_frame++;
		if (current_frame > current_anim.rec_crop_location.size() - 1)
			current_frame = 0;

	//	printf("\current_frame %d\n", current_frame);

		rec_crop_entity_texture.x = current_anim.rec_crop_location[current_frame].x;
		rec_crop_entity_texture.y = current_anim.rec_crop_location[current_frame].y;
	}

}

void Entity::OnCollisionOverlap(Entity& overlapped_actor_)
{
	printf("\n Overlapped\n");
}

TileMapCoordinates Entity::GetCoordinates()
{
	return TileMapCoordinates(column, row);
}

void Entity::SetLocation(int row_, int column_)
{
	if (!tile_map)
	{
		//printf("\nInvalid Tile map\n");
		return;
	}

	//Do a collision check if there some entity there
	//for (auto& entity : tile_map->entities)
	//{
	//	if (entity.get().bActive)
	//	{
	//		if (&entity.get() != this && row_ == entity.get().row && column_ == entity.get().column && entity.get().collision_type == ECollisionType::BLOCKING)
	//		{
	//			//	printf("cant move");
	//			return;
	//		}
	//		if (&entity.get() != this && row_ == entity.get().row && column_ == entity.get().column && entity.get().collision_type == ECollisionType::OVERLAP)
	//		{
	//			CollisionOverlap(entity);
	//			break;
	//		}
	//	}

	////}
	column = column_;
	row = row_;
	
	entity_collision.x = tile_map->tiles[column].x;
	entity_collision.y = tile_map->tiles[(tile_map->amount_x * row) + column].y;
}

void Entity::SetLocation(int tile_number_)
{
	entity_collision.x = tile_map->tiles[tile_number_].x;
	entity_collision.y = tile_map->tiles[tile_number_].y;
}


//This is how the object is moving
void Entity::AddMovement(int x, int y)
{
	if (!tile_map)
		return;

	if (IsColliding(x, y))
		return;

	//Here is where the real movement happens
	entity_collision.x = std::lerp(entity_collision.x, entity_collision.x + x, GetFrameTime() * lerp_speed);
	entity_collision.y = std::lerp(entity_collision.y, entity_collision.y + y, GetFrameTime() * lerp_speed);
}

void Entity::AddMovement(Vector2 dir, float axis)
{
	if (IsColliding(dir.x * axis * speed, dir.y * axis * speed))
		return;

	if (axis == 0.f)
		return;

	entity_collision.x = std::lerp(entity_collision.x, entity_collision.x + dir.x * axis * speed, GetFrameTime() * lerp_speed);
	entity_collision.y = std::lerp(entity_collision.y, entity_collision.y + dir.y * axis * speed, GetFrameTime() * lerp_speed);
}


void Entity::MoveOutOfCollision(int x, int y)
{
	//Add world movement with lerp
	const float lerp_speed = 4.f;

	//Here is where the real movement happens
	entity_collision.x = std::lerp(entity_collision.x, entity_collision.x + x, GetFrameTime() * lerp_speed);
	entity_collision.y = std::lerp(entity_collision.y, entity_collision.y + y, GetFrameTime() * lerp_speed);
}

void Entity::SetShowCollision(bool ShowCollision)
{
	bShow_collision = ShowCollision;
}

bool Entity::IsColliding(int x, int y)
{
	//Add world movement with lerp
	const float lerp_time = 4.f;

	//Here is where we check with a fake rectangle to see if it will overlap
	Rectangle rect = entity_collision;
	rect.width = entity_collision.width;
	rect.height = entity_collision.height;

	rect.x = std::lerp(rect.x, entity_collision.x + x, GetFrameTime() * lerp_time);
	rect.y = std::lerp(rect.y, entity_collision.y + y, GetFrameTime() * lerp_time);

	if (collision_type != ECollisionType::IGNORE)
	{
		for (size_t i = 0; i < tile_map->entities.size(); i++)
		{
			if (&tile_map->entities[i].get() != this && tile_map->entities[i].get().collision_type != ECollisionType::IGNORE
				&& CheckCollisionRecs(rect, tile_map->entities[i].get().entity_collision))
			{
				auto entity = &tile_map->entities[i].get();
				if (entity)
				{
					if (entity->collision_type == ECollisionType::BLOCKING)
					{
						return true;
					}
					if (entity->collision_type == ECollisionType::OVERLAP)
					{
						OnCollisionOverlap(*entity);
						return false;
					}
				}
			}
		}
	}
	return false;

}