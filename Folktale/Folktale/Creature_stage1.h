#pragma once
#include "Creature.h"

//�ε鷹
class Dandelion :public Ally
{
private:

public:
};

//��������
class DogPoop :public Ally
{
private:

public:
	DogPoop(int _health, int _x, int _y);

};

//���Ƹ�
class Chick : public Monster
{
	// hp, attck_damage, (x,y), speed, (fx,fy),spon()  -  Ÿ����ǥ(0)
private:
	int attack_damage;

public:

};

//����
class Sparrow : public Monster
{
private:
	int attack_damage;

public:

};