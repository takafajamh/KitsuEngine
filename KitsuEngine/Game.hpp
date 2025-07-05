#pragma once
#include "pch.h"

#include <memory>
#include <SDL3/SDL.h>
#include <SDL3_Mixer/SDL_mixer.h>

class Scene;

class Game 
{
private:
	Uint64 previousTime = 0;

	bool m_quit_game = false;

	std::unique_ptr<Scene> m_scene;

	Scene* toChange = nullptr;

	void DoDeltaTime();

	void HandleEvents();

	void Update();

	void Draw();

	void MainLoop();
public:
	Mix_Music* music = nullptr;
	int Volume = 60;

	void StartGame(Scene* scene);

	void NewScene(Scene* scene);

	void StopGame();

	virtual ~Game() {}
};