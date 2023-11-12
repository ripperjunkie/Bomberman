#pragma once

#include "Engine/Public/EngineUtils.h"
#include "Engine/Public/Utils.h"




class Actor : public std::enable_shared_from_this<Actor>
{
	friend class ActorManager;
public:

	virtual void Start();
	virtual void Update();
	virtual void Destroy();


	bool GetActiveState() const
	{
		return bActive;
	}

	Vector2 GetLocation() const
	{
		return Vector2{ mCollider.x, mCollider.y };
	}


	virtual void SetActive(bool ActiveState)
	{
		bActive = ActiveState;
	}

	void SetShowCollision(bool ShowCollision)
	{
		bShowCollision = ShowCollision;
	}

	void SetLocation(float x, float y)
	{
		mCollider.x = x;
		mCollider.y = y;
	}


	void AddMovement(int x, int y);
	void AddMovement(Vector2 dir, float axis);
	
	void UpdateAnimation();


	// overlap collision related
	std::unordered_map<std::shared_ptr<Actor>, bool> overlapped_entities;


	Texture2D mEntityTexture;
	std::string mTexturePath = "resources/133670.png";

protected:
	/* Both the constructor and destructor are on protected to prevent other classes
	from creating the class other than our ActorManager class*/
	Actor();
	~Actor();

protected:


	Texture2D mSpriteSheet;


	/* Collider "component" */
	Rectangle mCollider;
	
	//Texture related stuff
	Rectangle mRecCropEntityTexture;

	//Animation related
	unsigned int mCurrentFrame;
	unsigned int mFrameCounter;
	float mAnimationSpeed = 5.f;
	std::vector<AnimationData> mAnimations;
	int mCurrentAnimation = 0;

	virtual void OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor);
	virtual void OnCollisionEndOverlap(Actor& otherActor);
	virtual void OnCollisionBlock(Actor& otherActor);

	bool bShowCollision;
	bool bActive;
	
	//We do some setting to crop the sprite location we want this entity to have
	void CropSprite(float x, float y, float width = 32.f, float height = 32.f);

	//movement
	float mSpeed;
	float mAcceleration = 1.f;
	float mLerpSpeed;



	EObjectMovType mObjectMovementType;
	ECollisionType mCollisionType;

	Color mColor;
	std::string mName;



private:
	//Collision related
	bool IsColliding(int x, int y);
	void CheckOverlapCollision();
	void CheckEndOverlap();
	void MoveOutOfCollision(int x, int y);
};

