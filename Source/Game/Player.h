#pragma once

#include "Engine/GameFramework/Actor.h"



class Bomb;
class HealthComponent;


class Player : public Actor
{
public:
	Player() : Actor()
	{
		//Here we insert inside the animations array each sprite we want it to be cycling
		idle.push_back(RecCropLocation(0, 32));

		
		walk_horizontal.push_back(RecCropLocation(30, 130));
		walk_horizontal.push_back(RecCropLocation(63, 130));
		walk_horizontal.push_back(RecCropLocation(96, 130));
		walk_horizontal.push_back(RecCropLocation(127, 130));

		walk_up.push_back(RecCropLocation(0, 65));
		walk_up.push_back(RecCropLocation(32, 65));
		walk_up.push_back(RecCropLocation(64, 65));
		walk_up.push_back(RecCropLocation(96, 65));
		walk_up.push_back(RecCropLocation(130, 65));

		walk_down.push_back(RecCropLocation(34, 32));
		walk_down.push_back(RecCropLocation(64, 32));
		walk_down.push_back(RecCropLocation(97, 32));
		walk_down.push_back(RecCropLocation(129, 32));

		CropSprite(idle[0].x, idle[0].y);

		//Load animations
		mAnimations.push_back(AnimationData(idle));
		mAnimations.push_back(AnimationData(walk_horizontal));
		mAnimations.push_back(AnimationData(walk_up));
		mAnimations.push_back(AnimationData(walk_down));

		bCanPlaceBomb = true;
		bStartTimer = false;
		timer = 4.f; //cooldown of player to place bombs
		initialTimer = timer;
		mSpeed = 25.f;
		mName = "Player";
	}

	~Player();

    virtual void Start() override;
    virtual void Update() override;
    void Input();
    void InputMovement();
    void InputSpawnBomb();
    
    
    //to control animations switching
    std::vector<RecCropLocation> idle;
    std::vector<RecCropLocation> walk_horizontal;
    std::vector<RecCropLocation> walk_up;
    std::vector<RecCropLocation> walk_down;

    float input_up;
    float input_right;
    std::shared_ptr<Bomb> bomb;

	// Getters 
	std::shared_ptr<HealthComponent> GetHealthComp() const
	{
		return healthComp;
	}
protected:

	virtual void OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor) override;
    virtual void OnCollisionEndOverlap(Actor& otherActor) override;
    bool bCanPlaceBomb;
	void OnDie();

	// components
	std::shared_ptr<HealthComponent> healthComp; 

private:
	float timer;
	float initialTimer; //using to reset timer back to default value
	bool bStartTimer;
};

