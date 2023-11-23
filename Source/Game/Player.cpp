#include "Player.h"
#include "Bomb.h"
#include "Explosion.h"

#include "Engine/Managers/ActorManager.h"
#include "Engine/Managers/PoolManager.h"

// components
#include "HealthComponent.h"

#include <functional>

Player::Player() : Actor()
{
	//Here we insert inside the animations array each sprite we want it to be cycling
	idle.push_back(RecCropLocation(0, 32));


	walk_horizontal.push_back(RecCropLocation(30, 130));
	walk_horizontal.push_back(RecCropLocation(63, 130));
	walk_horizontal.push_back(RecCropLocation(96, 130));
	walk_horizontal.push_back(RecCropLocation(127, 130));

	walk_up.push_back(RecCropLocation(0, 65));
	walk_up.push_back(RecCropLocation(32, 65));
	walk_up.push_back(RecCropLocation(64, 65));
	walk_up.push_back(RecCropLocation(96, 65));
	walk_up.push_back(RecCropLocation(130, 65));

	walk_down.push_back(RecCropLocation(34, 32));
	walk_down.push_back(RecCropLocation(64, 32));
	walk_down.push_back(RecCropLocation(97, 32));
	walk_down.push_back(RecCropLocation(129, 32));

	CropSprite(idle[0].x, idle[0].y);

	//Load animations
	mAnimations.push_back(AnimationData(idle));
	mAnimations.push_back(AnimationData(walk_horizontal));
	mAnimations.push_back(AnimationData(walk_up));
	mAnimations.push_back(AnimationData(walk_down));

	bCanPlaceBomb = true;
	bStartTimer = false;
	timer = 4.f; //cooldown of player to place bombs
	initialTimer = timer;
	mSpeed = 25.f;
	mName = "Player";
}


Player::~Player()
{

}


void Player::Start()
{
	Actor::Start();

	// Creating health component
	healthComp = std::make_shared<HealthComponent>(3); // set max and current life

	// bind on die callback from health component
	healthComp->SetHealthChangeCallback
	(
		std::bind
		(&Player::OnDie,
			this
		) 
	);

	// let's reserve the bomb to use later
	//bomb = ACTOR_MANAGER->SpawnActor<Bomb>();
	//for (int i = 0; i < 5; i++)
	//{
	//	bombs[i] = ACTOR_MANAGER->SpawnActor<Bomb>();
	//}
}

void Player::Update()
{
	Actor::Update();

#pragma region DEBUG STUFF (show information on screen)

	{
		//std::string hp = "HP: " + std::to_string(healthComp->GetCurrentHP()) ;
		//DrawText(hp.c_str(), 0, 25, 24, YELLOW);
	}
	//	DEBUG: overlapped entities
	{
		std::string hp = "OE: " + std::to_string(overlapped_entities.size());
		DrawText(hp.c_str(), 0, 55, 24, YELLOW);
	}
#pragma endregion DEBUG STUFF (show information on screen)


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

	//Normalize input so character don't walk faster if moving diagonally
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
		mCurrentAnimation = 1;
		mRecCropEntityTexture.width = std::abs(mRecCropEntityTexture.width);
	}

	if (IsKeyDown(KEY_A))
	{
		right_2 = -1.f;
		mCurrentAnimation = 1;
		mRecCropEntityTexture.width = -std::abs(mRecCropEntityTexture.width);
	}

	if (IsKeyDown(KEY_W))
	{
		up_1 = -1.f;
		mCurrentAnimation = 2;
	}

	if (IsKeyDown(KEY_S))
	{
		up_2 = 1.f;
		mCurrentAnimation = 3;
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

		if (!bombs[itrBomb])
		{
			if (itrBomb <= bombs.size() - 1)
			{
				bombs[itrBomb] = ACTOR_MANAGER->SpawnActor<Bomb>();
			}
		}


		
		//if (!bomb)
		//{
		//	bomb = ACTOR_MANAGER->SpawnActor<Bomb>();
		//}

		bombs[itrBomb]->SetActive(true);
		//overlapped_entities.emplace(bomb, false);
		bombs[itrBomb]->SetShowCollision(true); //just for debug sake
		bombs[itrBomb]->SetLocation(mCollider.x, mCollider.y);
		
		if (itrBomb + 1 >= bombs.size())
		{
			itrBomb = 0;
		}
		else
		{
			itrBomb++;
		}
	//	bCanPlaceBomb = false;		
	}
}



void Player::OnCollisionBeginOverlap(std::shared_ptr<Actor> otherActor)
{
	Actor::OnCollisionBeginOverlap(otherActor);


}

void Player::OnCollisionEndOverlap(std::shared_ptr<Actor> otherActor)
{
	Actor::OnCollisionEndOverlap(otherActor);
}

void Player::OnDie()
{
	SetActive(false);
}

/***************** INTERFACES ***********************/
void Player::OnTakenDamage(Actor* damageCauser, int damageAmount)
{
	std::cout << __FUNCTION__ << std::endl;

	if (!damageCauser)
		return;

	if (healthComp)
	{
		healthComp->TakeDamage(damageAmount);
	}
}