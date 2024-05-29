#include "Phase_stage3Game.h"
#include <Windows.h>
#include <iomanip>

extern default_random_engine generator;


Stage3::Stage3() {
    //1. 객체 생성
    //a. 종 생성
    uniform_int_distribution<int> distributionX(0, screenWidth/GRID-1);
    uniform_int_distribution<int> distributionY(1, screenHeight/GRID-1);


    bell = new Bell(distributionX(generator), distributionY(generator), 0, 0);
    //b. 까치 생성
    magpie = new Magpie(3, 3, 1, 50,0); //(0,0)에서 시작, speed는 1,hp는 100으로 설정
    //c. 구렁이 생성
    snake = new Snake(0, 0, 1, 100, 10, magpie->getX(),magpie->getY());
    //d. 폭탄 생성
    bombList.push_front(new Bomb(0, 0, 1, 100, 5, magpie->getX(), magpie->getY()));

    ////2. 텍스쳐 가져오기
    //a. 종 텍스쳐
    SDL_Surface* temp_sheet_surface = IMG_Load("../../Resource/bell.png");
    bell_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    bell_destination_rect.x = bell->getX();
    bell_destination_rect.y = bell->getY();
    bell_destination_rect.w = GRID;
    bell_destination_rect.h = GRID;

    //b. 까치 텍스쳐
    temp_sheet_surface = IMG_Load("../../Resource/magpie.png");
    magpie_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    magpie_destination_rect.x = magpie->getX()*GRID;
    magpie_destination_rect.y = magpie->getY()*GRID;
    magpie_destination_rect.w = GRID;
    magpie_destination_rect.h = GRID;

    
    //c. 구렁이 텍스쳐
    temp_sheet_surface = IMG_Load("../../Resource/snakeHead.png");;
    snakeHead_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    snake_destination_rect.x = snake->getSnakeList().front()->sX;
    snake_destination_rect.y = snake->getSnakeList().front()->sY;
    snake_destination_rect.w = GRID;
    snake_destination_rect.h = GRID;

    temp_sheet_surface = IMG_Load("../../Resource/snakeBody.png");
    snakeBody_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    temp_sheet_surface = IMG_Load("../../Resource/snakeTail.png");
    snakeTail_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

   
    //폭탄 텍스쳐 
    temp_sheet_surface  = IMG_Load("../../Resource/bombAfter.png");
    bombAfter_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    bomb_source_rect.x = 0;
    bomb_source_rect.y = 0;
    bomb_source_rect.w = 32;
    bomb_source_rect.h = 32;
    
    bomb_destination_rect.w = GRID*3;
    bomb_destination_rect.h = GRID*3;

    //d. 배경 텍스쳐
    temp_sheet_surface = IMG_Load("../../Resource/background.png");
    bg_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수
    bg_destination_rect.x = GRID;
    bg_destination_rect.y = GRID;
    bg_destination_rect.w = screenWidth-GRID*2;
    bg_destination_rect.h = screenHeight-GRID*2;


    //하트 텍스처
    temp_sheet_surface = IMG_Load("../../Resource/heartZero.png");
    heartZero_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    temp_sheet_surface = IMG_Load("../../Resource/heartHalf.png");
    heartHalf_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    temp_sheet_surface = IMG_Load("../../Resource/heartOne.png");
    heartOne_texture = SDL_CreateTextureFromSurface(g_renderer, temp_sheet_surface);
    SDL_FreeSurface(temp_sheet_surface);//해제 필수

    heart_destination_rect.w = GRID;
    heart_destination_rect.h = GRID;

    //2. 기타 세팅
    f_state = STOP;//방향키 안 누름
    stop = true; //정지 상황으로 초기화
    //모두 안 눌린 것으로 초기화 -> stop
    for (int i = 0; i < f_state; i++) {//0은 좌측, ...
        f_list[i] = false;
    }
    game_result = 0;//1-> 승리, 2-> 패배

    flip = SDL_FLIP_HORIZONTAL;

    lastSpeedUpTime = 0;
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
                f_state = LEFT; //현재 눌린 값이 LEFT
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
            else if (event.key.keysym.sym == SDLK_SPACE) {
                game_result = 5; //엔딩으로 건너뛰기
                g_current_game_phase = PHASE_ENDING;
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

            //만약 up되지 않은 놈들이 있다면
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
    //1. 까치
    //1.1 까치 좌표 업데이트
    int x = magpie->getX();
    int y = magpie->getY();
    if (!stop) { //정지가 아니라면 까치 이동
        if (f_state == 0) { //좌측이동
            x -= 1;
            flip = SDL_FLIP_NONE;
        }
        else if (f_state == 1) {//우측이동
            x += 1;
            flip = SDL_FLIP_HORIZONTAL;
        }
        else if (f_state == 2) {//위로 이동
            y -= 1;
        }
        else if (f_state == 3) {//아래로 이동
            y += 1;
        }

    }

    //1.2 까치 좌표 범위
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
    //1.3 까치 이동
    magpie->move(x, y);   
    //1.4 까치 무적 시간 업데이트
    if (magpie->getInvincible() && SDL_GetTicks() - magpie->getLastDamageTime() >= 2000) {
        magpie->setInvincible(false);
    }
    

    //2. 구렁이 업데이트
    //구렁이 속도 조절
    int time = SDL_GetTicks();
    if (snake->getN() >5 && time-lastSpeedUpTime > 10000) {
        cout<<snake->getN()<<endl;
        snake->setN(snake->getN()-1);
        // 속도 증가 시간 업데이트
        // 속도 증가 시간 업데이트
        lastSpeedUpTime = time;
    }
    //구렁이 이동
    snake->move(magpie->getX(), magpie->getY());
    

    //3. 폭탄 업데이트
    for (const auto& bomb : bombList) {
        if (bomb->getCheckCount() >= 75)
            bomb->setCheckCount(-20); //재설정
        bomb->setCheckCount(bomb->getCheckCount() + 1); //카운트 개수 증가
        bomb->move(magpie->getX(), magpie->getY()); //타겟 좌표 변경 -> 0 이하일 때만 값 변경됨
    }

    //3. 충돌 확인
    //3.1 종 개수 확인
    if (magpie->isCollidingBell(bell)) {//bell이랑 부딪혔다면
        bell->setCount(bell->getCount() + 1); //count개수 하나 증가
        bell->spawn();//종 위치 갱신
    }


    //3.2 구렁이 충돌 확인
    if (magpie->isCollidingSnake(snake)) { //snake랑 부딪혔다면 hp 깎임
        magpie->GetAttackted(snake->getAttackPower());//데미지 받음
    }
    

    //3.3 폭탄 충돌 확인
    for(const auto& bomb:bombList){
        if (bomb->getCheckCount() >= 50 && bomb->getCheckCount() < 75) {
            if (magpie->isCollidingBomb(bomb)) {
                magpie->GetAttackted(bomb->getAttackPower());
            }
        }
    }


    //4. 종료 조건 확인
    if (bell->getCount() == 5) {//종 5개 모았으면 
        game_result = 1; //승리
        g_current_game_phase = PHASE_ENDING;
        
        
    }

    if (magpie->getHealth() <= 0) {
        game_result = 2; //실패
        g_current_game_phase=PHASE_ENDING;
        
    }
}
void Stage3::Render() {

    //// 1. 배경 그리기.
    // 1.1. 커서를 콘솔 화면의 왼쪽 위 모서리 부분으로 옮긴다. 좌표(0, 0)
    // <windows.h>에서 제공하는 함수를 사용한다
    
    //// 1.2. 배경 그리기
   
    int time = SDL_GetTicks();
    int r = 200, g = 200, b = 200;
    if (time < 60000) { // 1분 동안 점차 밝아짐 => 새벽에서 아침으로 변화
        r = time/240+50; // 1분 동안 255에서 0으로 감소
        if (r > 255)
            r = 255;
    }
    else { // 1분이 지나면 다시 새벽으로
        r = 200; // 새벽 색상
    }
    SDL_SetTextureColorMod(bg_texture, r, g, b);
    SDL_SetTextureColorMod(snakeHead_texture, r, g, b);
    SDL_SetTextureColorMod(snakeBody_texture, r, g, b);
    SDL_SetTextureColorMod(snakeTail_texture, r, g, b);
    SDL_SetTextureColorMod(bombAfter_texture, r, g, b);
    SDL_SetTextureColorMod(magpie_texture, r, g, b);
    SDL_SetTextureColorMod(bell_texture, r, g, b);
    SDL_RenderCopy(g_renderer, bg_texture, NULL, &bg_destination_rect);


    //// 2. 캐릭터 그리기.
    // 종 그리기
    bell_destination_rect.x = bell->getX()*GRID; //그려질 좌표 지정
    bell_destination_rect.y = bell->getY()*GRID;
    SDL_RenderCopy(g_renderer, bell_texture, NULL, &bell_destination_rect);
    
    // 폭탄 그리기
    for (const auto& bomb : bombList) {
        int b_count = bomb->getCheckCount();
        //카운트가 50보다 작고 0 이상인데 짝수면 ? 출력
        if (b_count < 50 && b_count >= 0) {
            if (b_count % 2 == 0) {
                bell_destination_rect.x = bomb->getBombRange()[4].x * GRID;
                bell_destination_rect.y = bomb->getBombRange()[4].y * GRID;
                SDL_SetTextureColorMod(bell_texture, 200, 50, 50);
                SDL_RenderCopy(g_renderer, bell_texture, NULL, &bell_destination_rect);
                SDL_SetTextureColorMod(bell_texture, 255, 255, 255);
            }
        }

        //카운트가 100에서 150 사이면 !출력
        else if (b_count >= 50 && b_count < 75) {
            bombAttack* b = bomb->getBombRange();

            if (b_count % 3 == 0) { // 51 54 57 60 63 66 69 72일 때 실행
                int i = (b_count / 3) % 17;
                bomb_source_rect.x = 32 * i; // 0 32 64 
            }

            bomb_destination_rect.x = b[0].x * GRID;
            bomb_destination_rect.y = b[0].y * GRID;

            SDL_RenderCopy(g_renderer, bombAfter_texture, &bomb_source_rect, &bomb_destination_rect);
        }
    }

    // 구렁이 그리기
    auto snakeList = snake->getSnakeList();
    auto last = --snakeList.end();
    int angle = 0;
    int prevD = LEFT;
    int shiftX = 0, shiftY = 0;
    
    for (auto it = snakeList.begin(); it != snakeList.end(); ++it) {
        snake_destination_rect.x = (*it)->sX*(GRID); // 그려질 좌표 지정
        snake_destination_rect.y = (*it)->sY*(GRID);

        //각도 설정
        switch ((*it)->dircetion) {
        case LEFT://좌
            angle = -90;
            break;
        case RIGHT://우
            angle = 90;
            break;
        case UP://위
            angle = 0;
            break;
        case DOWN://아래
            angle = 180;
            break;
        default:
            break;
        }


        // 뱀의 헤드 노드인 경우에는 헤드 이미지를 사용하고, 그렇지 않은 경우에는 기존의 뱀 이미지를 사용합니다.
        if (it == snakeList.begin()) {
            SDL_RenderCopyEx(g_renderer, snakeHead_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);
        }
        else if (it == last) {
            switch (prevD) {
            case LEFT://좌
                angle = -90;
                break;
            case RIGHT://우
                angle = 90;
                break;
            case UP://위
                angle = -0;
                break;
            case DOWN://아래
                angle = 180;

                break;
            default:
                break;
            }
            SDL_RenderCopyEx(g_renderer, snakeTail_texture, NULL, &snake_destination_rect, angle, NULL, SDL_FLIP_NONE);

        }
        else {
            SDL_RenderCopyEx(g_renderer, snakeBody_texture, NULL, &snake_destination_rect, angle,NULL, SDL_FLIP_NONE);
           
        }

       prevD= (*it)->dircetion;
    }
    
    
    // 까치 그리기
    magpie_destination_rect.x = magpie->getX() * GRID; //그려질 좌표 지정
    magpie_destination_rect.y = magpie->getY() * GRID;

    // 까치 렌더링
    if (!magpie->getInvincible() || SDL_GetTicks() % 500 < 250) { // 무적 상태가 아니거나 0.25초 간격으로 깜빡거림
        SDL_RenderCopyEx(g_renderer, magpie_texture, NULL, &magpie_destination_rect, 0, NULL, flip);
    }


    //하트 출력

    heart_destination_rect.w = GRID-15;
    heart_destination_rect.h = GRID-15;
    int hp = (int)magpie->getHealth();

    // 하트 렌더링
    for (int i = 0;i < 5;i++) {
        
        heart_destination_rect.x = i * (GRID)+GRID+5;
        heart_destination_rect.y = 0+GRID+5;

        if (magpie->getInvincible()) {
            int timeSinceDamage = SDL_GetTicks() - magpie->getLastDamageTime();
            if (timeSinceDamage < 100) {
                // 0.125초와 0.375초에 하트를 흔듬
                if ((timeSinceDamage % 100) < 20 || (timeSinceDamage % 100) > 80) {
                    heart_destination_rect.y += 10; // y 좌표를 흔듬
                }
            }
            
        }

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

    //모은 종 개수 출력 -> 아직 안 함
    

    //// 3. 프레임 완성.
    // std::cout으로 출력한 내용 중, 아직 화면에 표시되 않고 버퍼에 남아 있는 것이 있다면, 모두 화면에 출력되도록 한다.
    SDL_RenderPresent(g_renderer);
    
}
void Stage3::Reset() {
    //객체 초기화
    delete bell;
    delete magpie;
    delete snake;
    for (const auto& bomb : bombList) {
        delete bomb;
    }
    bombList.clear();

    //a. 종 생성
    uniform_int_distribution<int> distributionX(0, screenWidth / GRID - 1);
    uniform_int_distribution<int> distributionY(1, screenHeight / GRID - 1);
    bell = new Bell(distributionX(generator), distributionY(generator), 0, 0);
    //b. 까치 생성
    magpie = new Magpie(3, 3, 1, 50, 0); //(0,0)에서 시작, speed는 1,hp는 100으로 설정
    //c. 구렁이 생성
    snake = new Snake(0, 0, 1, 100, 10, magpie->getX(), magpie->getY());
    //d. 폭탄 생성
    bombList.push_front(new Bomb(0, 0, 1, 100, 5, magpie->getX(), magpie->getY()));


    //2. 기타 세팅
    f_state = STOP;//방향키 안 누름
    stop = true; //정지 상황으로 초기화
    //모두 안 눌린 것으로 초기화 -> stop
    for (int i = 0; i < f_state; i++) {//0은 좌측, ...
        f_list[i] = false;
    }
    game_result = 0;//1-> 승리, 2-> 패배

    flip = SDL_FLIP_HORIZONTAL;

    lastSpeedUpTime = 0;

}


Stage3::~Stage3() {
    //이미지 텍스쳐 해제
    SDL_DestroyTexture(snakeHead_texture);
    SDL_DestroyTexture(snakeBody_texture);
    SDL_DestroyTexture(snakeTail_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(bell_texture);
    SDL_DestroyTexture(magpie_texture);
    SDL_DestroyTexture(heartZero_texture);
    SDL_DestroyTexture(heartHalf_texture);
    SDL_DestroyTexture(heartOne_texture);


    //객체 해제
    delete bell;
    delete magpie;
    delete snake;
    for (const auto& bomb : bombList) {
        delete bomb;
    }
    bombList.clear();
}