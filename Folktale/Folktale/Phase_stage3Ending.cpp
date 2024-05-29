#include "Phase_stage3Ending.h"

Phase_stage3Ending::Phase_stage3Ending() {
    // 배경 텍스쳐
    SDL_Surface* temp_sheet_surface = IMG_Load("../../Resource/winEnding.png");
    winEnding_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    temp_sheet_surface = IMG_Load("../../Resource/loseEnding.png");
    loseEnding_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    ending_destination.x = 0;
    ending_destination.y = 0;
    ending_destination.w = screenWidth;
    ending_destination.h = screenHeight;
    
    // 버튼 텍스쳐
    SDL_Surface* tmp_surface = IMG_Load("../../Resource/retry.png");
    retry_button_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    if (retry_button_texture == NULL)
        std::cout<<"retry_button_texture is NULL\n"<<std::endl;
    SDL_FreeSurface(tmp_surface);
    retry_button_destination.x = 100;
    retry_button_destination.y = 100;
    retry_button_destination.w = 100;
    retry_button_destination.h = 50;

    tmp_surface = IMG_Load("../../Resource/home.png");
    home_button_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);
    // 버튼 텍스쳐의 색상을 파란색으로 변경
    home_button_destination.x = retry_button_destination.x;
    home_button_destination.y = retry_button_destination.y + 80;
    home_button_destination.w = 100;
    home_button_destination.h = 50;


    button = false;
    endingPhaseStartTime = 0;
    buttonPushed = 0; //0이면 버튼 안누름, 1이면 retry버튼 누름, 2이면 home버튼 누름
    pageCheck = 0;
}

void Phase_stage3Ending::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;          

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
                if (button) {//버튼이 켜져있으면 버튼을 누르는 순간

                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;

                    if (mouse_x >= retry_button_destination.x && mouse_x <= retry_button_destination.x + retry_button_destination.w &&
                        mouse_y >= retry_button_destination.y && mouse_y <= retry_button_destination.y + retry_button_destination.h
                        )
                        buttonPushed= 1;
                    else if (mouse_x >= home_button_destination.x && mouse_x <= home_button_destination.x + home_button_destination.w &&
                        mouse_y >= home_button_destination.y && mouse_y <= home_button_destination.y + home_button_destination.h
                        )
                        buttonPushed = 2;
                }

            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_SPACE) {
                pageCheck++;
                std::cout<<"menu"<<std::endl;
                endingPhaseStartTime = SDL_GetTicks();
            }
            break;
        }
    }
}

void Phase_stage3Ending::Update() {
    if (g_prev_game_phase != g_current_game_phase)
        endingPhaseStartTime = SDL_GetTicks();

    int currentTime = SDL_GetTicks();
    if (currentTime - endingPhaseStartTime > 3000) { // 3초가 지났다면
        // 버튼 보이게 함
        button = true;
    }else
        button = false;

    if (game_result == 5) {
        pageCheck = 1;
        
    }
    if (pageCheck == 3) {
        g_current_game_phase = PHASE_INTRO;
        game_result = 0;
    }

    
    if (buttonPushed == 1) {
        g_current_game_phase = PHASE_STAGE;
        game_result = 0;
    }
    else if (buttonPushed == 2) {
        g_current_game_phase = PHASE_INTRO;
        game_result = 0;
    }
    

}

    
void Phase_stage3Ending::Render() {
    if(game_result==1 ||pageCheck==1)
        SDL_RenderCopy(g_renderer, winEnding_texture, NULL, &ending_destination);
    else if(game_result==2 || pageCheck == 2)
        SDL_RenderCopy(g_renderer, loseEnding_texture, NULL, &ending_destination);

    
    
    if (button) {
        
        SDL_RenderCopy(g_renderer, retry_button_texture, NULL, &retry_button_destination);
        SDL_RenderCopy(g_renderer, home_button_texture, NULL, &home_button_destination);

    }
    
    SDL_RenderPresent(g_renderer);
}

void Phase_stage3Ending::Reset() {
    button = false;
    buttonPushed = 0; //0이면 버튼 안누름, 1이면 retry버튼 누름, 2이면 home버튼 누름
    pageCheck = 0;
    ///endingPhaseStartTime = 0;
}

Phase_stage3Ending::~Phase_stage3Ending() {
    SDL_DestroyTexture(winEnding_texture);
    SDL_DestroyTexture(loseEnding_texture);
    SDL_DestroyTexture(retry_button_texture);
    SDL_DestroyTexture(home_button_texture);


}


