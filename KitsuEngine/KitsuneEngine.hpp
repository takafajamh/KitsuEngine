#pragma once
#include "pch.h"

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include "Globals.hpp"
#include "Game.hpp"
#include "Scene.hpp"

inline int KitsuEngineInit(const int windowWidth, const int windowHeight)
{
    spdlog::info("Starting SDL3...");

    if (SDL_Init(SDL_INIT_VIDEO) != true)
    {
        spdlog::error("SDL_Init failed: {}", SDL_GetError());
        return -1;
    }

    spdlog::info("SDL3 Initialized!");


    window = SDL_CreateWindow("SDL3 Test", windowWidth, windowHeight, 0);
    if (!window)
    {
        spdlog::error("Failed to create window: {}", SDL_GetError());
        SDL_Quit();
        return -1;
    }


    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        spdlog::error("Failed to create renderer: {}", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    spdlog::info("Window created!");
    return 0;
}

inline void KitsuEngineClean()
{
    spdlog::info("Starting cleanup");

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
