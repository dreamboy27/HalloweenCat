#include "Character.h"

Character::Character(){

}

Character::~Character(){
    Free();
}

void Character::Free(){
    RunCat.Free();
    WaitCat.Free();
    DrawCat.Free();
    HealthCat.Free();
    HurtCat.Free();
    DrawBugle.Free();
    DrawSunken.Free();
    DrawHorizontal.Free();
    DrawVertical.Free();
}

void Character::Run(int *x, int y, SDL_Renderer* renderer){



    RunCat.LoadFromFile("image/character/run.png", renderer);
    for (int i = 0; i < 6; i++)
    {
        RunCatClips[i].x = 190*i;
        RunCatClips[i].y = 0;
        RunCatClips[i].w = 190;
        RunCatClips[i].h = 170;
    }
    if (!played){
        RunCat.Render(6, *x, CHAR_POS_Y, CHAR_WIDTH, CHAR_HEIGHT, renderer, RunCatClips);
        *x += 10;
        if (*x == CHAR_POS_X){
            played = true;
        }
    }
    DieCat.LoadFromFile("image/character/die.png", renderer);
    for (int i = 0; i < 16; i++){
        DieCatClips[i].x = 190*i;
        DieCatClips[i].y = 0;
        DieCatClips[i].w = 190;
        DieCatClips[i].h = 170;
    }
    WaitCat.LoadFromFile("image/character/waiting.png", renderer);
    for (int i = 0; i < 6; i++)
    {
        WaitCatClips[i].x = 190*i;
        WaitCatClips[i].y = 0;
        WaitCatClips[i].w = 190;
        WaitCatClips[i].h = 170;
    }
    for (int i = 6; i < 11; i++){
        WaitCatClips[i].x = 190 * (10-i);
        WaitCatClips[i].y = 0;
        WaitCatClips[i].w = 190;
        WaitCatClips[i].h = 170;
    }
    for (int i = 11; i < 16; i++){
        WaitCatClips[i].x = 190 * (i-5);
        WaitCatClips[i].y = 0;
        WaitCatClips[i].w = 190;
        WaitCatClips[i].h = 170;
    }
    for (int i = 16; i < 20; i++){
        WaitCatClips[i].x = 190 * (26 - i);
        WaitCatClips[i].y = 0;
        WaitCatClips[i].w = 190;
        WaitCatClips[i].h = 170;
    }

    DrawCat.LoadFromFile("image/character/drawing.png", renderer);
    for (int i = 0; i < 6; i++)
    {
        DrawCatClips[i].x = 190*i;
        DrawCatClips[i].y = 0;
        DrawCatClips[i].w = 190;
        DrawCatClips[i].h = 170;
    }

    HurtCat.LoadFromFile("image/character/hurt.png", renderer);
    for (int i = 0; i < 4; i++)
    {
        HurtCatClips[i].x = 190*i;
        HurtCatClips[i].y = 0;
        HurtCatClips[i].w = 190;
        HurtCatClips[i].h = 170;
    }

    DrawHorizontal.LoadFromFile("image/character/draw_horizontal.png", renderer);
    for (int i = 0; i < 5; i++)
    {
        DrawHorizontalClips[i].x = 190*i;
        DrawHorizontalClips[i].y = 0;
        DrawHorizontalClips[i].w = 190;
        DrawHorizontalClips[i].h = 170;
    }

    DrawVertical.LoadFromFile("image/character/draw_vertical.png", renderer);
    for (int i = 0; i < 5; i++)
    {
        DrawVerticalClips[i].x = 190*i;
        DrawVerticalClips[i].y = 0;
        DrawVerticalClips[i].w = 190;
        DrawVerticalClips[i].h = 170;
    }

    DrawSunken.LoadFromFile("image/character/draw_sunken.png", renderer);
    for (int i = 0; i < 5; i++)
    {
        DrawSunkenClips[i].x = 190*i;
        DrawSunkenClips[i].y = 0;
        DrawSunkenClips[i].w = 190;
        DrawSunkenClips[i].h = 170;
    }

    DrawBugle.LoadFromFile("image/character/draw_bugle.png", renderer);
    for (int i = 0; i < 5; i++)
    {
        DrawBugleClips[i].x = 190*i;
        DrawBugleClips[i].y = 0;
        DrawBugleClips[i].w = 190;
        DrawBugleClips[i].h = 170;
    }

}



void Character::RenderHealth(int CHAR_HEALTH, int width, int height, SDL_Renderer* gRenderer){
    for (int i = 0; i < CHAR_HEALTH; i++){
        Health[i].LoadFromFile("image/health.png", gRenderer);
    }
    for (int i = 0; i < CHAR_HEALTH; i++){
        Health[i].Render(0, 15 + 30*i, 15 , width, height, gRenderer, NULL);
    }
}

void Character::RenderHurt(int frame, int width, int height, SDL_Renderer* gRenderer){
    HurtCat.Render(4, CHAR_POS_X, CHAR_POS_Y, width, height, gRenderer, HurtCatClips);
}

void Character::RenderDead(SDL_Renderer* gRenderer){
    DieCat.Render(16, CHAR_POS_X, CHAR_POS_Y, CHAR_WIDTH, CHAR_HEIGHT, gRenderer, DieCatClips);
    TIMEDIE++;
}

