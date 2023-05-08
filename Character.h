#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "LTexture.h"

class Character
{

private:
    LTexture RunCat;
    LTexture WaitCat;
    LTexture DrawCat;
    LTexture HealthCat;
    LTexture HurtCat;
    LTexture DrawBugle;
    LTexture DrawSunken;
    LTexture DrawHorizontal;
    LTexture DrawVertical;
    LTexture DieCat;

    SDL_Rect DieCatClips[16];
    SDL_Rect HurtCatClips[4];
    SDL_Rect RunCatClips[6];
    SDL_Rect WaitCatClips[21];
    SDL_Rect DrawCatClips[6];
    SDL_Rect DrawHorizontalClips[4];
    SDL_Rect DrawVerticalClips[4];
    SDL_Rect DrawSunkenClips[6];
    SDL_Rect DrawBugleClips[6];

public:
    bool played = false;
    int RunCatX = -10;
    int TIMEDIE = 0;
    LTexture Health[5];
	Character();

	~Character();

	void Free();

	void SetPosition(int x, int y, SDL_Renderer* renderer);

	void Run(int *char_pos_x, int char_pos_y, SDL_Renderer* renderer);

	void RenderHealth(int CHAR_HEALTH, int width, int height, SDL_Renderer* gRenderer);

    void RenderHurt(int frame, int width, int height, SDL_Renderer* gRenderer);

    void RenderDead( SDL_Renderer* gRenderer);


};


#endif // CHARACTER_H_INCLUDED
