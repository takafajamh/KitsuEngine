#pragma once
#include "Position.hpp"
#include "Sprite.hpp"

/// <summary>
/// Supposed to change the layer of (playerSprite) to a higher or lower than (playerPos) depending on it's Y position
/// </summary>
struct HeightDependendLayer
{
	Position* playerPos = nullptr;
	Sprite* playerSprite = nullptr;
};