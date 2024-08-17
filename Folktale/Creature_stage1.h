#pragma once
#include "Creature.h"
#include <vector>


class Item {
private:
    int x, y;  // �������� ��ġ
    int type;  // �������� ����
    int currentTextureIndex = 0;  // ���� �̹����� �ε���
    int frameChangeCounter = 0; // ������ ���� ī����
    static const int frameChangeFrequency = 5; // ������ ���� ��
public:
    std::vector<Item*> items;
    Item(int x, int y, int type) : x(x), y(y), type(type) {}
    int getX() const { return x; }
    int getY() const { return y; }
    int getType() const { return type; }
    void createItem(int x, int y, int type);
    int getCurrentFrameIndex() { return currentTextureIndex; }
    void nextFrame();
    void frameUpdate();
};
class Projectile {
private:
    int x, y;  // ����ü�� ��ġ
    int dx, dy;  // ����ü�� �̵� ����
    int speed; // ����ü�� �̵� �ӵ�

public:
    Projectile(int x, int y, int dx, int dy, int speed)
        : x(x), y(y), dx(dx), dy(dy) {}

    void move(int projectileSpeed) {
        float speed = projectileSpeed;
        if (dx != 0 && dy != 0) { // �밢�� �̵��� ���
            speed /= sqrt(2.0f);
        }
        x += dx * speed;
        y += dy * speed;
    }

    int getX() const { return x; }
    int getY() const { return y; }
};

//�ε鷹
class Dandelion : public Ally {
public:
    Dandelion(int x, int y, int speed, double health, int attackPower) : Ally(x, y, speed, health, attackPower) {}

    void Draw();

    void GetAttackted(int damage);

    void move(int newX, int newY);
};

//��������
class DogPoop :public Ally
{
private:
    int projectileSpeed; // ����ü �ӵ�
    int projectileDamage; // ����ü ���ݷ�
    int currentTextureIndex;  // ���� �̹����� �ε���
    bool isInvincible; // ���� �������� ����
    int killcount;

public:
    std::vector<Projectile*> projectiles;
    DogPoop(int x, int y, int speed, double health, int attackPower, int projectileSpeed, int projectileDamage, int killcount)
        : Ally(x, y, speed, health, attackPower), projectileSpeed(projectileSpeed), projectileDamage(projectileDamage) {}
    void throwProjectile(int dx, int dy);
    void moveProjectiles();
    void setProjectileSpeed(int projectileSpeed);
    void setProjectileDamage(int projectileDamage);
    void updateProjectiles(std::vector<Monster*>& monsters);
    //void updateItems(std::vector<Item*>& items);
    void Draw();
    void GetAttackted(int damage);
    void move(int newX, int newY);
    void attackDamage(int attackPower);
    //�ִϸ��̼� �ε�����ȯ
    int getCurrentFrameIndex() const;
    //���� ���� ���ͼ���
    void setInvincible(bool invincible);
    bool getInvincible() const;
    //ųī��Ʈ ���� ���ͼ���
    void setKillcount(int killcount);
    int getKillcount() { return killcount; };
};

//���Ƹ�
class Chick : public Monster {
private:
    int attack_damage;

public:
    DogPoop* target;
    Chick(int x, int y, int speed, double health, int attackPower, int targetX, int targetY)
        : Monster(x, y, speed, health, attackPower, targetX, targetY) {}

    void Draw();
    void GetAttackted(int damage);
    int getAttackDamage() { return attack_damage; }
    void move(int newX, int newY);
    void attackDamage(int attackPower);
    void setTarget(DogPoop* newTarget);
    void toTarget();

};

//����
class Sparrow : public Monster {
private:
    int attack_damage;

public:
    Dandelion* target;
    Sparrow(int x, int y, int speed, double health, int attackPower, int targetX, int targetY)
        : Monster(x, y, speed, health, attackPower, targetX, targetY) {}

    void Draw();
    void GetAttackted(int damage);
    int getAttackDamage() { return attack_damage; }
    void move(int newX, int newY);
    void setTarget(Dandelion* newTarget);
    void attackDamage(int attackPower);
    void toTarget();


};

//attackDamage �� ��