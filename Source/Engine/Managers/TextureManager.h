#pragma once
#include <raylib.h>


class TextureManager
{
public:
	static TextureManager* GetInstance()
	{
		if (!mInstance)
		{
			mInstance = new TextureManager();
		}
		return mInstance;
	}
	static Texture2D GetTexture()
	{
		return texture;
	}
private:
	TextureManager();
	static TextureManager* mInstance;
	static Texture2D texture;
};
