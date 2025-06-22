#pragma once
#include "pch.h"
#include <SDL3/SDL.h>


inline SDL_Window* window = nullptr;
inline SDL_Renderer* renderer = nullptr;
inline float dt = 0;


inline bool SDL_FRectIntersects(const SDL_FRect& a, const SDL_FRect& b)
{
	return !(a.x + a.w <= b.x || b.x + b.w <= a.x ||
		a.y + a.h <= b.y || b.y + b.h <= a.y);
}