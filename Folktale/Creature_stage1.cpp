#include "Creature_stage1.h"
#include "Phase_stage1Game.h"


void Item::nextFrame() {
    currentTextureIndex = (currentTextureIndex + 1) % 10;
}

void Item::frameUpdate() {
    frameChangeCounter++;
    if (frameChangeCounter >= frameChangeFrequency) {
        nextFrame();
        frameChangeCounter = 0;
    }
}

void Item::createItem(int x, int y, int type) {
    // �������� �����ϴ� �ڵ�
    Item* item = new Item(x, y, type);
    items.push_back(item);
}
// #########Dandelion Ŭ������ �޼��� ����#########

void Dandelion::Draw() {
    // �ε鷹�� �׸��� �ڵ�

}

void Dandelion::GetAttackted(int damage) {
    // ���� �޾��� ���� ����
        //ü�� ����
    setHealth(getHealth() - damage);
    //ü���� 0���Ϸ� ��������
    if (getHealth() <= 0) {
        g_current_game_phase = PHASE_STAGE1_ENDING;

    }

}

void Dandelion::move(int newX, int newY) {
    // �̵��ϴ� �ڵ�
    //�׷��� �ε鷹�� �������� �����Ƿ� SKIP
}


// #########DogPoop Ŭ������ �޼��� ����#########
void DogPoop::Draw() {
    // ���������� �׸��� �ڵ� 
}

void DogPoop::GetAttackted(int damage) {
    // ���� �޾��� ���� ����
    //ü�� ����
    setHealth(getHealth() - damage);

}
/*
void DogPoop::updateItems(std::vector<Item*>& items) {
    for (int i = 0; i < items.size(); ++i) {
        Item* item = items[i];

        if (item->getX() == getX() && item->getY() == getY()) {
            if (item->getType() == 1) {
                //1���̸� ���� ������
                setHealth(getHealth() + 10);
            }
            else if (item->getType() == 2) {
                //2���̸� ��Ÿ�� ����
                FIRE_COOLDOWN -= 100;
            }
            else if (item->getType() == 3) {
                //3���̸� �̵��ӵ� ���� ������
                setSpeed(getSpeed() + 1);
            }
            else if (item->getType() == 4) {
                //4���̸� �� ����
                is_rock = true;
            }
            delete item;
            items.erase(items.begin() + i);
            --i;
        }
    }
}*/
void DogPoop::throwProjectile(int dx, int dy) {
    Projectile* projectile = new Projectile(getX(), getY(), dx, dy, projectileSpeed);
    projectiles.push_back(projectile);
}

void DogPoop::setProjectileSpeed(int projectileSpeed)
{
    this->projectileSpeed = projectileSpeed;
}

void DogPoop::setProjectileDamage(int projectileDamage)
{
    this->projectileDamage = projectileDamage;
}

void DogPoop::updateProjectiles(std::vector<Monster*>& monsters)
{
    for (int i = 0; i < projectiles.size(); ++i) {
        Projectile* projectile = projectiles[i];

        // ����ü�� �̵���Ų��.
        projectile->move(projectileSpeed);

        // ����ü�� ȭ�� ������ �������� Ȯ���Ѵ�.
        if (projectile->getX() < 0 || projectile->getX() > SCREEN_WIDTH ||
            projectile->getY() < 0 || projectile->getY() > SCREEN_HEIGHT) {
            // ����ü�� �����Ѵ�.
            delete projectile;
            projectiles.erase(projectiles.begin() + i);
            --i;
            continue;
        }

        for (size_t j = 0; j < monsters.size(); ++j) {
            Monster* monster = monsters[j];
            if (monster == nullptr) continue;
            int dx = projectile->getX() - monster->getX();
            int dy = projectile->getY() - monster->getY();
            if (dx * dx + dy * dy < COLLISION_DISTANCE * COLLISION_DISTANCE) {
                // ���� ü���� ���ҽ�Ų��.
                monster->GetAttackted(projectileDamage);

                // ü���� 0 ������ ��� ���� �����Ѵ�.
                if (monster->getHealth() <= 0) {
                    delete monster;
                    monsters.erase(monsters.begin() + j);
                    delete projectile;
                    projectiles.erase(projectiles.begin() + i);
                    killcount++;
                    --i;
                    break;
                }
                // ����ü�� �����Ѵ�.
                delete projectile;
                projectiles.erase(projectiles.begin() + i);
                --i;

                break;
            }
        }
    }

}

void DogPoop::moveProjectiles() {
    for (Projectile* projectile : projectiles) {
        projectile->move(projectileSpeed);
    }
}

void DogPoop::move(int newX, int newY) {
    // �̵��ϴ� �ڵ�
    float speed = getSpeed();
    if (newX != 0 && newY != 0) {
        speed /= sqrt(2.0f);
    }
    setX(getX() + newX * speed);
    setY(getY() + newY * speed);
    currentTextureIndex = (currentTextureIndex + 1) % 4;  // 4�� �ִϸ��̼� �������� ��

}

void DogPoop::setInvincible(bool invincible) {
    isInvincible = invincible;
}

bool DogPoop::getInvincible() const {
    return isInvincible;
}
// #########Chick Ŭ������ �޼��� ����#########
void Chick::Draw() {
    // ���Ƹ��� �׸��� �ڵ� SKIP
}

void Chick::GetAttackted(int damage) {
    // ���� �޾��� ���� ����
    setHealth(getHealth() - damage);

}


void Chick::move(int newX, int newY) {
    // �̵��ϴ� �ڵ� (���ΰ��� ���� �ٰ����� ����)

    if (getX() < getTargetX()) {
        setX(getX() + getSpeed());
    }
    else if (getX() > getTargetX()) {
        setX(getX() - getSpeed());
    }

    if (getY() < getTargetY()) {
        setY(getY() + getSpeed());
    }
    else if (getY() > getTargetY()) {
        setY(getY() - getSpeed());
    }

}

int DogPoop::getCurrentFrameIndex() const {
    return currentTextureIndex;
}
void Chick::attackDamage(int attackPower) {
    // �����ϴ� �ڵ� (���ΰ��� �����ϴ� ����)
    if (target != nullptr) {
        target->GetAttackted(attackPower);
    }

}
void Chick::setTarget(DogPoop* newTarget) {
    target = newTarget;
}

// #########Sparrow Ŭ������ �޼��� ����#########
void Sparrow::Draw() {
    // ������ �׸��� �ڵ�
}

void Sparrow::GetAttackted(int damage) {
    // ���� �޾��� ���� ����
        //ü�� ����
    setHealth(getHealth() - damage);
}

void Sparrow::move(int newX, int newY) {
    // �̵��ϴ� �ڵ� (���ΰ��� ���� �ٰ����� ����)

    if (getX() < getTargetX()) {
        setX(getX() + getSpeed());
    }
    else if (getX() > getTargetX()) {
        setX(getX() - getSpeed());
    }

    if (getY() < getTargetY()) {
        setY(getY() + getSpeed());
    }
    else if (getY() > getTargetY()) {
        setY(getY() - getSpeed());
    }
}
void Sparrow::setTarget(Dandelion* newTarget) {
    target = newTarget;
}

void Sparrow::attackDamage(int attackPower) {
    // �����ϴ� �ڵ� (���ΰ��� �����ϴ� ����)
}

