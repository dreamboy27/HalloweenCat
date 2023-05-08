#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "GameBase.h"
#include "LTexture.h"


class Button
{
public:
	ButtonSprite currentSprite;

	Button();

	Button(int x, int y);

	void SetPosition(int x, int y);

	bool IsInside(SDL_Event *e, int size);

	void Render(int width, int height, SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture);

private:
	SDL_Point position;
};


#endif // BUTTON_H_INCLUDED
