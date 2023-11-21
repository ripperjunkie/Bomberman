#include "Actor.h"
#include "Engine/Managers/ActorManager.h"
#include "Engine/Managers/TextureManager.h"
#include "Game/GameUtils.h"
#include <future>

#define PRINT(x) std::cout << "\n";  printf(x) ; std::cout << "\n";



Actor::Actor()
{
	mSpeed = 20;
	bActive = true;
	bShowCollision = false;
	mCollider.x = 0.f;
	mCollider.y = 0.f;
	mColor = GREEN;
	mLerpSpeed = 4.f;
	mFrameCounter = 0;
	mCurrentAnimation = 0;
	mCurrentFrame = 0;
	mObjectMovementType = EObjectMovType::STATIC;
	mCollisionType = ECollisionType::BLOCKING;

	mEntityTexture = TextureManager::GetInstance()->GetTexture();	
	//mEntityTexture = LoadTexture("resources/133670.png"); // old slow way
	mEntityTexture.width = 512;
	mEntityTexture.height = 832;

	mCollider.width = TILE_SIZE;
	mCollider.height = TILE_SIZE;
}



void Actor::Start()
{

}
Actor::~Actor()
{
	//printf("\n I'm going to space!\n");
}

//This is turning into our tick/update methods
void Actor::Update()
{
	if (!bActive) return;


	if (bShowCollision)
	{
		DrawRectangleLinesEx(mCollider, 1.f, mColor);
	}


	Vector2 text_pos;
	text_pos.x = mCollider.x;
	text_pos.y = mCollider.y;
	DrawTextureRec(mEntityTexture, mRecCropEntityTexture, text_pos, WHITE);

	UpdateAnimation();

	if (mCollisionType != ECollisionType::IGNORE)
	{
		CheckOverlapCollision();
		CheckEndOverlap();
	}

}

void Actor::Destroy()
{
	bActive = false;
}

void Actor::UpdateAnimation()
{
	if (mAnimations.size() == 0)
		return;

	const AnimationData current_anim = mAnimations[mCurrentAnimation];

	mFrameCounter++;
	if (mFrameCounter >= (GetFPS() / mAnimationSpeed))
	if (mFrameCounter >= (GetFPS() / mAnimationSpeed))
	{
		mFrameCounter = 0;
		mCurrentFrame++;

		// reset anim
		if (mCurrentFrame > current_anim.rec_crop_location.size() - 1)
		{
			mCurrentFrame = 0;
		}

		mRecCropEntityTexture.x = current_anim.rec_crop_location[mCurrentFrame].x;
		mRecCropEntityTexture.y = current_anim.rec_crop_location[mCurrentFrame].y;
	}

}

void Actor::OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor)
{
	//if (otherActor)
		//printf("\n Collision begin overlap from: %s, to: %s\n", this->mName.c_str(), otherActor->mName.c_str());
}

void Actor::OnCollisionEndOverlap(Actor& otherActor)
{
	//printf("\n Collision end overlap from: %s, to: %s\n", this->mName.c_str(), otherActor.mName.c_str());
}


void Actor::OnCollisionBlock(Actor& otherActor)
{
	//printf("\n OnCollisionBlock, entity: %s\n", other_actor.name.c_str());
}

void Actor::CropSprite(float x, float y, float width, float height)
{
	mRecCropEntityTexture.x = x;
	mRecCropEntityTexture.y = y;
	mRecCropEntityTexture.width = width;
	mRecCropEntityTexture.height = height;
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
	mCollider.x = std::lerp(mCollider.x, mCollider.x + x, GetFrameTime() * mLerpSpeed);
	mCollider.y = std::lerp(mCollider.y, mCollider.y + y, GetFrameTime() * mLerpSpeed);
}

void Actor::AddMovement(Vector2 dir, float axis)
{
	if (IsColliding(dir.x * axis * mSpeed, dir.y * axis * mSpeed))
		return;

	if (axis == 0.f)
		return;

	//Here is where the real movement happens, also we are lerping it to smooth the movement
	mCollider.x = std::lerp(mCollider.x, mCollider.x + dir.x * axis * mSpeed, GetFrameTime() * mLerpSpeed);
	mCollider.y = std::lerp(mCollider.y, mCollider.y + dir.y * axis * mSpeed, GetFrameTime() * mLerpSpeed);

	//collider.x += dir.x * axis * speed * GetFrameTime();
	//collider.y += dir.y * axis * speed * GetFrameTime();
}


void Actor::MoveOutOfCollision(int x, int y)
{
	//Add world movement with lerp
	const float mLerpSpeed = 4.f;

	//Here is where the real movement happens
	mCollider.x = std::lerp(mCollider.x, mCollider.x + x, GetFrameTime() * mLerpSpeed);
	mCollider.y = std::lerp(mCollider.y, mCollider.y + y, GetFrameTime() * mLerpSpeed);

	//printf("name %s trying to move out of collision", name.c_str());
}


//Check blocking collision between entities
bool Actor::IsColliding(int x, int y)
{
	//Add world movement with lerp
	const float lerp_time = 4.f;

	//Here is where we check with a rectangle to see if it will overlap
	Rectangle rect = mCollider;
	rect.width = mCollider.width;
	rect.height = mCollider.height;

	rect.x = std::lerp(rect.x, mCollider.x + x, GetFrameTime() * lerp_time);
	rect.y = std::lerp(rect.y, mCollider.y + y, GetFrameTime() * lerp_time);

	if (mCollisionType == ECollisionType::IGNORE)
		return false;


	for (const std::shared_ptr<Actor>& actor : ACTOR_MANAGER->GetInstance()->GetActors())
	{
		if (actor.get() != this && actor->mCollisionType != ECollisionType::IGNORE
			&& CheckCollisionRecs(rect, actor->mCollider))
		{
			auto entity = actor;
			if (entity)
			{
				if (entity->mCollisionType == ECollisionType::BLOCKING && entity->bActive)
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
	//Iterate through all entities
	for (auto& pair : overlapped_entities)
	{

		if (!CheckCollisionRecs(mCollider, pair.first->mCollider))
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
	if (mCollisionType == ECollisionType::IGNORE)
	{
		return;
	}

	//Iterate through all entities
	for (auto& pair : overlapped_entities)
	{
		if (CheckCollisionRecs(mCollider, pair.first->mCollider))
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