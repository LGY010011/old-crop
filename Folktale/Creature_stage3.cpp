#include "Creature_stage3.h"
#define SNAKESIZE 10

//������ �޼��� ���� -------------------------------------------------------------------------------
Snake::Snake(int x, int y, int speed, double health, int attackPower, int tX, int tY) : Monster(x, y, speed, health, attackPower, tX, tY){//init �Լ� -> �ʱⰪ ����
	//������ ��ǥ �ʱⰪ ���� 
	//�������� ���̴� �ϴ� 10���� ����
	int centerX = screenWidth / 2;
	int centerY = screenHeight / 2;
	for (int i = 0;i < SNAKESIZE;i++) {
		Node* n = new Node;
		n->sX=i+ centerX;
		n->sY = centerY;
		snakeList.push_back(n);
	}

}

void Snake::Draw() { //��� ���ϴ� �Լ���

}

void Snake::GetAttackted(int damage) { //�����غ��� �����̴� �������� �� ����
	//double hp = getHealth(); //���� Snake�� hp ��������
	//hp -= damage; 
	//if (hp < 0) //���� �׾����� 0���� ����
	//	hp = 0;
	//setHealth(hp); //hp���� damage ���� ������ �缳��
}

void Snake::move(int newX, int newY) { //newX�� newY�� ����Ȯ���� ���� �� 
	//front�� �� ��� �߰�
	Node* n = new Node;
	n->sX = newX;
	n->sY = newY;
	snakeList.push_front(n);
	//back���� ��� ����
	Node* lastNode = snakeList.back();
	delete lastNode;
	snakeList.pop_back();
}

void Snake::attackDamage(int attackPower) { 
	//�����̰� ��ġ���� ������ �ִ� �޼��� -> ��ġ�� attacked�޼���� ����
	//�� �޼���� isColliding�� true�� �� ȣ��

}


Snake::~Snake() {
	//snake �޸� ����
	while (!snakeList.empty()) {
		delete snakeList.back();
		snakeList.pop_back();
	}
}

//��ġ �޼��� ���� -----------------------------------------------------------------------------

Magpie::Magpie(int x, int y, int speed, double health, int attackPower) :Ally(x, y, speed, health, attackPower) {

}

bool Magpie::isCollidingSnake(Snake snake) { //�����̿��� �浹 ���� Ȯ��
	bool is = false; //�浹 �� ������ �ʱ�ȭ

	// snake�� ��� ��带 ���� Ȯ���ؾ� ��
	for (const auto& node : snake.getSnakeList()) {
		// ���� �ε������� true ��ȯ
		if ((node->sX == this->getX()) && (node->sY == this->getY())) {
			is = true;
			break;
		}
	}

	return is;
}

void Magpie::Draw() { //��� ���ϴ� �Լ���

}

void Magpie::GetAttackted(int damage) { 
	//��ġ ������ �ޱ� -> damage=������ attackPower��������
	double hp = getHealth(); //���� ��ġ�� hp ��������
	hp -= damage; 
	if (hp < 0) //���� �׾����� 0���� ����
		hp = 0;
	setHealth(hp); //hp���� damage ���� ������ �缳��
}

void Magpie::move(int newX, int newY) {
	//newX�� newY ���� Ȯ��
	if (newX > screenWidth)
		newX = screenWidth;
	else if (newX < 0)
		newX = 0;
	if (newY > screenHeight)
		newY = screenHeight;
	else if (newY < 0)
		newY = 0;

	this->setXY(newX, newY);
}

void Magpie::attackDamage(int attackPower) {
	
}