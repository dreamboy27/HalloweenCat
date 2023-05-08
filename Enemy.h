#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "GameBase.h"
#include "LTexture.h"

class Enemy
{
private:
    LTexture EnemyTexture;
    LTexture HealthTexture;
    LTexture EnemyDeadTexture;
    LTexture EnemyAttackTexture;
    LTexture EnemyHurtTexture;
    SDL_Rect EnemyClips[2];
    SDL_Rect EnemyHurtClips[5];
    SDL_Rect EnemyAttackClips[7];
    SDL_Rect EnemyDeadClips[8];

public:
	Enemy();

	~Enemy();
    bool attack = false;
    int start_x;
    int start_y;
    int pos_x;
	int pos_y;
	std::vector <int> health;

    int timeattack = 0;
    int timedie = 0;
    int timehurt = 0;
    int timemove = 0;

	void Free();

	void SetPosition(int x, int y, SDL_Renderer* gRenderer);

	void move(int char_pos_x, int char_pos_y);

	void SetHealth(int levelgame);

	void RenderEnemy(int frame, int width, int height, SDL_Renderer* gRenderer, SDL_Rect* clip);

	void RenderHealth(int levelgame, int width, int height, SDL_Renderer* gRenderer);

    void RenderDead(int frame, int width, int height, SDL_Renderer* gRenderer, SDL_Rect* clip);

    void RenderAttack(int frame, int width, int height, SDL_Renderer* gRenderer, SDL_Rect* clip);

    void RenderHurt(int frame, int width, int height, SDL_Renderer* gRenderer);

};

#endif // ENEMY_H_INCLUDED
