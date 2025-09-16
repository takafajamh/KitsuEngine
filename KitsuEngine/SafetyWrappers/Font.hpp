#pragma once
#pragma once
#include "../pch.h"
#include "../KitsuAsserts.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <spdlog/spdlog.h>

#include "../Globals.hpp"
#include <string>

class Font
{
private:
	std::string m_path;
public:
	TTF_Font* SDL_Font = nullptr;

	Font(std::string path)
	{
		SDL_Font = TTF_OpenFont(path.c_str(), 24);
		acquisition_assert(SDL_Font, path, SDL_GetError());

		m_path = path;

		spdlog::info("[Font] Font from {} loaded correctly", path);
	}

	~Font()
	{
		spdlog::info("[Font] Deleting Font {} ", m_path);
		TTF_CloseFont(SDL_Font);
	}

	TTF_Font* getSDL()
	{
		return SDL_Font;
	}
};