#pragma once

#include "Engine/Public/EngineUtils.h"
#include "Engine/Public/Utils.h"



class Actor : public std::enable_shared_from_this<Actor>
{
	friend class ActorManager;
public:

	bool GetActiveState() const
	{
		return bActive;
	}


	Vector2 GetLocation() const
	{
		return Vector2{ collider.x, collider.y };
	}
	void SetLocation(float x, float y);
	void AddMovement(int x, int y);
	void AddMovement(Vector2 dir, float axis);



	void SetActive(bool ActiveState)
	{
		bActive = ActiveState;
	}

	virtual void Start();
	virtual void Update();
	virtual void Destroy();
	int row;
	int column;

	void UpdateAnimation();

	//movement
	float speed;
	std::string name;

	//Collision related
	void SetShowCollision(bool ShowCollision);
	bool IsColliding(int x, int y);
	void CheckOverlapCollision();
	void CheckEndOverlap();
	void MoveOutOfCollision(int x, int y);


	Rectangle collider; //this is not the best name
	EObjectMovType object_mov_type;
	ECollisionType collision_type;
	Vector2 direction_movement; //direction that this object is moving to
	float acceleration = 1.f;
	float lerp_speed;



	Texture2D entity_texture;
	Texture2D sprite_sheet;

	bool bHasOverlapped;

	float timer;
	float initialTimer; //using to reset timer back to default value
	bool bStartTimer;

	std::unordered_map<std::shared_ptr<Actor>, bool> overlapped_entities;
	Actor();
	~Actor();
protected:
	/* Both the constructor and destructor are on protected to prevent other classes
	from creating the class other than our ActorManager class*/

	Color color;
	
	//Texture related stuff
	Rectangle rec_crop_entity_texture;

	//Animation related
	int current_frame;
	int frame_counter;
	float animation_speed = 5.f;
	std::vector<AnimationData> animations;
	int current_animation = 0;

	int GetTileNumber(int row_, int column_);
	virtual void OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor);
	virtual void OnCollisionEndOverlap(Actor& other_actor);
	virtual void OnCollisionBlock(Actor& other_actor);

	bool bShow_collision;
	bool bActive;
	
	//We do some setting to crop the sprite location we want this entity to have
	void CropSprite(float x, float y, float width = 32.f, float height = 32.f);
};

