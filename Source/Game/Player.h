#pragma once

#include "Engine/GameFramework/Actor.h"



class Bomb;
class HealthComponent;


class Player : public Actor
{
public:
    Player();


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

