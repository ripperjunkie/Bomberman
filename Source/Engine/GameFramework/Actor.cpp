#include "Actor.h"
#include "Engine/Managers/ActorManager.h"
#include "Game/GameUtils.h"

#define PRINT(x) std::cout << "\n";  printf(x) ; std::cout << "\n";

Actor::Actor()
{
	speed = 20;
	bActive = true;
	row = 1;
	column = 1;
	bHasOverlapped = false;
	collider.x = 0.f;
	collider.y = 0.f;
	color = GREEN;
	lerp_speed = 4.f;
	frame_counter = 0;

	// deprecated (load textures in another thread)
	entity_texture = LoadTexture("resources/133670.png");
	entity_texture.width = 512;
	entity_texture.height = 832;

	collider.width = TILE_SIZE;
	collider.height = TILE_SIZE;
}

Actor::~Actor()
{
	//printf("\n I'm going to space!\n");
}

void Actor::Start()
{
}


//This is turning into our tick/update methods
void Actor::Update()
{
	if (!bActive) return;


	if (bShow_collision)
	{
		DrawRectangleLinesEx(collider, 1.f, color);
	}


	Vector2 text_pos;
	text_pos.x = collider.x;
	text_pos.y = collider.y;
	DrawTextureRec(entity_texture, rec_crop_entity_texture, text_pos, WHITE);

	UpdateAnimation();
	CheckOverlapCollision();
	CheckEndOverlap();
}

void Actor::Destroy()
{
	bActive = false;
}

void Actor::UpdateAnimation()
{
	if (animations.size() == 0)
		return;

	const AnimationData current_anim = animations[current_animation];

	frame_counter++;
	if (frame_counter >= (GetFPS() / animation_speed))
	{
		frame_counter = 0;
		current_frame++;

		// reset anim
		if (current_frame > current_anim.rec_crop_location.size() - 1)
		{
			current_frame = 0;
		}

		rec_crop_entity_texture.x = current_anim.rec_crop_location[current_frame].x;
		rec_crop_entity_texture.y = current_anim.rec_crop_location[current_frame].y;
	}

}

int Actor::GetTileNumber(int row_, int column_)
{
	//if (level)
	//{
	//	return row_ + level->amount_x + column;
	//}
	return 0;
}

void Actor::OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor)
{
	if (otherActor)
		printf("\n Collision begin overlap from: %s, to: %s\n", this->name.c_str(), otherActor->name.c_str());
}

void Actor::OnCollisionEndOverlap(Actor& other_actor)
{
	printf("\n Collision end overlap from: %s, to: %s\n", this->name.c_str(), other_actor.name.c_str());
}


void Actor::OnCollisionBlock(Actor& other_actor)
{
	//printf("\n OnCollisionBlock, entity: %s\n", other_actor.name.c_str());
}

void Actor::CropSprite(float x, float y, float width, float height)
{
	rec_crop_entity_texture.x = x;
	rec_crop_entity_texture.y = y;
	rec_crop_entity_texture.width = width;
	rec_crop_entity_texture.height = height;
}



void Actor::SetLocation(float x, float y)
{
	collider.x = x;
	collider.y = y;
}

//This is how the object is moving
void Actor::AddMovement(int x, int y)
{
	//if (!level)
	//	return;

	if (IsColliding(x, y))
	{
		return;
	}

	//Here is where the real movement happens, also we are lerping it to smooth the movement
	collider.x = std::lerp(collider.x, collider.x + x, GetFrameTime() * lerp_speed);
	collider.y = std::lerp(collider.y, collider.y + y, GetFrameTime() * lerp_speed);
}

void Actor::AddMovement(Vector2 dir, float axis)
{
	if (IsColliding(dir.x * axis * speed, dir.y * axis * speed))
		return;

	if (axis == 0.f)
		return;

	//Here is where the real movement happens, also we are lerping it to smooth the movement
	collider.x = std::lerp(collider.x, collider.x + dir.x * axis * speed, GetFrameTime() * lerp_speed);
	collider.y = std::lerp(collider.y, collider.y + dir.y * axis * speed, GetFrameTime() * lerp_speed);

	//collider.x += dir.x * axis * speed * GetFrameTime();
	//collider.y += dir.y * axis * speed * GetFrameTime();
}


void Actor::MoveOutOfCollision(int x, int y)
{
	//Add world movement with lerp
	const float lerp_speed = 4.f;

	//Here is where the real movement happens
	collider.x = std::lerp(collider.x, collider.x + x, GetFrameTime() * lerp_speed);
	collider.y = std::lerp(collider.y, collider.y + y, GetFrameTime() * lerp_speed);

	//printf("name %s trying to move out of collision", name.c_str());
}

void Actor::SetShowCollision(bool ShowCollision)
{
	bShow_collision = ShowCollision;
}

//Check blocking collision between entities
bool Actor::IsColliding(int x, int y)
{
	//Add world movement with lerp
	const float lerp_time = 4.f;

	//Here is where we check with a rectangle to see if it will overlap
	Rectangle rect = collider;
	rect.width = collider.width;
	rect.height = collider.height;

	rect.x = std::lerp(rect.x, collider.x + x, GetFrameTime() * lerp_time);
	rect.y = std::lerp(rect.y, collider.y + y, GetFrameTime() * lerp_time);

	if (collision_type == ECollisionType::IGNORE)
		return false;


	//OLD WAY
	//for (unsigned int i = 0; i < overlapped_entities.size(); i++)
	//{
	//	if (level->entities[i] != this && level->entities[i]->collision_type != ECollisionType::IGNORE
	//		&& CheckCollisionRecs(rect, level->entities[i]->collider))
	//	{
	//		auto entity = level->entities[i];
	//		if (entity)
	//		{
	//			if (entity->collision_type == ECollisionType::BLOCKING && entity->bActive)
	//			{
	//				OnCollisionBlock(*entity);
	//				return true;
	//			}
	//		}
	//	}
	//}

	for (const std::shared_ptr<Actor>& actor : ACTOR_MANAGER->GetInstance()->GetActors())
	{
		if (actor.get() != this && actor->collision_type != ECollisionType::IGNORE
			&& CheckCollisionRecs(rect, actor->collider))
		{
			auto entity = actor;
			if (entity)
			{
				if (entity->collision_type == ECollisionType::BLOCKING && entity->bActive)
				{
					OnCollisionBlock(*entity);
					return true;
				}
			}
		}
	}
	return false;

}

void Actor::CheckOverlapCollision()
{
	//Here is where we check with a rectangle to see if it's overlap
	if (collision_type == ECollisionType::IGNORE)
	{
		return;
	}

	//Iterate through all entities
	for (auto& pair : overlapped_entities)
	{

		if (!CheckCollisionRecs(collider, pair.first->collider))
			continue;

		//If this entity already overlapped with other entity, don't execute (skip this iteration and go to the next one)
		//We need to do this toggle method so that overlap gets fired only once per begin and end overlap events
		if (pair.second)
			continue;

		if (!pair.first->bActive)
			return;

		//Flag the entity we overlapped with as overlapped
		pair.second = true;
		//This will fire the begin overlap for this actor passing as parameter the actor we just overlapped
		OnCollisionBeginOverlap(pair.first);
		pair.first->OnCollisionBeginOverlap(shared_from_this()); //this is not the way to do it but it works for now
	}
}

void Actor::CheckEndOverlap()
{
	if (collision_type == ECollisionType::IGNORE)
	{
		return;
	}

	//Iterate through all entities
	for (auto& pair : overlapped_entities)
	{
		if (CheckCollisionRecs(collider, pair.first->collider))
			continue;

		//If this entity already overlapped with other entity, don't execute (skip this iteration and go to the next one)
		//We need to do this toggle method so that overlap gets fired only once per begin and end overlap events
		if (!pair.second)
			continue;

		//Flag the entity we overlapped with as overlapped
		pair.second = false;

		//This will fire the end overlap method for this actor passing as parameter the actor we just overlapped
		OnCollisionEndOverlap(*pair.first);
		pair.first->OnCollisionEndOverlap(*this); //this is not the way to do it
	}
}