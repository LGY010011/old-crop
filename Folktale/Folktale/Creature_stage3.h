#pragma once
#include "Creature.h"
#include <list>
#include <random>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#define SNAKESIZE 15
#define GRID 40

using namespace std;

//ui ���� �� �� ���ͼ� �Ҵ��ϱ�
//���⼭ ������ ���� ������ phase_stage3, main���� ��� ����
enum DIRECTION { LEFT, RIGHT, UP, DOWN, STOP };

extern int screenWidth;
extern int screenHeight;


//������ ���Ḯ��Ʈ ���
typedef struct Node {
	//x��ǥ y��ǥ
	int sX, sY;
	int dircetion;
}Node;


//������
class Snake : public Monster  //������
{
private:
	//������ ��ǥ�� �����ϰ� ������Ʈ �� ���Ḯ��Ʈ
	list<Node*> snakeList;
    DIRECTION dSnake;
	int moveCounter;

public:
	Snake(int x, int y, int speed, double health, int attackPower, int tX, int tY);
	~Snake();
	virtual void Draw();
	virtual void GetAttackted(int damage);
	virtual void move(int newX, int newY);
	virtual void attackDamage(int attackPower);
	bool isNodeInList(int x, int y);

	//getter setter
	list<Node*> getSnakeList() {
		return snakeList;
	}
	DIRECTION getSnakeDirection() {
		return dSnake;
	}

};

//��ź
typedef struct bombAttack {
	int x;
	int y;
}bombAttack;

class Bomb : public Monster  
{
private:
	int checkCount;
	bombAttack bombRange[9];
public:
	Bomb(int x, int y, int speed, double health, int attackPower, int tX, int tY);
	~Bomb();
	virtual void Draw();
	virtual void GetAttackted(int damage);
	virtual void move(int newX, int newY);
	virtual void attackDamage(int attackPower);

	//getter setter
	int getCheckCount() {
		return checkCount;
	}
	void setCheckCount(int a) {
		this->checkCount = a;
	}

	bombAttack* getBombRange() {
		return bombRange;
	}
};



//��
class Bell : public bellAndRabbit
{
private:
    //�θ� ��ü�� �ִ� �ʵ常���� ���
public:
    Bell(int x, int y, int speed, double health);
    ~Bell();

    virtual void Draw();
    virtual void GetAttackted(int damage);
    virtual void move(int newX, int newY);
    virtual void spawn();
  
};

//��ġ
class Magpie : public Ally
{
private:
	int moveCounter;
	bool invincible;
	int lastDamageTime;
	int countBell;

public:
	Magpie(int x, int y, int speed, double health, int attackPower);
	virtual void Draw();
	virtual void GetAttackted(int damage);
	virtual void move(int newX, int newY);
	virtual void attackDamage(int attackPower);

	//�浹 ���� Ȯ��
	bool isCollidingSnake(Snake* snake);
	bool isCollidingBell(Bell* bell);
	bool isCollidingBomb(Bomb* bomb);

	bool getInvincible() {
		return invincible;
	}
	int getLastDamageTime() {
		return lastDamageTime;
	}
	int getCountBell() {
		return countBell;
	}

	void setInvincible(bool is) {
		invincible = is;
	}

	void setCountBell(int count) {
		countBell = count;
	}

  
};


