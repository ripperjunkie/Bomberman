#include "TextureManager.h"

TextureManager* TextureManager::mInstance = nullptr;
Texture2D TextureManager::texture;
TextureManager::TextureManager()
{
	texture = LoadTexture("resources/133670.png");
}
