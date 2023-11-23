#include "Brick.h"
#include "Explosion.h"


Brick::Brick() : Actor()
{
	mEntityTexture.width = 512.f;
	mEntityTexture.height = 832.f;
	mRecCropEntityTexture.x = 192.f;
	mRecCropEntityTexture.y = 672.f;
	mRecCropEntityTexture.width = 32.f;
	mRecCropEntityTexture.height = 32.f;
	mCollisionType = ECollisionType::BLOCKING;
}

void Brick::OnTakenDamage(Actor* damageCauser, int damageAmount)
{
	SetActive(false);
}
