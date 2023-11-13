#include "Enemy.h"

#include "Bomb.h"
#include "Explosion.h"
#include "HealthComponent.h"
#include "Engine/Managers/ActorManager.h"

Enemy::Enemy() : Actor()
{
	idle.push_back(RecCropLocation(0, 384));
	mAnimations.push_back(AnimationData(idle));
	CropSprite(idle[0].x, idle[0].y);
}

void Enemy::Start()
{
	Actor::Start();

	healthComp = std::make_shared<HealthComponent>(3);
	healthComp->SetHealthChangeCallback(std::bind(&Enemy::OnDie, this));

	// let's reserve the bomb to use later
	bomb = ACTOR_MANAGER->SpawnActor<Bomb>();
}

void Enemy::Update()
{
	Actor::Update();

	if (bStartTimer)
	{
		timer -= GetFrameTime();
		//printf("Timer: %f\n", timer);

		if (timer <= 0.f)
		{
			timer = initialTimer;
			bCanPlaceBomb = true;
		}
	}

	InputSpawnBomb();
	InputMovement();


	//Normalize input so character don't walk faster if moving diagonally
	Vector2 normalize_vector = Vector2Normalize(Vector2(input_right, input_up));
	AddMovement(Vector2(0, 1), normalize_vector.y); //vertical
	AddMovement(Vector2(1, 0), normalize_vector.x); //horizontal
}

void Enemy::OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor)
{
	Actor::OnCollisionBeginOverlap(otherActor);

	if (std::shared_ptr<Explosion> enemy = std::dynamic_pointer_cast<Explosion>(otherActor))
	{
		if (healthComp)
		{
			healthComp->TakeDamage(1);
		}
	}
}


void Enemy::OnDie()
{
	SetActive(false);
}

void Enemy::InputMovement()
{
	//current_animation = 0;
	float up_1 = 0.f;
	float up_2 = 0.f;
	float right_1 = 0.f;
	float right_2 = 0.f;

	if (IsKeyDown(KEY_D))
	{
		right_1 = 1.f;

	}

	if (IsKeyDown(KEY_A))
	{
		right_2 = -1.f;

	}

	if (IsKeyDown(KEY_W))
	{
		up_1 = -1.f;
	}

	if (IsKeyDown(KEY_S))
	{
		up_2 = 1.f;
	}

	input_up = up_1 + up_2;
	input_right = right_1 + right_2;
}

void Enemy::InputSpawnBomb()
{
	if (IsKeyPressed(KEY_C))
	{
		if (!bCanPlaceBomb)
			return;

		bStartTimer = true;

		/* for now we are literally spawning every time, no object pooling stuff yet
		 but it should be fine for now */

		if (!bomb)
			return;

		bomb->SetActive(true);
		overlapped_entities.emplace(bomb, false);
		bomb->SetShowCollision(true); //just for debug sake
		bomb->SetLocation(mCollider.x, mCollider.y);
		bCanPlaceBomb = false;
	}
}

