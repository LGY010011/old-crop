#pragma once
#include <SDL.h>
#include "Creature_stage3.h"

extern bool g_flag_running;

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
};