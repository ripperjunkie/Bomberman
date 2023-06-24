#include "Environment.h"
#include "Explosion.h"

void Environment::OnCollisionBeginOverlap(Entity& overlapped_actor_)
{
	Entity::OnCollisionBeginOverlap(overlapped_actor_);

	if (Explosion* explosion = dynamic_cast<Explosion*>(&overlapped_actor_))
	{
		this->SetActive(false);
	}
}