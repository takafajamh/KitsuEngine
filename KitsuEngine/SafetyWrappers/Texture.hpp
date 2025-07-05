#pragma once
#include "../pch.h"
#include <SDL3/SDL.h>
#include <SDL3_Image/SDL_image.h>

#include <spdlog/spdlog.h>

#include "../Globals.hpp"
#include <string>

class Texture
{
private:
	std::string m_path;
public:
	SDL_Texture* SDL_texture = nullptr;

	Texture(std::string path)
	{
		SDL_texture = IMG_LoadTexture(renderer, path.c_str());
		if (SDL_texture == nullptr)
		{
			spdlog::error("Could not load the texture - {}", SDL_GetError());
			assert(false);
		}
		m_path = path;

		if (!SDL_SetTextureScaleMode(SDL_texture, SDL_SCALEMODE_NEAREST))
		{
			spdlog::error("Could not set Texture Scale Mode - {}", SDL_GetError());
			assert(false);
		}

		if (!SDL_SetTextureBlendMode(SDL_texture, SDL_BLENDMODE_BLEND))
		{
			spdlog::error("Could not set Texture Blend Mode - {}", SDL_GetError());
			assert(false);
		}


		spdlog::info("Texture from {} loaded correctly", path);
	}

	~Texture()
	{
		spdlog::info("Deleting texture {} ", m_path);
		SDL_DestroyTexture(SDL_texture);
	}

	SDL_Texture* getSDL()
	{
		return SDL_texture;
	}
};