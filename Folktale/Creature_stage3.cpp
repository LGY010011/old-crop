#include "Creature_stage3.h"
#include <random>


//������ �޼��� ���� -------------------------------------------------------------------------------
Snake::Snake(int x, int y, int speed, double health, int attackPower, int tX, int tY) : Monster(x, y, speed, health, attackPower, tX, tY) {//init �Լ� -> �ʱⰪ ����
    //������ ��ǥ �ʱⰪ ���� 
    //�������� ���̴� �ϴ� 10���� ����
    //ó�� �����̴� ȭ���� �߾ӿ� ��ġ
    int centerX = (screenWidth / GRID_STAGE3) / 2 - 1;
    int centerY = (screenHeight / GRID_STAGE3) / 2 - 1;
    for (int i = 0; i < SNAKESIZE - 1; i++) {
        Node* n = new Node;
        n->sX = i + centerX;
        n->sY = centerY;
        n->dircetion = LEFT;
        snakeList.push_back(n);
    }
    dSnake = LEFT; //������ ó�� ��� ������ LEFT�� ����

    moveCounter = 0;
    n = 8;
}

void Snake::Draw() { //��� ���ϴ� �Լ���

}

void Snake::GetAttackted(int damage) { //�����غ��� �����̴� �������� �� ����

}

bool Snake::isNodeInList(int x, int y) {
    for (const auto& node : snakeList) {
        if (node->sX == x && node->sY == y) {//��ġ�ϴ� ��尡 ������ true ��ȯ
            return true;
        }
    }
    return false;
}

void Snake::move(int magpieX, int magpieY) { //newX�� newY�� ������� ����
    //snake�� �����ϰ� ������ => �� �Լ� �ȿ��� ��ǥ ���ŵǵ��� �����ϱ�
    //��, ��, ��, �Ʒ� �� �ϳ��� �����ϰ� ����
    //switch������ ��ǥ ����
    moveCounter++;
    if (moveCounter < n) { // 5���� ���� �������� �� ���� �����̵��� ����
        return;
    }
    moveCounter = 0; // ī���� �ʱ�ȭ

    Node* head = new Node;

    //�� ��ǥ ���

    int sx = snakeList.front()->sX;
    int sy = snakeList.front()->sY;

    int newHeadX = sx;
    int newHeadY = sy;


    // ��ġ�� ���󰡴� ����
    if (magpieX > sx) {
        dSnake = RIGHT;
        newHeadX = sx + 1;
    }
    else if (magpieX < sx) {
        dSnake = LEFT;
        newHeadX = sx - 1;
    }
    else if (magpieY > sy) {
        dSnake = DOWN;
        newHeadY = sy + 1;
    }
    else if (magpieY < sy) {
        dSnake = UP;
        newHeadY = sy - 1;
    }

    // �� ���� ����
    if (newHeadX < 1 || newHeadX >= screenWidth / GRID_STAGE3 - 1 //�� �ʺ� ����
        || newHeadY < 1 || newHeadY >= screenHeight / GRID_STAGE3 - 1 || isNodeInList(newHeadX, newHeadY))//�� ���� ����)
    {
        if (dSnake == RIGHT || dSnake == LEFT) {
            newHeadX = sx;
            newHeadY = (newHeadY + 1) % (screenHeight / GRID_STAGE3);
            dSnake = (dSnake == RIGHT) ? UP : DOWN; // ���� ����

        }
        else {
            newHeadY = sy;
            newHeadX = (newHeadX + 1) % (screenWidth / GRID_STAGE3);
            dSnake = (dSnake == UP) ? LEFT : RIGHT; // ���� ����
        }
    }




    //front�� �� ��� �߰�;
    head->sX = newHeadX;
    head->sY = newHeadY;
    head->dircetion = dSnake;
    snakeList.push_front(head);
    //back���� ��� ����
    Node* tail = snakeList.back();
    delete tail;
    snakeList.pop_back();
}

void Snake::attackDamage(int attackPower) {
    //�����̰� ��ġ���� ������ �ִ� �޼��� -> ��ġ�� attacked�޼���� ����

}


Snake::~Snake() {
    //snake �޸� ����
    while (!snakeList.empty()) {
        delete snakeList.front();
        snakeList.pop_front();
    }
}

//��ź �޼��� ���� --------------------------------------------------------------------------------------
//������ �޼��� ���� -------------------------------------------------------------------------------
Bomb::Bomb(int x, int y, int speed, double health, int attackPower, int tX, int tY, int startCount, int middleCount, int lastCount, int type) : Monster(x, y, speed, health, attackPower, tX, tY) {//init �Լ� -> �ʱⰪ ����
    //cout << "bomb init" << endl;
    //checkCount�� 6�� �Ǵ� ���� !�� ����ϰ� �浹���� Ȯ�� �� ���� 
    //checkCount�� 0�� �Ǵ� �������� �����Ÿ����� -> 0���� 5���� �ʿ��ѵ� ¦���� ��� Ȧ���� �����? ���
    checkCount = -20;
    this->startCount = startCount;
    this->middleCount = middleCount;
    this->lastCount = lastCount;

    this->type = type;
    //������ ���� ����
    int k_y = -1;
    int k_x = -1;
    for (int i = 1; i <= 9; i++) {

        bombRange[i - 1].x = x + k_x;
        bombRange[i - 1].y = y + k_y;

        k_y += 1;

        if (i % 3 == 0) {
            k_y = -1;
            k_x += 1;
        }
    }

}

void Bomb::Draw() { //��� ���ϴ� �Լ���

}

void Bomb::GetAttackted(int damage) { //�����غ��� �����̴� �������� �� ����

}


void Bomb::move(int newX, int newY) {
    if (checkCount < 0) { //���� 0���� ���� ��� ��ġ�� ��ġ���� �����ͼ� ���� ��ǥ�� �Ҵ��Ѵ�
        this->setXY(newX, newY);

        int k_y = -1;
        int k_x = -1;
        for (int i = 1; i <= 9; i++) {
            bombRange[i - 1].x = newX + k_x;
            bombRange[i - 1].y = newY + k_y;

            k_y += 1;

            if (i % 3 == 0) {
                k_y = -1;
                k_x += 1;
            }
        }

    }
}


void Bomb::attackDamage(int attackPower) {

}


Bomb::~Bomb() {

}

//��ġ �޼��� ���� -----------------------------------------------------------------------------

Magpie::Magpie(int x, int y, int speed, double health, int attackPower) :Ally(x, y, speed, health, attackPower) {
    moveCounter = 0;
    invincible = false;
    countBell = 0;
    lastDamageTime = 0;
    Mix_VolumeChunk(hit_sound, 100);
}

void Magpie::Draw() { //��� ���ϴ� �Լ���

}

void Magpie::GetAttackted(int damage) {
    //��ġ ������ �ޱ� -> damage=������ attackPower��������
    if (invincible) return; // ���� ������ ���
    Mix_PlayChannel(-1, hit_sound, 0);
    double hp = getHealth(); //���� ��ġ�� hp ��������
    hp -= damage;
    if (hp < 0) //���� �׾����� 0���� ����
        hp = 0;
    setHealth(hp); //hp���� damage ���� ������ �缳��

    invincible = true; // �������� ���� �� ���� ���·� ��ȯ
    lastDamageTime = SDL_GetTicks(); // �������� ���� 
}

void Magpie::move(int newX, int newY) {
    //newX�� newY ���� Ȯ���� �ܺο��� �ϰ� �ѱ�� -> �ڵ� �ߺ���
    static int moveCounter = 0;
    moveCounter++;

    if (moveCounter % 5 == 0) { // 5���� ȣ�⸶�� �� ���� �̵�
        this->setXY(newX, newY);
    }

}

void Magpie::attackDamage(int attackPower) {

}

bool Magpie::isCollidingSnake(Snake* snake) { //�����̿��� �浹 ���� Ȯ�� => �̰� Ʈ��� magpie.attacked�Լ� ȣ��

    bool is = false; //�浹 �� ������ �ʱ�ȭ

    // snake�� ��� ��带 ���� Ȯ���ؾ� ��
    for (const auto& node : snake->getSnakeList()) {
        // ���� �ε������� true ��ȯ
        if ((node->sX == this->getX()) && (node->sY == this->getY())) {
            is = true;
            break;
        }
    }

    return is;
}

bool Magpie::isCollidingBell(Bell* bell) {
    bool is = false; //�浹 �� ������ �ʱ�ȭ

    if ((this->getX() == bell->getX()) && (this->getY() == bell->getY())) {//�浹����
        is = true;
        bell->setIsFace(!bell->getIsFace()); // setIsFace �޼��� ȣ��
        bell->setLastEatenTime(SDL_GetTicks()); // ���������� ���� �ð� ����
        bell->setXY(0, 0); //ȭ�鿡�� ��������� ����
    }

    return is;
}

bool Magpie::isCollidingBomb(Bomb* bomb) {

    bool is = false; //�浹 �� ������ �ʱ�ȭ

    int x = this->getX();
    int y = this->getY();

    bombAttack* b = bomb->getBombRange();
    for (int i = 0; i < 9; i++) {
        // ���� �ε������� true ��ȯ
        if ((b[i].x == x) && (b[i].y == y)) {
            is = true;
            break;
        }
    }

    return is;
}


//�� ������ -----------------------------------------------------------------------------

Bell::Bell(int x, int y, int speed, double health) : bellAndRabbit(x, y, speed, health) {
    lastEatenTime = 0;
}

void Bell::Draw() {

}
void Bell::GetAttackted(int damage) {
    //Bell�� ������ �� ����
}
void Bell::move(int newX, int newY) {
    //Bell�� ��ǥ�� �������� ����
}
void Bell::spawn() {
    uniform_int_distribution<int> distributionX(1, screenWidth / GRID_STAGE3 - 2);
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID_STAGE3 - 2);

    if (this->getIsFace()) { //���� ��ġ�� �����ٸ�
        //���� �ѹ��� ȭ�鿡 �Ѹ��Ÿ� �ܺο��� Bell ��ü �迭�� ����°� �� ȿ����
        //���� �ϳ� ���� ������ �����ϰ� �Ѹ� �Ÿ� �� ������� ���

        this->setIsFace(!this->getIsFace()); //������ �� �� �����ٰ� ����

        //��ǥ ���� -> �����ϰ�
        this->setXY(distributionX(generator), distributionY(generator));
    }
}


Bell::~Bell() {

}