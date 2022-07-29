#include "Player.h"


void Player::OnCollisionOverlap(Entity& overlapped_actor_)
{
	printf("\ncoordinate of overlapped actor: %d\n ", overlapped_actor_.GetCoordinates().x);
	//overlapped_actor_.Destroy();
}

void Player::Update()
{
	Entity::Update();
    Movement();	
}

void Player::Movement()
{
    current_animation = 0;
    if (IsKeyDown(KEY_D))
    {
        current_animation = 1;        
        rec_crop_entity_texture.width = std::abs(rec_crop_entity_texture.width);
        AddMovement(speed, 0);
    }

    if (IsKeyDown(KEY_A))
    {
        current_animation = 1;
        rec_crop_entity_texture.width = -std::abs(rec_crop_entity_texture.width);
        AddMovement(-speed,0);

    }
    if (IsKeyDown(KEY_W))
    {
        current_animation = 2;
        AddMovement(0,-speed);

    }
    if (IsKeyDown(KEY_S))
    {
        current_animation = 3;
        AddMovement(0, speed);
    }


}
