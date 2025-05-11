#pragma once
#include "pch.h"

#include <entt/entt.hpp>
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <memory>

#include "Texture.hpp"

class Game;

class Scene
{
protected:
	entt::registry m_registry;
	std::vector<std::shared_ptr<Texture>> m_textures;
	Game* m_game = nullptr;

public:
	Scene(Game* game);

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Events(const SDL_Event& event) = 0;

	entt::registry& GetRegistry() { return m_registry; }

	void AddTexture(std::shared_ptr<Texture> texture);
	std::shared_ptr<Texture> CreateTexture(std::string path);

	
	virtual ~Scene() {}
};