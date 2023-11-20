#pragma once

#include "Engine/GameFramework/Actor.h"
#include "DamageInterface.h"

class HealthComponent;
class Bomb;

class Enemy : public Actor, public IDamageInterface
{
public:
	Enemy();
    std::vector<RecCropLocation> idle;

	virtual void Start() override;
protected:

    virtual void OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor) override;
	void OnDie();
	virtual void Update() override;
	virtual void OnTakenDamage(class Actor* damageCauser, int damageAmount) override;


	std::shared_ptr<Bomb> bomb;
	bool bCanPlaceBomb;


	// components
	std::shared_ptr<HealthComponent> healthComp;

	bool bStartTimer;
	float timer;
	float initialTimer; //using to reset timer back to default value
};

