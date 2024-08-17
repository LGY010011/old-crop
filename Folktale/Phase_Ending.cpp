
#include "Game.h"
#include "Phase_Ending.h"

Ending::Ending()
{
    // For Texture


}

Ending::~Ending()
{

}

void Ending::Update()
{
}


void Ending::Render()
{
    SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 255);
    SDL_RenderClear(g_renderer); // clear the renderer to the draw color

    SDL_RenderPresent(g_renderer);
}



void Ending::HandleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_MOUSEBUTTONDOWN:

            // If the mouse left button is pressed. 
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                g_current_game_phase = PHASE_INTRO;
            }
            break;

        default:
            break;
        }
    }
}

void Ending::Reset()
{
    // Reset the game phase
    g_current_game_phase = PHASE_INTRO;
}