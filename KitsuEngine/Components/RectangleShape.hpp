#pragma once
#include <SDL3/SDL.h>


struct RectangleShape
{
	float width;
	float height;
	int layer = 5;
	SDL_Color color;
};