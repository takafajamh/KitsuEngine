#include "pch.h"
#include "Scene.hpp"
#include "Game.hpp"

#include <SDL3_Image/SDL_image.h>
#include <spdlog/spdlog.h>
#include <memory>
#include <unordered_map>

struct PairHash
{
	std::size_t operator()(const std::pair<int, int>& p) const noexcept
	{
		return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
	}
};



Scene::Scene(Game* game)
{
	m_game = game;
	
	if (game == nullptr)
	{
		spdlog::error("Tried making a scene with invalid Game adress, Null Pointer");
		assert(game != nullptr);
	}

	spdlog::info("Scene created");
}

void Scene::AddTexture(std::shared_ptr<Texture> texture)
{
	m_textures.push_back(texture);
}
void Scene::Update()
{
	for (std::unique_ptr<ISystem>& sys : m_systems)
	{
		sys->Update(m_registry);
	}
}

std::pair<int, int> Scene::findCamPos()
{
	std::unordered_map<std::pair<int, int>, int, PairHash> changes;

	
	for (const std::unique_ptr<ISystem>& sys : m_systems)
	{
		std::pair<int, int> key{ sys->camXPos, sys->camYPos };
		changes[key]++;
	}
	
	std::pair<int, int> leastFrequent{};
	int minCount = std::numeric_limits<int>::max();

	for (const auto& [coords, count] : changes)
	{
		if (count < minCount)
		{
			minCount = count;
			leastFrequent = coords;
		}
	}

	return leastFrequent;
}

void Scene::Draw()
{
	if (xCamPos == nullptr)
	{
		std::pair<int, int> pos = findCamPos();
		for (std::unique_ptr<ISystem>& sys : m_systems)
		{
			sys->camXPos = pos.first;
			sys->camYPos = pos.second;
		}
	}

	for (std::unique_ptr<ISystem>& sys : m_systems)
	{
		if (xCamPos != nullptr)
		{
			sys->camXPos = *xCamPos;
			sys->camYPos = *yCamPos;
		}
		sys->Render(m_registry);
	}
	for (std::unique_ptr<ISystem>& sys : m_systems)
	{
		sys->UIRender(m_registry);
	}
}

std::shared_ptr<Texture> Scene::CreateTexture(std::string path)
{
	std::shared_ptr<Texture> tex = std::make_shared<Texture>(path);
	AddTexture(tex);
	return tex;
}
