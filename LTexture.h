#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

#include "GameBase.h"

class LTexture
{
public:
	LTexture();

	~LTexture();

	void Free();

	bool LoadFromRenderedText(std::string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer);

	bool LoadFromFile(std::string path, SDL_Renderer *gRenderer);

	void Render(int frame, int x, int y,int width, int height, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);

    void Rotate(int frame, int angle, int x, int y, int width, int height, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);


	int GetWidth();

	int GetHeight();

private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};

#endif // LTEXTURE_H_INCLUDED
