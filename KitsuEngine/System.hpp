#pragma once
#include <entt/entt.hpp>

class ISystem
{
public:
	virtual void Update(entt::registry& registry) {}
	virtual void Render(entt::registry& registry) {}
};