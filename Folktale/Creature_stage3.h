#pragma once
#include "Creature.h"
#include <list>
#include <random>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
#include "STAGE.h"
#define SNAKESIZE 15
#define GRID_STAGE3 40

using namespace std;

//ui ���� �� �� ���ͼ� �Ҵ��ϱ�




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
    int n; // n���� ���� �������� �� ���� �����̵��� ����

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
    int startCount;
    int middleCount;
    int lastCount;
    int type;
public:
    Bomb(int x, int y, int speed, double health, int attackPower, int tX, int tY, int startCount, int middleCount, int lastCount, int type);
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

    int getStartCount() {
        return startCount;
    }
    int getMiddleCount() {
        return middleCount;
    }
    int getLastCount() {
        return lastCount;
    }
    int getType() {
        return type;
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
    int lastEatenTime; //���������� ���� �ð�
public:
    Bell(int x, int y, int speed, double health);
    ~Bell();

    virtual void Draw();
    virtual void GetAttackted(int damage);
    virtual void move(int newX, int newY);
    virtual void spawn();

    //getter setter
    int getLastEatenTime() {
        return lastEatenTime;
    }
    void setLastEatenTime(int time) {
        lastEatenTime = time;
    }
};

//��ġ
class Magpie : public Ally
{
private:
    int moveCounter;
    bool invincible;
    int lastDamageTime;
    int countBell;

    Mix_Chunk* hit_sound = Mix_LoadWAV("../../Resources/hit.wav");


public:
    Magpie(int x, int y, int speed, double health, int attackPower);
    ~Magpie() {
        Mix_FreeChunk(hit_sound);
    }
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


