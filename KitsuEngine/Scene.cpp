#include "pch.h"


#include "Scene.hpp"
#include "Game.hpp"

#include <SDL3_Image/SDL_image.h>
#include <spdlog/spdlog.h>
#include <memory>

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
void Scene::Draw()
{
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
