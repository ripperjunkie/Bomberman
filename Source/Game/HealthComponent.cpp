#include "HealthComponent.h"
#include "Engine/Public/Utils.h"

HealthComponent::HealthComponent(unsigned int MaxLife)
{
	mMaxHP = MaxLife;
	mCurrentHP = mMaxHP;
}

void HealthComponent::TakeDamage(unsigned int _value)
{
	mCurrentHP = (int)(Clamp(mCurrentHP - _value, 0, mMaxHP));


	if (mCurrentHP <= 0)
	{
		// check if it's valid (if it has been bound)
		if (OnDie)
		{
			OnDie(); // delegate call
		}
	}
}

void HealthComponent::Heal(unsigned int _value)
{
	mCurrentHP = (int)(Clamp(mCurrentHP + _value, 0, mMaxHP));
}
