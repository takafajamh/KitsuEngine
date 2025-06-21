#pragma once
#include "pch.h"

#include <memory>
#include <SDL3/SDL.h>

class Scene;

class Game 
{
private:
	Uint64 previousTime = 0;

	bool m_quit_game = false;

	std::unique_ptr<Scene> m_scene;

	void DoDeltaTime();

	void HandleEvents();

	void Update();

	void Draw();

	void MainLoop();
public:
	void StartGame(Scene* scene);

	virtual ~Game() {}
};