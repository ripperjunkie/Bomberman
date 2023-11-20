#include "Brick.h"
#include "Explosion.h"

void Brick::OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor)
{
	Actor::OnCollisionBeginOverlap(otherActor);

	if (std::dynamic_pointer_cast<Explosion>(otherActor))
	{
		SetActive(false);
	}
}
