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
    if (IsKeyPressed(KEY_D))
    {
        int x = GetCoordinates().x;
        x += 1;
        current_animation = 0;        
        rec_crop_entity_texture.width = std::abs(rec_crop_entity_texture.width);
        SetLocation(GetCoordinates().y, x);
    }

    if (IsKeyPressed(KEY_A))
    {
        int x = GetCoordinates().x;
        x -= 1;
        current_animation = 0;
        rec_crop_entity_texture.width = -std::abs(rec_crop_entity_texture.width);
        SetLocation(GetCoordinates().y, x);
    }
    if (IsKeyPressed(KEY_W))
    {
        int y = GetCoordinates().y;
        y -= 1;
        current_animation = 2;
        SetLocation(y, GetCoordinates().x);
    }
    if (IsKeyPressed(KEY_S))
    {
        int y = GetCoordinates().y;
        y += 1;
        current_animation = 1;
        SetLocation(y, GetCoordinates().x);

    }
}
