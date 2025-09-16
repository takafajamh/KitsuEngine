#pragma once
#include <string>
#include <vector>
#include <SDL3/SDL.h>

/// <summary>
/// A single frame of an animation, consists of an FRect of the texture and the duration of the frame
/// </summary>
struct Frame
{
	SDL_FRect frame;
	float duration;
};

struct Animation
{
	std::string name;
	std::vector<Frame> frames;
};

/// <summary>
/// Component for an Entity
/// </summary>
struct Animator
{
	std::vector<Animation> anims;	// stored animations
	bool looping = false;			// does the animation loop
	bool restartOnFinish = false;	// if the animation is not looping, should the entity finish with the 1st frame image? (True or False for last)

	std::string currentAnimationName = "";	// currently playing animation, default - ""
	int currentAnimationId = -1;			// current animation id, default - -1 (for not playinh)
	float currentTime = 0;					// how long has the frame been on
	int currentFrame = 0;					// which frame is playing currently

	std::string ToPlay = "";				// variable to start playing an animation, based on the animation name (case sensitive)
};

