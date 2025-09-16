#pragma once
#include "pch.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_Mixer/SDL_mixer.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include "Globals.hpp"
#include "Game.hpp"
#include "Scene.hpp"
#include "SafetyWrappers/Font.hpp"
#include "SafetyWrappers/Texture.hpp"
#include "KitsuAsserts.hpp"


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

    kitsu_return_assert(SDL_Init(SDL_INIT_VIDEO), "[KitsuEngine] SDL_Init Video failed: ", "[KitsuEngine] SDL_Init Video succeded", -1, SDL_GetError());
    kitsu_return_assert(TTF_Init(), "[KitsuEngine] TTF_Init failed: ", "[KitsuEngine] TTF_Init succeded", -1, SDL_GetError());
    kitsu_return_assert(SDL_Init(SDL_INIT_AUDIO), "[KitsuEngine] SDL_Init Audio failed: ", "[KitsuEngine] SDL_Init Audio succeded", -1, SDL_GetError());
    kitsu_return_assert(Mix_Init(MIX_INIT_OGG | MIX_INIT_FLAC), "[KitsuEngine] Mix_Init for OGG and FLAC failed: ", "[KitsuEngine] Mix_Init for OGG and FLAC succeded", -1, SDL_GetError());
    kitsu_return_assert(Mix_OpenAudio(0, nullptr), "[KitsuEngine] Mix_OpenAudio failed: ", "[KitsuEngine] Mix_OpenAudio succeded", -1, SDL_GetError());

    spdlog::info("========== Window Initialization ==========");

    Uint32 windowFlags = 0;

    if (args == nullptr)
    {
        spdlog::info("[KitsuEngine] No Window Creation parameters found, standard parameters set");
    }
    else
    {
        if (args->Transparent)
        {
            spdlog::info("[Window] Window set into Transparent mode");
            windowFlags |= SDL_WINDOW_TRANSPARENT;
        }

        if (args->Fullscreen)
        {
            spdlog::info("[Window] Window set to be fullscreen");
            windowFlags |= SDL_WINDOW_FULLSCREEN;
        }

        if (args->Borderless)
        {
            spdlog::info("[Window] Window set to be fullscreen");
            windowFlags |= SDL_WINDOW_BORDERLESS;
        }

        if (args->Resizable)
        {
            spdlog::info("[Window] Window is now resizable");
            windowFlags |= SDL_WINDOW_RESIZABLE;
        }

        if (args->AlwaysOnTop)
        {
            spdlog::info("[Window] Window set to be always on top");
            windowFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
        }
            
    }
    
    window = SDL_CreateWindow(title.c_str(), windowWidth, windowHeight, windowFlags);

    kitsu_return_assert(window, "[KitsuEngine] Failed to create window: ", "[KitsuEngine] Window creation succeded", -1, SDL_GetError());


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
    kitsu_return_assert(renderer, "[KitsuEngine] Failed to create renderer: ", "[KitsuEngine] Renderer created", -1, SDL_GetError());

    kitsu_return_assert(SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND), "[Renderer] Failed to ensure Blend: ", "[Renderer] ensured Blend", -1, SDL_GetError());


    spdlog::info("========== Initialization Finished ==========\n");

    return 0;
}

inline void KitsuEngineClean()
{
    spdlog::info("========== Starting cleanup ==========");
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
