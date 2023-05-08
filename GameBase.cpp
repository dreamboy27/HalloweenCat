#include "GameBase.h"


void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
 os << msg << " Error: " << SDL_GetError() << std::endl;
 if (fatal) {
 SDL_Quit();
 exit(1);
 }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
 if (SDL_Init(SDL_INIT_EVERYTHING) != 0) logSDLError(std::cout, "SDL_Init", true);
 window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
 if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
 renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
 if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
 SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
 SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int r) {
    for(int i = -r; i <= r; i++) {
        for(int j = -r; j <= r; j++) {
            if(i*i + j*j <= r*r) {
                SDL_RenderDrawPoint(renderer, x+i, y+j);
            }
        }
    }
}

void SDL_RenderDrawCurve(SDL_Renderer* renderer, int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int x = x1;
    int y = y1;

    while (x != x2 || y != y2)
    {
        SDL_RenderDrawCircle(renderer, x, y, 4);
        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y += sy;
        }
    }
}

