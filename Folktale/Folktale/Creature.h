#pragma once

class Creature // �ֻ���
{
private:
	int pos_x, pos_y;
	int speed;
	double health;
public:
	virtual void Draw() = 0;
	virtual void GetAttackted(int damage) = 0;
	virtual void move(int newX, int newY) = 0;
};

//�ź��� �������� �ε鷹 ��ġ
class Ally : public Creature
{
private:
	int attackPower;
public:

};

//���Ƹ� ���� ������
class Monster : public Creature
{
private:
	int attackPower;
	int target_x, target_y;

public:
	void attackDamage(int attackPower);
	virtual void update_targetXY() = 0;
};

//��, �䳢
class bellAndRabbit : public Creature
{
private:
	bool isFace = false;
	int count = 0;
public:
	virtual void spawn() = 0;
	//��״� ���� �����ϱ�
};
