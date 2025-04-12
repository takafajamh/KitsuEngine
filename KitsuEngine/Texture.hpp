#pragma once
#include "pch.h"
#include <SDL3/SDL.h>
#include <SDL3_Image/SDL_image.h>

#include <spdlog/spdlog.h>

#include "Globals.hpp"
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
			assert(SDL_texture != nullptr);
		}
		m_path = path;
		spdlog::info("Texture from {} loader correctly", path);
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