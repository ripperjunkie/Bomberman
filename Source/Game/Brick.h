#pragma once

#include "Engine/GameFramework/Actor.h"
#include "DamageInterface.h"

class Brick : public Actor, public IDamageInterface
{
public:
	Brick();
	virtual void OnTakenDamage(class Actor* damageCauser, int damageAmount) override;

};

