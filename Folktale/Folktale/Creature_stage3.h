#pragma once
#include "Creature.h"
#include <list>
#include <random>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
#include "STAGE3.h"
#define SNAKESIZE 15
#define GRID 40

using namespace std;

//ui 적용 시 값 얻어와서 할당하기
//여기서 정의한 전역 변수는 phase_stage3, main에서 사용 가능
enum DIRECTION { LEFT, RIGHT, UP, DOWN, STOP };



//구렁이 연결리스트 노드
typedef struct Node {
	//x좌표 y좌표
	int sX, sY;
	int dircetion;
}Node;


//구렁이
class Snake : public Monster  //구렁이
{
private:
	//구렁이 좌표를 저장하고 업데이트 할 연결리스트
	list<Node*> snakeList;
    DIRECTION dSnake;
	int moveCounter;
    int n; // n번의 게임 루프마다 한 번씩 움직이도록 변경

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
    int getN() {
        return n;
    }
    void setN(int n) {
        this->n = n;
    }

};

//폭탄
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



//종
class Bell : public bellAndRabbit
{
private:
    //부모 객체에 있는 필드만으로 사용
public:
    Bell(int x, int y, int speed, double health);
    ~Bell();

    virtual void Draw();
    virtual void GetAttackted(int damage);
    virtual void move(int newX, int newY);
    virtual void spawn();
  
};

//까치
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

	//충돌 여부 확인
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


