#pragma once
#include "STAGE3.h"
#include <string>
#define GRID 40



class Phase_stage3Ending : public PhaseInterface {
private:
    //엔딩 텍스쳐
    SDL_Texture* winEnding_texture;
    SDL_Texture* loseEnding_texture;
    SDL_Rect ending_destination;
    //버튼 텍스트 텍스쳐
    SDL_Texture* retry_button_texture;
    SDL_Texture* home_button_texture;
    SDL_Rect retry_button_destination;
    SDL_Rect home_button_destination;
    
    // 엔딩 페이즈로 넘어온 시간을 저장하는 변수
    int endingPhaseStartTime;
    bool button; //버튼 생성 여부

    int buttonPushed;//1이면 retry버튼 =>intro로 이동 , 2면 home 버튼 main으로 이동

    TTF_Font* font = TTF_OpenFont("../../Resource/establish Retrosans.ttf", 100);
    
    int pageCheck;
public:
    Phase_stage3Ending();
    ~Phase_stage3Ending();

    void HandleEvents();
    void Update();
    void Render();
    void Reset();
};