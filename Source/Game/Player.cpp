#include "Player.h"
#include "Bomb.h"
#include "Explosion.h"

#include "Engine/Managers/ActorManager.h"


Player::~Player()
{

}

void Player::Start()
{
	Actor::Start();
}

void Player::Update()
{
	Actor::Update();

	//Destroy after a certain time if timer is active
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

	Input();

	//Normalize input so character don't walk faster if two inputs are pressed at once
	Vector2 normalize_vector = Vector2Normalize(Vector2(input_right, input_up));
	AddMovement(Vector2(0, 1), normalize_vector.y); //vertical
	AddMovement(Vector2(1, 0), normalize_vector.x); //horizontal
}

void Player::Input()
{
	InputMovement();
	InputSpawnBomb();
}

void Player::InputMovement()
{
	//current_animation = 0;
	float up_1 = 0.f;
	float up_2 = 0.f;
	float right_1 = 0.f;
	float right_2 = 0.f;

	if (IsKeyDown(KEY_D))
	{
		right_1 = 1.f;
		current_animation = 1;
		rec_crop_entity_texture.width = std::abs(rec_crop_entity_texture.width);
	}

	if (IsKeyDown(KEY_A))
	{
		right_2 = -1.f;
		current_animation = 1;
		rec_crop_entity_texture.width = -std::abs(rec_crop_entity_texture.width);
	}

	if (IsKeyDown(KEY_W))
	{
		up_1 = -1.f;
		current_animation = 2;
	}

	if (IsKeyDown(KEY_S))
	{
		up_2 = 1.f;
		current_animation = 3;
	}

	input_up = up_1 + up_2;
	input_right = right_1 + right_2;
}

void Player::InputSpawnBomb()
{
	if (IsKeyPressed(KEY_C))
	{	
		if (!bCanPlaceBomb)
			return;

		bStartTimer = true;

		/* for now we are literally spawning every time, no object pooling stuff yet
		 but it should be fine for now */
		bomb = ACTOR_MANAGER->SpawnActor<Bomb>();
		if (!bomb)
			return;
		overlapped_entities.emplace(bomb, false);
		bomb->SetShowCollision(true); //just for debug sake
		bomb->SetLocation(collider.x, collider.y);
		bCanPlaceBomb = false;		
	}
}

void Player::OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor)
{
	Actor::OnCollisionBeginOverlap(otherActor);
}

void Player::OnCollisionEndOverlap(Actor& other_actor)
{
	Actor::OnCollisionEndOverlap(other_actor);
}