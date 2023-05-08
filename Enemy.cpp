#include "Enemy.h"

Enemy::Enemy(){
    pos_x = 0;
    pos_y = 0;
}

Enemy::~Enemy(){
    Free();
}


void Enemy::Free()
{
    health.clear();
    EnemyTexture.Free();
    HealthTexture.Free();
    EnemyAttackTexture.Free();
    EnemyDeadTexture.Free();
}

void Enemy::SetPosition(int x, int y, SDL_Renderer* gRenderer){
    pos_x = x;
    pos_y = y;
    start_x = x;
    start_y = y;
    EnemyTexture.LoadFromFile("image/enemy/normal.png", gRenderer);
    EnemyDeadTexture.LoadFromFile("image/enemy/dead.png", gRenderer);
    for (int i = 0; i < 8; i++){
        EnemyDeadClips[i].x = 150*i;
        EnemyDeadClips[i].y = 0;
        EnemyDeadClips[i].w = 150;
        EnemyDeadClips[i].h = 150;
    }
    EnemyHurtTexture.LoadFromFile("image/enemy/hurt.png", gRenderer);
    for (int i = 0; i < 5; i++)
    {
        EnemyHurtClips[i].x = 150*i;
        EnemyHurtClips[i].y = 0;
        EnemyHurtClips[i].w = 150;
        EnemyHurtClips[i].h = 150;
    }

    EnemyAttackTexture.LoadFromFile("image/enemy/attack.png", gRenderer);
    for (int i = 0; i < 7; i++)
    {
        EnemyAttackClips[i].x = 150*i;
        EnemyAttackClips[i].y = 0;
        EnemyAttackClips[i].w = 150;
        EnemyAttackClips[i].h = 150;
    }
}

void Enemy::SetHealth(int levelgame){
    for (int i = 0; i < levelgame; i++){
        health.push_back(std::rand() % 4);
    }

}

void Enemy::move(int char_pos_x, int char_pos_y){

    if(!attack){

        int dx = abs(char_pos_x - pos_x);
        int dy = abs(char_pos_y - pos_y);
        int sx = (start_x < char_pos_x) ? 1 : -1;
        int sy = (start_y < char_pos_y) ? 1 : -1;
        int err = dx - dy;

        if (pos_x != char_pos_x || pos_y != char_pos_y) {

            int e2 = err * 2;
            if (e2 > -dy)
            {
                err -= dy;
                pos_x += sx;
            }
            if (e2 < dx)
            {
                err += dx;
                pos_y += sy;
            }
        }

    }


    if ((pos_x + 40 > CHAR_POS_X && pos_x < CHAR_POS_X && pos_y + 100 > CHAR_POS_Y && pos_y < CHAR_POS_Y)
        || (pos_x + 40 > CHAR_POS_X && pos_x < CHAR_POS_X && pos_y > CHAR_POS_Y && pos_y < CHAR_POS_Y + 100)
        || (pos_x > CHAR_POS_X && pos_x < CHAR_POS_X + 40 && pos_y + 100 > CHAR_POS_Y && pos_y < CHAR_POS_Y)
        || (pos_x > CHAR_POS_X && pos_x < CHAR_POS_X + 40 && pos_y > CHAR_POS_Y && pos_y < CHAR_POS_Y + 100)){
        attack = true;
    }
}

void Enemy::RenderEnemy(int frame, int width, int height, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr){
    if(!attack){
        EnemyTexture.Render(frame, pos_x, pos_y, width, height, gRenderer, clip);
    }
    if (attack){
        Enemy::RenderAttack(7, ENEMY_WIDTH, ENEMY_HEIGHT, gRenderer, EnemyAttackClips);
        timeattack++;
    }
}


void Enemy::RenderHealth(int levelgame, int width, int height, SDL_Renderer* gRenderer){
    LTexture HealthTexture[levelgame];
    for (int i = levelgame - 1; i >= 0; i--){
        if (health[i] == 0){
            HealthTexture[levelgame-1-i].LoadFromFile("image/horizontal.png", gRenderer);
        }
        if (health[i] == 1){
            HealthTexture[levelgame-1-i].LoadFromFile("image/vertical.png", gRenderer);
        }
        if (health[i] == 2){
            HealthTexture[levelgame-1-i].LoadFromFile("image/sunken.png", gRenderer);
        }
        if (health[i] == 3){
            HealthTexture[levelgame-1-i].LoadFromFile("image/bugle.png", gRenderer);
        }
    }
    int widthhealth = levelgame * 13;
    int heighthealth = 60;

    for (int i = 0; i < levelgame; i++){
        HealthTexture[i].Render(0, pos_x+ENEMY_WIDTH/2-widthhealth + 25*i, pos_y + 10 , width, height, gRenderer, NULL);
    }
}

void Enemy::RenderDead( int frame, int width, int height, SDL_Renderer* gRenderer, SDL_Rect* clip){

    if (health.empty()){
        EnemyTexture.Free();
        HealthTexture.Free();
        EnemyDeadTexture.Render(frame, pos_x, pos_y, width, height, gRenderer, clip);
        timedie++;
    }

}

void Enemy::RenderHurt(int frame, int width, int height, SDL_Renderer* gRenderer){
    EnemyHurtTexture.Render(frame, pos_x, pos_y, width, height, gRenderer, EnemyHurtClips);
}

void Enemy::RenderAttack(int frame, int width, int height, SDL_Renderer* gRenderer, SDL_Rect* clip){
    if (attack){
        EnemyAttackTexture.Render(frame, pos_x, pos_y, width, height, gRenderer, EnemyAttackClips);
    }
}
