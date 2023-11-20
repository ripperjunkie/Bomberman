#pragma once

class IDamageInterface
{
public:
	virtual void OnTakenDamage(class Actor* damageCauser, int damageAmount);

};