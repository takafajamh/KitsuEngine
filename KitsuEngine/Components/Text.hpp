#pragma once
#include "../SafetyWrappers/Font.hpp"
#include <SDL3/SDL.h>
#include <memory>

struct Text 
{
    std::string content;            // Text to be shown
    SDL_Color color;                // Text color, inner
    std::shared_ptr<Font> font;     // Font
    float xSize;                    // Aproximate size, the text wraps after the size is reached            
    float ySize;                    // Used for the destination Rect, but doesn't really matter?           
    int fontSize;                   // Text size
    int padding = 1;                // Space between lines when wrapping
};