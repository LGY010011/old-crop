#pragma once
#include "Creature.h"

//민들레
class Dandelion :public Ally
{
private:

public:
};

//강아지똥
class DogPoop :public Ally
{
private:

public:
	DogPoop(int _health, int _x, int _y);

};

//병아리
class Chick : public Monster
{
	// hp, attck_damage, (x,y), speed, (fx,fy),spon()  -  타겟좌표(0)
private:
	int attack_damage;

public:

};

//참새
class Sparrow : public Monster
{
private:
	int attack_damage;

public:

};