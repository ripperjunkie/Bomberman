#pragma once

#include "Engine/GameFramework/Actor.h"

class HealthComponent;
class Bomb;

class Enemy : public Actor
{
public:
	Enemy();
    std::vector<RecCropLocation> idle;

	virtual void Start() override;
protected:

    virtual void OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor) override;
	void OnDie();
	void InputMovement();
	void InputSpawnBomb();
	virtual void Update() override;

	float input_up;
	float input_right;
	std::shared_ptr<Bomb> bomb;
	bool bCanPlaceBomb;


	// components
	std::shared_ptr<HealthComponent> healthComp;

	bool bStartTimer;
	float timer;
	float initialTimer; //using to reset timer back to default value
};

