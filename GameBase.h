#ifndef GAMEBASE_H_INCLUDED
#define GAMEBASE_H_INCLUDED
#include <iostream>
#include <ctime>
#include <vector>
#include <math.h>
#include <algorithm>
#include <SDL.h>
#include <float.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2
#define STATIC 100
#define DYNAMIC 200

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

const int SCREEN_WIDTH = 890;
const int SCREEN_HEIGHT = 500;
const std::string WINDOW_TITLE = "Hogwarts Cat";

const int COMMON_BUTTON_WIDTH = 82;
const int COMMON_BUTTON_HEIGHT = 82;
const int SMALL_BUTTON_WIDTH = 56;
const int SMALL_BUTTON_HEIGHT = 33;

const int CHAR_WIDTH = 250;
const int CHAR_HEIGHT = 220;

const int ENEMY_WIDTH = 200;
const int ENEMY_HEIGHT = 200;

const int CHAR_MID_X = 330;
const int CHAR_MID_Y = 200;

const int CHAR_POS_X = 330;
const int CHAR_POS_Y = 125;

const int STARTBUTTON_POSX = 405;
const int STARTBUTTON_POSY = 210;

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};
const SDL_Color DEFAULT_COLOR = BLACK_COLOR;

const int VERTICAL = 1;
const int HORIZONTAL = 2;
const int RIGHTUP = 3;
const int RIGHTDOWN = 4;
const int LEFTUP = 5;
const int LEFTDOWN = 6;
const int BUGLE = 7;
const int SUNKEN = 8;
const int LIGHTNING = 9;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int r);
void SDL_RenderDrawCurve(SDL_Renderer* renderer, int x1, int y1, int x2, int y2);


#endif // GAMEBASE_H_INCLUDED
