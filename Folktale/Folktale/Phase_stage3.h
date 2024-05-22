#pragma once

#include "Creature_stage3.h"

extern bool g_flag_running;
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;

extern int screenWidth, screenHeight;

class Stage3
{
private:
    Bell* bell;
    Magpie* magpie;
    Snake* snake;
	Bomb* bomb;
	
	//����Ű ���� ������
	bool f_list[4];
	int f_state;//���� ���� Ű ����
	bool stop;//���� ����

	//���� Ȯ�� ����
	int game_result;

	SDL_RendererFlip flip;

public:
	Stage3();
	~Stage3();

	void HandleEvents();
	void Update();
	void Render();
	void Reset();

	int getResult() {
		return this->game_result;
	}

private:
	//�� �ؽ��� 
	SDL_Texture* bell_texture; // the SDL_Texture 
	SDL_Rect bell_destination_rect; // for destination
	//��ġ �ؽ���
	SDL_Texture* magpie_texture; // the SDL_Texture 
	SDL_Rect magpie_destination_rect; // for destination
	//������ �ؽ���
	///���
	SDL_Texture* snakeHead_texture; // the SDL_Texture 
	SDL_Texture* snakeBody_texture;
	SDL_Texture* snakeTail_texture;
	SDL_Texture* snakeCurve_texture;
	SDL_Rect snake_destination_rect; // for destination

	//��� �ؽ���
	SDL_Texture* bg_texture; // the SDL_Texture 
	SDL_Rect bg_destination_rect; // for destination

	//��ź �ؽ���
	SDL_Texture* bombPrev_texture;
	SDL_Texture* bombAfter_texture;

	//��Ʈ �ؽ���
	SDL_Texture* heartZero_texture; // the SDL_Texture 
	SDL_Texture* heartHalf_texture; // the SDL_Texture 
	SDL_Texture* heartOne_texture; // the SDL_Texture 
	SDL_Rect heart_destination_rect; // for destination
};