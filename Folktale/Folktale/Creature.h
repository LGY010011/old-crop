#pragma once

class Creature // 최상위
{
private: //부모의 private 필드는 자식 클래스에서 접근 불가 -> 메서드를 통해 업데이트하고 초기화하고 읽어와야 함;;
	int pos_x, pos_y;
	int speed;
	double health;
	
public:
	Creature(int x, int y, int speed, double health) {
		//자식 클래스는 init 함수 호출시 이거 먼저 호출해서 좌표 할당하기! -> 객프설에서 배운 거니까 모르겠다고 하면 슬퍼잉
		pos_x = x;
		pos_y = y;
		this->speed = speed;
		this->health = health;
	}
	//setter들
	void setXY(int x, int y) { //좌표 업데이트 메서드
		pos_x = x;
		pos_y = y;
	}
	void setSpeed(int speed) { //스피드 업데이트 => speed 조절하는 객체 없으면 나중에 삭제합디다
		this->speed = speed;
	}
	void setHealth(int health) { //HP 업데이트 메서드
		this->health = health;
	}
	//getter -> 일단 health랑 x,y 해놓음
	double getHealth() {
		return health;
	}
	int getX() {
		return pos_x;
	}
	int getY() {
		return pos_y;
	}
	int getSpeed() {
		return speed;
	}

	virtual void Draw() = 0;
	virtual void GetAttackted(int damage) = 0;
	virtual void move(int newX, int newY) = 0;
	
};

//거북이 강아지똥 민들레 까치
class Ally : public Creature
{
private:
	int attackPower;
public:
	Ally(int x, int y, int speed, double health, int attackPower) : Creature(x, y, speed, health) {
		this->attackPower = attackPower;
	}
};

//병아리 참새 구렁이
class Monster : public Creature
{
private:
	int attackPower;
	int target_x, target_y;

public:
	Monster(int x, int y, int speed, double health, int attackPower, int tX, int tY) : Creature(x, y, speed, health){
		this->attackPower = attackPower;
		this->target_x = tX;
		this->target_y = tY;
	}

	void setTargetXY(int x, int y) { //타겟 좌표 setter
		this->target_x = x;
		this->target_y = y;
	}
	int getTargetX() { //타겟 x좌표 getter
		return this->target_x;
	}
	int getTargetY() { //타겟 y좌표 getter
		return this->target_y;
	}
	int getAttackPower() {
		return this->attackPower;
	}

	virtual void attackDamage(int attackPower)=0;
	
};


//종, 토끼
class bellAndRabbit : public Creature
{
private:
	bool isFace;
	int count;
public:
    bellAndRabbit(int x, int y, int speed, double health) : Creature(x, y, speed, health) {
        isFace = false;
        count = 0;
    }
    //setter
    void setIsFace(bool isFace) {
        this->isFace = isFace;
    }
    void setCount(int count) {
        this->count = count;
    }
    //getter
    bool getIsFace() {
        return this->isFace;
    }
    int getCount() {
        return this->count;
    }

	virtual void spawn() = 0;
	//얘네는 무브 스루하기
};
