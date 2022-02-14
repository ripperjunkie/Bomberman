#include "Entity.h"
#include <iostream>
#include <cmath>

#define PRINT(x) std::cout << "\n";  printf(x) ; std::cout << "\n";

Entity::Entity(TileMap& tile_map_, ECollisionType collision_type_, bool bShow_collision_, Texture2D shared_sprite_sheet_)
{
	bActive = true;
	row = 1;
	column = 1; 
	tile_map = &tile_map_;
	collision_type = collision_type_;
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
}

Entity::~Entity()
{
	//printf("\n I'm going to space!\n");
}

//This is turning into our tick or update methods
void Entity::Update()
{
	if (!bActive) return;
	if(bShow_collision)
		DrawRectangleLinesEx(entity_collision, 2.f, color);

	Vector2 text_pos;
	text_pos.x = entity_collision.x + 3.f;
	text_pos.y = entity_collision.y + 3.f;
	DrawTextureRec(entity_texture, rec_crop_entity_texture, text_pos, WHITE);
	UpdateAnimation();


	//Do a collision check if there some entity there
	for (auto& entity : tile_map->entities)
	{
		if (entity.get().bActive)
		{
			if (&entity.get() != this && !CheckCollisionRecs(entity_collision, entity.get().entity_collision) && entity.get().collision_type == ECollisionType::BLOCKING)
			{
				previous_position.x = entity_collision.x;
				previous_position.y = entity_collision.y;

			}
			else if(&entity.get() != this && CheckCollisionRecs(entity_collision, entity.get().entity_collision) && entity.get().collision_type == ECollisionType::BLOCKING)
			{
				MoveOutOfCollision();
			}
	
		}

	}



	printf("\nprevious_x : %f, previous_y: %f\n", previous_position.x, previous_position.y);
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
	//printf("\nframecounter %d\n", frame_counter);
	if (frame_counter >= (60/frame_speed))
	{
		frame_counter = 0;
		current_frame++;
		if (current_frame > current_anim.animation_length)
			current_frame = 0;

		//Note for me: Put a starter offset
		rec_crop_entity_texture.x += current_anim.animation_length;
	}
	if (rec_crop_entity_texture.x >= current_anim.animation_final_pos_x)
	{
		rec_crop_entity_texture.x = current_anim.animation_start_pos_x;
	}
	if (rec_crop_entity_texture.x == 0)
	{
		rec_crop_entity_texture.x = current_anim.animation_start_pos_x;
	}
	rec_crop_entity_texture.y = current_anim.animation_start_pos_y;


}


void Entity::CollisionOverlap(Entity& overlapped_actor_)
{
	//printf("\n Overlapped\n");
}


TileMapCoordinates Entity::GetCoordinates()
{
	return TileMapCoordinates(column, row);
}

void Entity::SetLocation(int row_, int column_)
{
	if (!tile_map)
	{
		printf("\nInvalid Tile map\n");
		return;
	}

	//Do a collision check if there some entity there
	for (auto& entity : tile_map->entities)
	{
		if (entity.get().bActive)
		{
			if (&entity.get() != this && row_ == entity.get().row && column_ == entity.get().column && entity.get().collision_type == ECollisionType::BLOCKING)
			{
				//	printf("cant move");
				return;
			}
			if (&entity.get() != this && row_ == entity.get().row && column_ == entity.get().column && entity.get().collision_type == ECollisionType::OVERLAP)
			{
				CollisionOverlap(entity);
				break;
			}
		}

	}
	column = column_;
	row = row_;

	
	entity_collision.x = tile_map->tiles[column].x;
	entity_collision.y = tile_map->tiles[(tile_map->amount_x * row) + column].y;
	

}


void Entity::AddMovement(int x, int y)
{
	//Add world movement with lerp
	const float lerp_time = 4.f;



	//Do a collision check if there some entity there
	for (auto& entity : tile_map->entities)
	{
		if (entity.get().bActive)
		{
			if (&entity.get() != this && CheckCollisionRecs(entity_collision, entity.get().entity_collision) && entity.get().collision_type == ECollisionType::BLOCKING)
			{
				printf("cant move");
				MoveOutOfCollision();
				return;
			}
			if (&entity.get() != this && CheckCollisionRecs(entity_collision, entity.get().entity_collision) && entity.get().collision_type == ECollisionType::OVERLAP)
			{
				CollisionOverlap(entity);
				break;
			}
		}

	}
	
	entity_collision.x = std::lerp(entity_collision.x, entity_collision.x + x, GetFrameTime() * lerp_time);
	entity_collision.y = std::lerp(entity_collision.y, entity_collision.y + y, GetFrameTime() * lerp_time);
}

void Entity::MoveOutOfCollision()
{
	entity_collision.x = previous_position.x;
	entity_collision.y = previous_position.y;

}
