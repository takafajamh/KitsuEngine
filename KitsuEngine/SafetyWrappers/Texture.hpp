#pragma once
#include "../pch.h"
#include <SDL3/SDL.h>
#include <SDL3_Image/SDL_image.h>
#include "../KitsuAsserts.hpp"

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
		acquisition_assert(SDL_texture, path, SDL_GetError());

		m_path = path;

		kitsu_assert(SDL_SetTextureScaleMode(SDL_texture, SDL_SCALEMODE_NEAREST), "[Texture] Could not set Texture Scale Mode - {}", "[Texture] Texture Scale Mode set correctly", SDL_GetError());
		kitsu_assert(SDL_SetTextureBlendMode(SDL_texture, SDL_BLENDMODE_BLEND), "[Texture] Could not set Texture Blend Mode - {}", "[Texture] Texture Blend Mode set correctly", SDL_GetError());

		spdlog::info("[Texture] Texture from {} loaded correctly", path);
	}

	~Texture()
	{
		spdlog::info("[Texture] Deleting texture {} ", m_path);
		SDL_DestroyTexture(SDL_texture);
	}

	SDL_Texture* getSDL()
	{
		return SDL_texture;
	}
};