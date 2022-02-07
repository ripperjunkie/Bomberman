#include "Player.h"


void Player::CollisionOverlap(Entity& overlapped_actor_)
{
	printf("\ncoordinate of overlapped actor: %d\n ", overlapped_actor_.GetCoordinates().x);
	overlapped_actor_.Destroy();
}
