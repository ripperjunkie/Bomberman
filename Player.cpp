#include "Player.h"


void Player::CollisionOverlap(Entity& overlapped_actor_)
{
	printf("\ncoordinate of overlapped actor: %d\n ", overlapped_actor_.GetCoordinates().x);
	overlapped_actor_.Destroy();
}

void Player::Update()
{
	Entity::Update();
    Movement();
	
}

void Player::Movement()
{
    if (IsKeyDown(KEY_D))
    {
        current_animation = 0;        
        rec_crop_entity_texture.width = std::abs(rec_crop_entity_texture.width);

        AddMovement(10, 0);
    }

    if (IsKeyDown(KEY_A))
    {
        current_animation = 0;
        rec_crop_entity_texture.width = -std::abs(rec_crop_entity_texture.width);
        AddMovement(-10,0);

    }
    if (IsKeyDown(KEY_W))
    {
        current_animation = 2;

        AddMovement(0,-10);
    }
    if (IsKeyDown(KEY_S))
    {
        current_animation = 1;
        AddMovement(0,10);

    }
}
