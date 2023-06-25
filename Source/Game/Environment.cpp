#include "Environment.h"
#include "Explosion.h"

void Environment::OnCollisionBeginOverlap(Actor& overlapped_actor_)
{
	Actor::OnCollisionBeginOverlap(overlapped_actor_);

	if (Explosion* explosion = dynamic_cast<Explosion*>(&overlapped_actor_))
	{
		this->SetActive(false);
	}
}