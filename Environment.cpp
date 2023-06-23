#include "Environment.h"
#include "Explosion.h"

void Environment::OnCollisionBeginOverlap(Entity& overlapped_actor_)
{
	if (Explosion* explosion = dynamic_cast<Explosion*>(&overlapped_actor_))
	{
		SetActive(false);
	}
}