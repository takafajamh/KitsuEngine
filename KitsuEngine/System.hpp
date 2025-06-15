#pragma once
#include <entt/entt.hpp>

class ISystem
{
public:
	float camXPos = 0;
	float camYPos = 0;

	virtual void Update(entt::registry& registry) {}
	virtual void Render(entt::registry& registry) {}
};