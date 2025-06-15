#pragma once
#include "pch.h"

#include <entt/entt.hpp>
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <memory>
#include <typeindex>
#include <typeinfo>

#include "SafetyWrappers/Texture.hpp"
#include "System.hpp"

class Game;

class Scene
{
protected:
	entt::registry m_registry;
	std::vector<std::shared_ptr<Texture>> m_textures;
	std::vector<std::unique_ptr<ISystem>> m_systems;

	Game* m_game = nullptr;

	template<typename T, typename... Args>
	T* addSystem(Args&&... args)
	{
		const std::type_index type = typeid(T); // Getting a hashable info from type

		for (const auto& sys : m_systems) // go over all
		{
			if (typeid(*sys) == type) // check if system with the same type exists
			{
				spdlog::warn("System of type [{}] already exists in scene. Skipping add.", type.name());
				return static_cast<T*>(sys.get());
			}
		}

		auto sys = std::make_unique<T>(std::forward<Args>(args)...); // make a new if it doesn't
		T* ptr = sys.get();
		m_systems.push_back(std::move(sys));
		return ptr;
	}


public:
	Scene(Game* game);

	virtual void Init() = 0;
	virtual void Update();
	virtual void Draw();
	virtual void Events(const SDL_Event& event) { }

	entt::registry& GetRegistry() { return m_registry; }

	void AddTexture(std::shared_ptr<Texture> texture);
	std::shared_ptr<Texture> CreateTexture(std::string path);

	
	virtual ~Scene() {}
};