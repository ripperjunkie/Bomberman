#pragma once

#include <functional>


using HealthChangeFunction = std::function<void()>;

class HealthComponent
{
public:
	HealthComponent(unsigned int MaxLife);

	void TakeDamage(unsigned int _value);
	void Heal(unsigned int _value);

	
	// on die function callback
	HealthChangeFunction OnDie;
	void SetHealthChangeCallback(HealthChangeFunction OnDie)
	{
		this->OnDie = OnDie;
	}


	int GetCurrentHP() const
	{
		return mCurrentHP;
	}

private:
	int mMaxHP;
	int mCurrentHP;
};

