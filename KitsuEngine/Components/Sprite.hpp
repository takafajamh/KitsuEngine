	#pragma once
	#include "../SafetyWrappers/Texture.hpp"
	#include <memory>

	struct Sprite
	{
		float sizeX;					// Size in pixels
		float sizeY;					// Size in pixels

		bool flipX = false;

		int layerOrder = 9;				// layer (for sprites)

		bool useTextureRect = false;	// is a texture rect used
		SDL_FRect textureRect;			// what is the texture rect, important only if useTextureRect is true

		std::shared_ptr<Texture> texture; // Pointer to a used texture
	};