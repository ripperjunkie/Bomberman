#pragma once

#include "Engine/Public/EngineUtils.h"
#include "Engine/Public/Utils.h"



class Actor
{
public:
	Actor();
	~Actor();

	bool GetActiveState() const
	{
		return bActive;
	}
	TileMapCoordinates GetCoordinates();


	void SetLocation(int row_, int column_);
	void SetLocation(int tile_number_);
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


	//Vector2 movement;
	Rectangle collider; //this is not the best name
	EObjectMovType object_mov_type;
	ECollisionType collision_type;
	Vector2 direction_movement; //direction that this object is moving to
	float acceleration = 1.f;
	float lerp_speed;


	void MoveOutOfCollision(int x, int y);

	Texture2D entity_texture;
	Texture2D shared_sprite_sheet;

	bool bHasOverlapped;

	float timer;
	float initialTimer; //using to reset timer back to default value
	bool bStartTimer;

	std::unordered_map<Actor*, bool> overlapped_entities;
protected:

	Color color;
	
	//Texture related stuff
	Rectangle rec_crop_entity_texture;

	//Animation related
	int current_frame;
	int frame_counter;
	float frame_speed = 5.f;
	std::vector<AnimationData> animations;
	int current_animation;

	int GetTileNumber(int row_, int column_);
	virtual void OnCollisionBeginOverlap(Actor& other_actor);
	virtual void OnCollisionEndOverlap(Actor& other_actor);
	virtual void OnCollisionBlock(Actor& other_actor);

	bool bShow_collision;
	bool bActive;
	
	//We do some setting to crop the sprite location we want this entity to have
	void CropSprite(float x, float y, float width = 32.f, float height = 32.f);
};

