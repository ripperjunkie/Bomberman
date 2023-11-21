#include "TextureManager.h"
#include "Game/GameUtils.h"

TextureManager* TextureManager::mInstance = nullptr;
Texture2D TextureManager::texture;
TextureManager::TextureManager()
{
	texture = LoadTexture(SPRITE_SHEET_PATH);
}
