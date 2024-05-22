#include "Phase_stage3.h"
#include <Windows.h>
#include <iomanip>

extern default_random_engine generator;

Stage3::Stage3() {
    //1. ��ü ����
    //a. �� ����
    uniform_int_distribution<int> distributionX(0, screenWidth/GRID-1);
    uniform_int_distribution<int> distributionY(1, screenHeight/GRID-1);


    bell = new Bell(distributionX(generator), distributionY(generator), 0, 0);
    //b. ��ġ ����
    magpie = new Magpie(0, 0, 0.5, 50,0); //(0,0)���� ����, speed�� 1,hp�� 100���� ����
    //c. ������ ����
    snake = new Snake(0, 0, 1, 100, 10, magpie->getX(),magpie->getY());
    //d. ��ź ����
    bomb = new Bomb(0, 0, 1, 100, 5, magpie->getX(), magpie->getY());

    ////2. �ؽ��� ��������
    //a. �� �ؽ���
    SDL_Surface* temp_sheet_surface = IMG_Load("../../Resource/bell.png");
    bell_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�
    bell_destination_rect.x = bell->getX();
    bell_destination_rect.y = bell->getY();
    bell_destination_rect.w = GRID;
    bell_destination_rect.h = GRID;

    //b. ��ġ �ؽ���
    temp_sheet_surface = IMG_Load("../../Resource/magpie.png");
    magpie_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�
    magpie_destination_rect.x = magpie->getX()*GRID;
    magpie_destination_rect.y = magpie->getY()*GRID;
    magpie_destination_rect.w = GRID;
    magpie_destination_rect.h = GRID;

    
    //c. ������ �ؽ���
    temp_sheet_surface = IMG_Load("../../Resource/snakeHead.png");;
    snakeHead_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�
    snake_destination_rect.x = snake->getSnakeList().front()->sX;
    snake_destination_rect.y = snake->getSnakeList().front()->sY;
    snake_destination_rect.w = GRID;
    snake_destination_rect.h = GRID;

    temp_sheet_surface = IMG_Load("../../Resource/snakeBody.png");
    snakeBody_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�
    temp_sheet_surface = IMG_Load("../../Resource/snakeTail.png");
    snakeTail_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    temp_sheet_surface = IMG_Load("../../Resource/snakeCurve.png");
    snakeCurve_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);

    //��ź �ؽ��� 
    temp_sheet_surface  = IMG_Load("../../Resource/bombAfter.png");
    bombAfter_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    //d. ��� �ؽ���
    temp_sheet_surface = IMG_Load("../../Resource/background.png");
    bg_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�
    bg_destination_rect.x = 0;
    bg_destination_rect.y = GRID;
    bg_destination_rect.w = screenWidth;
    bg_destination_rect.h = screenHeight;


    //��Ʈ �ؽ�ó
    temp_sheet_surface = IMG_Load("../../Resource/heartZero.png");
    heartZero_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    temp_sheet_surface = IMG_Load("../../Resource/heartHalf.png");
    heartHalf_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    temp_sheet_surface = IMG_Load("../../Resource/heartOne.png");
    heartOne_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//���� �ʼ�

    heart_destination_rect.w = GRID;
    heart_destination_rect.h = GRID;

    //2. ��Ÿ ����
    f_state = STOP;//����Ű �� ����
    stop = true; //���� ��Ȳ���� �ʱ�ȭ
    //��� �� ���� ������ �ʱ�ȭ -> stop
    for (int i = 0; i < f_state; i++) {//0�� ����, ...
        f_list[i] = false;
    }
    game_result = 0;//1-> �¸�, 2-> �й�

    flip = SDL_FLIP_HORIZONTAL;
}


void Stage3::HandleEvents() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:

            if (event.key.keysym.sym == SDLK_LEFT) {
                f_state = LEFT; //���� ���� ���� LEFT
                f_list[f_state] = true;
                stop = false;

            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                f_state = RIGHT;
                f_list[f_state] = true;
                stop = false;

            }
            else if (event.key.keysym.sym == SDLK_UP) {
                f_state =UP;
                f_list[f_state] = true;
                stop = false;

            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                f_state = DOWN;
                f_list[f_state] = true;
                stop = false;

            }
            break;
        case SDL_KEYUP:

            if (event.key.keysym.sym == SDLK_LEFT) {
                f_list[0] = false;

            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                f_list[1] = false;

            }
            else if (event.key.keysym.sym == SDLK_UP) {
                f_list[2] = false;

            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                f_list[3] = false;

            }

            //���� up���� ���� ����� �ִٸ�
            if (f_list[0])
                f_state = 0;
            if (f_list[1])
                f_state = 1;
            if (f_list[2])
                f_state = 2;
            if (f_list[3])
                f_state = 3;

            if (f_list[0] != true && f_list[1] != true && f_list[2] != true && f_list[3] != true)
                stop = true;

            break;

        }
    }
}
void Stage3::Update() {
    //1. ��ġ
    //1.1 ��ġ ��ǥ ������Ʈ
    int x = magpie->getX();
    int y = magpie->getY();
    if (!stop) { //������ �ƴ϶�� ��ġ �̵�
        if (f_state == 0) { //�����̵�
            x -= 1;
            flip = SDL_FLIP_NONE;
        }
        else if (f_state == 1) {//�����̵�
            x += 1;
            flip = SDL_FLIP_HORIZONTAL;
        }
        else if (f_state == 2) {//���� �̵�
            y -= 1;
        }
        else if (f_state == 3) {//�Ʒ��� �̵�
            y += 1;
        }

    }

    //1.2 ��ġ ��ǥ ����
    if (x > screenWidth/GRID-1) { 
        x = screenWidth / GRID - 1;
    }
    else if (x < 0) {
        x = 0;
    }
    if (y > screenHeight/ GRID - 1) {
        y = screenHeight / GRID - 1;
    }
    else if (y < 1) {
        y = 1;
    }
    //1.3 ��ġ �̵�
    magpie->move(x, y);   
    //1.4 ��ġ ���� �ð� ������Ʈ
    if (magpie->getInvincible() && SDL_GetTicks() - magpie->getLastDamageTime() >= 3000) {
        magpie->setInvincible(false);
    }
    

    //2. ������ ������Ʈ
    snake->move(magpie->getX(), magpie->getY());

    //3. ��ź ������Ʈ
    if(bomb->getCheckCount()>=70)
        bomb->setCheckCount(-20); //�缳��
    bomb->setCheckCount(bomb->getCheckCount() + 1); //ī��Ʈ ���� ����
    bomb->move(magpie->getX(), magpie->getY()); //Ÿ�� ��ǥ ���� -> 0 ������ ���� �� �����


    //3. �浹 Ȯ��
    //3.1 �� ���� Ȯ��
    if (magpie->isCollidingBell(bell)) {//bell�̶� �ε����ٸ�
        bell->setCount(bell->getCount() + 1); //count���� �ϳ� ����
        bell->spawn();//�� ��ġ ����
    }


    //3.2 ������ �浹 Ȯ��
    if (magpie->isCollidingSnake(snake)) { //snake�� �ε����ٸ� hp ����
        magpie->GetAttackted(snake->getAttackPower());//������ ����
        cout << magpie->getHealth() << endl;
    }
    

    //3.3 ��ź �浹 Ȯ��
    if (bomb->getCheckCount() >= 50 && bomb->getCheckCount() < 70){
        if (magpie->isCollidingBomb(bomb)) {
            magpie->GetAttackted(bomb->getAttackPower());
            cout << magpie->getHealth() << endl;
        }

    }


    //4. ���� ���� Ȯ��
    if (bell->getCount() == 5) {//�� 5�� ������� 
        game_result = 1; //�¸�
    }

    if (magpie->getHealth() <= 0) {
        game_result = 2; //����
    }
}
void Stage3::Render() {

    //// 1. ��� �׸���.
    // 1.1. Ŀ���� �ܼ� ȭ���� ���� �� �𼭸� �κ����� �ű��. ��ǥ(0, 0)
    // <windows.h>���� �����ϴ� �Լ��� ����Ѵ�
    //// 1.2. ��� �׸���
    SDL_RenderClear(g_renderer); //�������� �ʱ�ȭ
    SDL_RenderCopy(g_renderer, bg_texture, NULL, &bg_destination_rect);


    //// 2. ĳ���� �׸���.
    // �� �׸���
    bell_destination_rect.x = bell->getX()*GRID; //�׷��� ��ǥ ����
    bell_destination_rect.y = bell->getY()*GRID;
    SDL_RenderCopy(g_renderer, bell_texture, NULL, &bell_destination_rect);
    
    // ��ź �׸���
    int b_count = bomb->getCheckCount();

    //ī��Ʈ�� 50���� �۰� 0 �̻��ε� ¦���� ? ���
    if (b_count < 50 && b_count >= 0) {
        if (b_count % 2 == 0) {
            heart_destination_rect.x = bomb->getBombRange()[4].x * GRID;
            heart_destination_rect.y = bomb->getBombRange()[4].y * GRID;
            SDL_SetTextureColorMod(bell_texture, 200, 50, 50);
            SDL_RenderCopy(g_renderer, bell_texture, NULL, &heart_destination_rect);
            SDL_SetTextureColorMod(bell_texture, 255, 255, 255);
        }
    }

    //ī��Ʈ�� 100���� 150 ���̸� !���
    else if (b_count >= 50 && b_count < 70) {
        bombAttack* b = bomb->getBombRange();
        for (int i = 0;i < 9;i++) {//������ ���� ���
            if (b[i].x >= screenWidth / GRID || b[i].x < 0 || b[i].y >= screenHeight / GRID || b[i].y < 1)
                continue;

            heart_destination_rect.x = b[i].x * GRID;
            heart_destination_rect.y = b[i].y * GRID;
            if (i == 4) {
                SDL_SetTextureColorMod(bell_texture, 255, 0, 0);
                SDL_RenderCopy(g_renderer, bell_texture, NULL, &heart_destination_rect);
                SDL_SetTextureColorMod(bell_texture, 255, 255, 255);
                continue;
            }
            SDL_RenderCopy(g_renderer, bombAfter_texture, NULL, &heart_destination_rect);
        }
    }


    // ������ �׸���
    auto snakeList = snake->getSnakeList();
    auto last = --snakeList.end();
    int angle = 0;
    int angle2 = 0;
    int checkPrevDirection = LEFT;
    int flag = false;
    for (auto it = snakeList.begin(); it != snakeList.end(); ++it) {
        snake_destination_rect.x = (*it)->sX*GRID; // �׷��� ��ǥ ����
        snake_destination_rect.y = (*it)->sY*GRID;

        //���� ����
        switch ((*it)->dircetion) {
        case LEFT://��
            angle = -90;
            break;
        case RIGHT://��
            angle = 90;
            break;
        case UP://��
            angle = -0;

            break;
        case DOWN://�Ʒ�
            angle = 180;
            
            break;
        default:
            break;
        }

        //���̴� �� �˻�
        if (((*it)->dircetion == RIGHT &&checkPrevDirection==DOWN) || ((*it)->dircetion == UP && checkPrevDirection == LEFT) ) {
            flag = true;
            angle2 = 180;
        }
        else if (((*it)->dircetion == RIGHT && checkPrevDirection == UP) || ((*it)->dircetion == DOWN && checkPrevDirection == LEFT)) {
            flag = true;
            angle2 = -90;
        }
        else if (((*it)->dircetion == UP && checkPrevDirection == RIGHT) || ((*it)->dircetion == LEFT && checkPrevDirection == DOWN)) {
            flag = true;
            angle2 = 90;
        }
        else if (((*it)->dircetion == DOWN && checkPrevDirection == RIGHT) || ((*it)->dircetion == LEFT && checkPrevDirection == UP)) {
            flag = true;
            angle2 = 0;
        }

        // ���� ��� ����� ��쿡�� ��� �̹����� ����ϰ�, �׷��� ���� ��쿡�� ������ �� �̹����� ����մϴ�.
        if (it == snakeList.begin()) {
            SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);
        }
        else if (it == last) {
            SDL_RenderCopyEx(g_renderer, snakeTail_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);

        }
        else {
            if(!flag)
                SDL_RenderCopyEx(g_renderer, snakeBody_texture, NULL, &snake_destination_rect, angle,NULL, SDL_FLIP_NONE);
            else
                SDL_RenderCopyEx(g_renderer, snakeCurve_texture, NULL, &snake_destination_rect, angle2, NULL, SDL_FLIP_NONE);

        }

        checkPrevDirection = (*it)->dircetion;
        flag = false;
    }
    
    
    // ��ġ �׸���
    magpie_destination_rect.x = magpie->getX() * GRID; //�׷��� ��ǥ ����
    magpie_destination_rect.y = magpie->getY() * GRID;

    // ��ġ ������
    if (!magpie->getInvincible() || SDL_GetTicks() % 500 < 250) { // ���� ���°� �ƴϰų� 0.25�� �������� �����Ÿ�
        SDL_RenderCopyEx(g_renderer, magpie_texture, NULL, &magpie_destination_rect, 0, NULL, flip);
    }


    //��Ʈ ���

    heart_destination_rect.w = GRID-10;
    heart_destination_rect.h = GRID-10;
    int hp = (int)magpie->getHealth();

    // ��ġ ������
    if (!magpie->getInvincible() || SDL_GetTicks() % 500 < 150) { // ���� ���°� �ƴϰų� 0.15�� �������� ����
        


    }
    for (int i = 0;i < 5;i++) {
        
        heart_destination_rect.x = i * GRID;
        heart_destination_rect.y = 0+5;
        if (hp / 10 != 0) {
            SDL_RenderCopy(g_renderer, heartOne_texture, NULL, &heart_destination_rect);
        }
        else if(hp %10 == 5){
            SDL_RenderCopy(g_renderer, heartHalf_texture, NULL, &heart_destination_rect);
        }
        else if (hp <= 0) {
            SDL_RenderCopy(g_renderer, heartZero_texture, NULL, &heart_destination_rect);

        }
        if (hp <= 0)
            continue;
        hp -= 10;
    }

    //���� �� ���� ���
    

    //// 3. ������ �ϼ�.
    // std::cout���� ����� ���� ��, ���� ȭ�鿡 ǥ�õ� �ʰ� ���ۿ� ���� �ִ� ���� �ִٸ�, ��� ȭ�鿡 ��µǵ��� �Ѵ�.
    SDL_RenderPresent(g_renderer);
    
}
void Stage3::Reset() {

}


Stage3::~Stage3() {
    //�̹��� �ؽ��� ����
    SDL_DestroyTexture(snakeHead_texture);
    SDL_DestroyTexture(snakeBody_texture);
    SDL_DestroyTexture(snakeTail_texture);
    SDL_DestroyTexture(snakeCurve_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(bell_texture);
    SDL_DestroyTexture(magpie_texture);
    SDL_DestroyTexture(heartZero_texture);
    SDL_DestroyTexture(heartHalf_texture);
    SDL_DestroyTexture(heartOne_texture);


    //��ü ����
    delete bell;
    delete magpie;
    delete snake;
    delete bomb;
}