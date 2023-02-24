#include "Player.h"
#include "raymath.h"
#include "iostream"
#include "Bomb.h"


void Player::OnCollisionOverlap(Entity& overlapped_actor_)
{
    Entity::OnCollisionOverlap(overlapped_actor_);
	//printf("\ncoordinate of overlapped actor: %d\n ", overlapped_actor_.GetCoordinates().x);
	//overlapped_actor_.Destroy();
}

void Player::Update()
{
	Entity::Update();

    Input();
	Vector2 normalize_vector = Vector2Normalize(Vector2(input_right, input_up));
    AddMovement(Vector2(0,1), normalize_vector.y); //vertical
	AddMovement(Vector2(1,0), normalize_vector.x); //horizontal
}

void Player::Input()
{
	InputMovement();
	InputSpawnBomb();

}

void Player::InputMovement()
{
	current_animation = 0;
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
		Bomb* bomb = new Bomb(*tile_map, ECollisionType::OVERLAP, EObjectMovType::MOVABLE, true, shared_sprite_sheet);
		if (bomb)
		{
			bomb->SetLocation(entity_collision.x, entity_collision.y);
			tile_map->entities.push_back(*bomb);
		}

	}
}
