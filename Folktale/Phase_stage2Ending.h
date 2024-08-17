#pragma once
#pragma once
#include "STAGE.h"
#include <string>
#define GRID 40



class Phase_stage2Ending : public PhaseInterface {
private:
    //���� �ؽ���
    SDL_Texture* winEnding_texture;
    SDL_Texture* loseEnding_texture1;
    SDL_Texture* loseEnding_texture_gameover;
    SDL_Rect ending_destination;
    //��ư �ؽ�Ʈ �ؽ���
    SDL_Texture* retry_button_texture;
    SDL_Texture* main_button_texture;
    SDL_Rect retry_button_destination;
    SDL_Rect main_button_destination;

    // ���� ������� �Ѿ�� �ð��� �����ϴ� ����
    int endingPhaseStartTime;
    int buttonToTime;
    bool button;

    int flag = false;

    int buttonPushed;//1�̸� retry��ư =>intro�� �̵� , 2�� home ��ư main���� �̵�


    int pageCheck;

    Mix_Music* win_music;
    Mix_Music* lose_music;
    Mix_Chunk* button_sound;
public:
    Phase_stage2Ending();
    ~Phase_stage2Ending();

    void HandleEvents();
    void Update();
    void Render();
    void Reset();
};