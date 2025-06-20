#include "pch.h"
#include "Game.hpp"
#include "Globals.hpp"
#include "Scene.hpp"

#include <cassert>
#include <spdlog/spdlog.h>
#include <SDL3/SDL.h>

void Game::DoDeltaTime()
{
    Uint64 currentTime = SDL_GetTicks();

    if (previousTime > 0) 
    {
        dt = (currentTime - previousTime) / 1000.0f; 
    }

    previousTime = currentTime;
}

void Game::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            spdlog::info("QUIT Event started");
            m_quit_game = true;
        }

        m_scene->Events(event);
    }
}

void Game::Update()
{
    m_scene->Update();
}

void Game::Draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    m_scene->Draw();

    SDL_RenderPresent(renderer);

}

void Game::MainLoop()
{
    while (!m_quit_game)
    {
        DoDeltaTime();
        HandleEvents();
        Update();
        Draw();
    }
}

void Game::StartGame(Scene* scene)
{
    spdlog::info("========== Game Initialization ==========");

    if (window == nullptr) 
    {
        spdlog::error("Window has not been created and assigned");
        assert(window != nullptr);
    }

    if (scene == nullptr)
    {
        spdlog::error("Expected valid scene, got nullptr");
        assert(scene != nullptr);
    }

    if (renderer == nullptr)
    {
        spdlog::error("Renderer has not been created and assigned");
        assert(renderer != nullptr);
    }

    m_scene = std::unique_ptr<Scene>(scene);
    m_scene->Init();

    spdlog::info("Starting game loop");
    spdlog::info("========== Initialization Finished ==========");
	MainLoop();
}
