#include "LTexture.h"

LTexture::LTexture()
{
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	Free();
}

void LTexture::Free()
{
	if (mTexture != nullptr)
	{
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

bool LTexture::LoadFromRenderedText(std::string textureText,TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer)
{
	Free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return mTexture != NULL;
}

bool LTexture::LoadFromFile(std::string path, SDL_Renderer *gRenderer)
{
	Free();

	SDL_Texture* tmpTexture = nullptr;

	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	if (tmpSurface == nullptr)
	{
		printf("Can not load image. %s\n", IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == nullptr)
		{
			printf("Can not create texture from surface. %s\n", SDL_GetError());
		}
		else
		{
			mWidth = tmpSurface->w;
			mHeight = tmpSurface->h;
		}

		SDL_FreeSurface(tmpSurface);
	}

	mTexture = tmpTexture;

	return mTexture != nullptr;
}

void LTexture::Render(int frame, int x, int y, int width, int height, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
	SDL_Rect renderSpace = { x, y, mWidth, mHeight };


    renderSpace.w = width;
    renderSpace.h = height;


    if (frame == 0){
        SDL_RenderCopy(gRenderer, mTexture, clip, &renderSpace);
    }
    else if (frame > 0){
        int k = (SDL_GetTicks() / 150) % frame;
        SDL_RenderCopy(gRenderer, mTexture, clip + k, &renderSpace);

    }
}

void LTexture::Rotate(int frame, int angle, int x, int y, int width, int height, SDL_Renderer* gRenderer, SDL_Rect* clip){
    SDL_Rect renderSpace = { x, y, mWidth, mHeight };
    if (clip != nullptr){
		renderSpace.w = width;
		renderSpace.h = height;
    }


    if (frame == 0){
        SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderSpace, angle, NULL, SDL_FLIP_NONE);
    }
    else if (frame > 0){
        int k = (SDL_GetTicks() / 150) % frame;
        SDL_RenderCopyEx(gRenderer, mTexture, clip + k, &renderSpace, angle, NULL, SDL_FLIP_NONE);
    }
}

int LTexture::GetWidth()
{
	return mWidth;
}

int LTexture::GetHeight()
{
	return mHeight;
}
