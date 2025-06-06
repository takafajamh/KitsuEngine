#pragma once
#include "pch.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_Mixer/SDL_mixer.h>
#include <spdlog/spdlog.h>

#include "Globals.hpp"
#include "Game.hpp"
#include "Scene.hpp"
#include "SafetyWrappers/Font.hpp"
#include "SafetyWrappers/Texture.hpp"


struct WindowParams
{
    bool Transparent = false;
    bool AlwaysOnTop = false;
    bool Fullscreen = false;
    bool Borderless = false;
    bool Resizable = false;
    bool SetPosition = false;
    int PosX = -1;
    int PosY = -1;

};


/// <summary>
/// Initializes SDL, TTF, Audio, Window, Renderer
/// </summary>
/// <param name="windowWidth">Width of the window</param>
/// <param name="windowHeight">Height of the window</param>
/// <param name="title">Title of the window</param>
/// <param name="args">Additional parameters of struct Type WindowParams</param>
/// <returns></returns>
inline int KitsuEngineInit(const int windowWidth, const int windowHeight, const std::string& title, const WindowParams* args = nullptr)
{
    spdlog::info("========== SDL3 Initialization ==========");

    if (SDL_Init(SDL_INIT_VIDEO) != true)
    {
        spdlog::error("SDL_Init failed: {}", SDL_GetError());
        return -1;
    }
    spdlog::info("SDL3 Initialized!");

    if (TTF_Init() != true) 
    {
        spdlog::error("TTF_Init failed: {}", SDL_GetError());
        return 1;
    }
    spdlog::info("SDL3 TTF Initialized!");

    if (SDL_Init(SDL_INIT_AUDIO) != true)
    {
        spdlog::error("SDL_Init Audio failed: {}", SDL_GetError());   
        return 1;
    }
    spdlog::info("SDL3 Audio Initialized!");

    spdlog::info("========== Window Initialization ==========");

    Uint32 windowFlags = 0;

    if (args == nullptr)
    {
        spdlog::info("No Window Creation parameters found, standard parameters set");
    }
    else
    {
        if (args->Transparent)
        {
            spdlog::info("Window set into Transparent mode");
            windowFlags |= SDL_WINDOW_TRANSPARENT;
        }

        if (args->Fullscreen)
        {
            spdlog::info("Window set to be fullscreen");
            windowFlags |= SDL_WINDOW_FULLSCREEN;
        }

        if (args->Borderless)
        {
            spdlog::info("Window set to be fullscreen");
            windowFlags |= SDL_WINDOW_BORDERLESS;
        }

        if (args->Resizable)
        {
            spdlog::info("Window is now resizable");
            windowFlags |= SDL_WINDOW_RESIZABLE;
        }

        if (args->AlwaysOnTop)
        {
            spdlog::info("Window set to be always on top");
            windowFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
        }
            
    }
    
    window = SDL_CreateWindow(title.c_str(), windowWidth, windowHeight, windowFlags);

    if (!window)
    {
        spdlog::error("Failed to create window: {}", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    spdlog::info("Window created!");


    if (args)
    {
        if (args->SetPosition)
        {
            if (!SDL_SetWindowPosition(window, args->PosX, args->PosY))
                spdlog::warn("Failed to set window position: {}", SDL_GetError());
            else
                spdlog::info("Window position changed into - {}, {}", args->PosX, args->PosY);
        }
    }

    spdlog::info("========== Remaining Initialization ==========");

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        spdlog::error("Failed to create renderer: {}", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    spdlog::info("Renderer created!");

    spdlog::info("========== Initialization Finished ==========\n");

    return 0;
}

inline void KitsuEngineClean()
{
    spdlog::info("Starting cleanup");

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
