#pragma once
#include "STAGE.h"
#include <string>



class Phase_stage1Ending : public PhaseInterface {
private:
    //���� �ؽ���
    SDL_Texture* stg1_dandelion_ending_texture1;
    SDL_Texture* stg1_dandelion_ending_texture2;
    SDL_Texture* stg1_dogPoop_ending_texture1;
    SDL_Texture* stg1_dogPoop_ending_texture2;
    SDL_Texture* stg1_happy_ending_texture1;
    SDL_Rect stg1_ending_destination;
    //��ư �ؽ�Ʈ �ؽ���
    SDL_Texture* stg1_retry_button_texture;
    SDL_Texture* stg1_home_button_texture;
    SDL_Rect stg1_retry_button_destination;
    SDL_Rect stg1_home_button_destination;

    //���� ����
    Mix_Chunk* stg1_gosad_sound;
    Mix_Chunk* stg1_gohappy_sound;
    // ���� ������� �Ѿ�� �ð��� �����ϴ� ����
    int stg1_endingPhaseStartTime;
    bool  stg1_button; //��ư ���� ����

    int stg1_buttonPushed;//1�̸� retry��ư =>intro�� �̵� , 2�� home ��ư main���� �̵�

    //TTF_Font* font = TTF_OpenFont("../../Resource/establish Retrosans.ttf", 100);

    int stg1_pageCheck;
public:
    Phase_stage1Ending();
    ~Phase_stage1Ending();

    void HandleEvents();
    void Update();
    void Render();
    void Reset();
};