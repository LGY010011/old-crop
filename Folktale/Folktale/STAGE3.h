#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_STAGE = 1;
const int PHASE_ENDING = 2;


class PhaseInterface
{
public:
    PhaseInterface() {};

    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Reset() = 0;

};

extern TTF_Font* font;

extern int g_current_game_phase;
extern int g_prev_game_phase;

extern bool g_flag_running;
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;

extern int screenWidth, screenHeight;
extern int game_result;