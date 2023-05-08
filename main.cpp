#include "GameBase.h"
#include "LTexture.h"
#include "Button.h"
#include "Enemy.h"
#include "Character.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Color textcolor = { 239, 185, 7 };
SDL_Color gameovertextcolor = {255,255,255};
TTF_Font* font = nullptr;
Mix_Music* mainmusic = nullptr;
Mix_Chunk* fightmusic = nullptr;
LTexture scoretexture;
LTexture startbackground;
LTexture gameoverbackground;
LTexture startbutton1;
LTexture startbutton2;
LTexture textgameover;
LTexture mutetexture;
LTexture opensoundtexture;
LTexture PlayBackground;
LTexture PlayBackgroundSprite;
LTexture PlayBackgroundLeft;
LTexture PlayBackgroundRight;
LTexture RunCat;
LTexture WaitCat;
LTexture DrawCat;
LTexture bubble[40];
LTexture DrawHorizontal;
LTexture DrawVertical;
LTexture DrawSunken;
LTexture DrawBugle;
LTexture EnemyTexture;
LTexture EnemyDeadTexture;
LTexture EnemyHurtTexture;
LTexture EnemyAttackTexture;
std::vector <LTexture> HealthTexture;
Character Player;


int RunCatX = -100;
bool gameover = false;
bool quit = false;
bool isclick = false;
bool clicked = false;
vector <SDL_Rect> rects;
vector <SDL_Point> points;
vector <SDL_Point> points_dis;
vector <int> status;
vector <int> finalstatus;
vector <float> hsg;
vector <int> drawkill;
float hsgtemp;
int x, y;
SDL_Event e;
int frame = 0;
bool played = false;
bool started = false;
bool drawed = false;
bool beattack = false;
int SCORE = 0;
int SCORETEMP = 0;
int TIMEDIE = 0;
int ENEMYSIZE = 6;
int draw[6];
int LEVEL_GAME = 1;
int CHAR_HEALTH = 5;

Button start;

SDL_Rect startclips1[5];
SDL_Rect startclips2[5];
SDL_Rect opensoundbutton[2];
SDL_Rect mutebutton[2];
SDL_Rect RunCatClips[6];
SDL_Rect WaitCatClips[21];
SDL_Rect DrawCatClips[6];
SDL_Rect DrawHorizontalClips[4];
SDL_Rect DrawVerticalClips[4];
SDL_Rect DrawSunkenClips[6];
SDL_Rect DrawBugleClips[6];
SDL_Rect PlayBackgroundClips[4];
SDL_Rect EnemyClips[2];
SDL_Rect EnemyDeadClips[8];
SDL_Rect EnemyHurtClips[5];
SDL_Rect EnemyAttackClips[7];

bool Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
        printf("Can not initialize SDL %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!";
		}

		window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
            printf("Can not create window %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
                printf("Can not create renderer %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
                    printf("Can not initialize SDL_image %s\n", IMG_GetError());
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool LoadMedia()
{
	bool success = true;

	mainmusic = Mix_LoadMUS("sound/mainmusic.mp3");
	if (mainmusic == nullptr)
	{
	    printf("Failed to load main music %s\n", Mix_GetError());
		success = false;
	}

	fightmusic = Mix_LoadWAV("sound/fightmusic.mp3");
	if (fightmusic == nullptr)
	{
	    printf("Failed to load fight music %s\n", Mix_GetError());
		success = false;
	}

	else
	{
		font = TTF_OpenFont("font/pixel_font.ttf", 28);
		if (font == NULL)
        {
            printf("Failed to load font file %s\n", TTF_GetError());
			success = false;
        }
		else
		{

			if (!startbackground.LoadFromFile("image/background/start.png", renderer))
			{
				std::cout << "Failed to load start background" << std::endl;
				success = false;
			}
			if (!gameoverbackground.LoadFromFile("image/background2/gameover.png", renderer))
			{
				std::cout << "Failed to load gameover background" << std::endl;
				success = false;
			}
			if (!PlayBackground.LoadFromFile("image/background2/background.png", renderer))
			{
				std::cout << "Failed to load play background" << std::endl;
				success = false;
			}
			if (!PlayBackgroundLeft.LoadFromFile("image/background2/leftlv1.png", renderer))
			{
				std::cout << "Failed to load left play background" << std::endl;
				success = false;
			}
			if (!PlayBackgroundRight.LoadFromFile("image/background2/rightlv1.png", renderer))
			{
				std::cout << "Failed to load right play background" << std::endl;
				success = false;
			}
            for (int i = 0; i < 19; i++){
                    if (!bubble[2*i].LoadFromFile("image/bubble/bubble2.png", renderer))
                    {
                        std::cout << "Failed to load bubble2 background" << std::endl;
                        success = false;
                    }
                    if (!bubble[2*i+1].LoadFromFile("image/bubble/bubble3.png", renderer))
                    {
                        std::cout << "Failed to load bubble3 background" << std::endl;
                        success = false;
                    }
            }
			if (!startbutton1.LoadFromFile("image/button/startbutton/start1.png", renderer))
			{
				std::cout << "Failed to load startbutton1 image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < 5; ++i)
				{
					startclips1[i].x = 79 * i;
					startclips1[i].y = 0;
					startclips1[i].w = 79;
					startclips1[i].h = 81;
				}
			}

			if (!startbutton2.LoadFromFile("image/button/startbutton/start2.png", renderer))
			{
				std::cout << "Failed to load startbutton2 image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < 5; ++i)
				{
					startclips2[i].x = 82 * i;
					startclips2[i].y = 0;
					startclips2[i].w = 82;
					startclips2[i].h = 82;
				}
			}

			if (!opensoundtexture.LoadFromFile("image/button/opensound/open.png", renderer))
			{
				std::cout << "Failed to load open sound image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < 2; ++i)
				{
					opensoundbutton[i].x = 56 * i;
					opensoundbutton[i].y = 0;
					opensoundbutton[i].w = 56;
					opensoundbutton[i].h = 33;
				}
			}

			if (!mutetexture.LoadFromFile("image/button/mute/mute.png", renderer))
			{
				std::cout << "Failed to load mute image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < 2; ++i)
				{
					mutebutton[i].x = 56 * i;
					mutebutton[i].y = 0;
					mutebutton[i].w = 56;
					mutebutton[i].h = 33;
				}
			}
			if (!RunCat.LoadFromFile("image/character/run.png", renderer))
			{
				std::cout << "Failed to load run cat sprite" << std::endl;
				success = false;
			}
			else{
                for (int i = 0; i < 6; i++)
                {
                    RunCatClips[i].x = 190*i;
                    RunCatClips[i].y = 0;
                    RunCatClips[i].w = 190;
                    RunCatClips[i].h = 170;
                }
			}
			if (!WaitCat.LoadFromFile("image/character/waiting.png", renderer))
			{
				std::cout << "Failed to load play cat sprite" << std::endl;
				success = false;
			}
			else{
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
			}
			if (!DrawCat.LoadFromFile("image/character/drawing.png", renderer))
			{
				std::cout << "Failed to load draw cat sprite" << std::endl;
				success = false;
			}
			else{
                for (int i = 0; i < 6; i++)
                {
                    DrawCatClips[i].x = 190*i;
                    DrawCatClips[i].y = 0;
                    DrawCatClips[i].w = 190;
                    DrawCatClips[i].h = 170;
                }
			}
			if (!DrawHorizontal.LoadFromFile("image/character/draw_horizontal.png", renderer))
			{
				std::cout << "Failed to load draw horizontal sprite" << std::endl;
				success = false;
			}
			else{
                for (int i = 0; i < 5; i++)
                {
                    DrawHorizontalClips[i].x = 190*i;
                    DrawHorizontalClips[i].y = 0;
                    DrawHorizontalClips[i].w = 190;
                    DrawHorizontalClips[i].h = 170;
                }
			}
			if (!DrawVertical.LoadFromFile("image/character/draw_vertical.png", renderer))
			{
				std::cout << "Failed to load draw vertical sprite" << std::endl;
				success = false;
			}
			else{
                for (int i = 0; i < 5; i++)
                {
                    DrawVerticalClips[i].x = 190*i;
                    DrawVerticalClips[i].y = 0;
                    DrawVerticalClips[i].w = 190;
                    DrawVerticalClips[i].h = 170;
                }
			}
			if (!DrawSunken.LoadFromFile("image/character/draw_sunken.png", renderer))
			{
				std::cout << "Failed to load draw sunken sprite" << std::endl;
				success = false;
			}
			else{
                for (int i = 0; i < 5; i++)
                {
                    DrawSunkenClips[i].x = 190*i;
                    DrawSunkenClips[i].y = 0;
                    DrawSunkenClips[i].w = 190;
                    DrawSunkenClips[i].h = 170;
                }
			}
			if (!DrawBugle.LoadFromFile("image/character/draw_bugle.png", renderer))
			{
				std::cout << "Failed to load draw bugle sprite" << std::endl;
				success = false;
			}
			else{
                for (int i = 0; i < 5; i++)
                {
                    DrawBugleClips[i].x = 190*i;
                    DrawBugleClips[i].y = 0;
                    DrawBugleClips[i].w = 190;
                    DrawBugleClips[i].h = 170;
                }
			}
			for (int j = 0; j < 8; j++){
                if (!PlayBackgroundSprite.LoadFromFile("image/background2/lightlv1.png", renderer))
                {
                    std::cout << "Failed to load background sprite" << std::endl;
                    success = false;
                }
                else{
                    for (int i = 0; i < 4; i++)
                    {
                        PlayBackgroundClips[i].x = 170*i;
                        PlayBackgroundClips[i].y = 0;
                        PlayBackgroundClips[i].w = 170;
                        PlayBackgroundClips[i].h = 160;
                    }
                }
			}
			if (!EnemyTexture.LoadFromFile("image/enemy/normal.png", renderer))
			{
				std::cout << "Failed to load enemy sprite" << std::endl;
				success = false;
			}

			if (!EnemyDeadTexture.LoadFromFile("image/enemy/dead.png", renderer))
			{
				std::cout << "Failed to load enemy dead sprite" << std::endl;
				success = false;
			}
			else{
                for (int i = 0; i < 8; i++)
                {
                    EnemyDeadClips[i].x = 150*i;
                    EnemyDeadClips[i].y = 0;
                    EnemyDeadClips[i].w = 150;
                    EnemyDeadClips[i].h = 150;
                }
			}
			if (!EnemyHurtTexture.LoadFromFile("image/enemy/hurt.png", renderer))
			{
				std::cout << "Failed to load enemy hurt sprite" << std::endl;
				success = false;
			}
			else{
                for (int i = 0; i < 5; i++)
                {
                    EnemyHurtClips[i].x = 150*i;
                    EnemyHurtClips[i].y = 0;
                    EnemyHurtClips[i].w = 150;
                    EnemyHurtClips[i].h = 150;
                }
			}
			if (!EnemyAttackTexture.LoadFromFile("image/enemy/attack.png", renderer))
			{
				std::cout << "Failed to load enemy attack sprite" << std::endl;
				success = false;
			}
			else{
                for (int i = 0; i < 7; i++)
                {
                    EnemyAttackClips[i].x = 150*i;
                    EnemyAttackClips[i].y = 0;
                    EnemyAttackClips[i].w = 150;
                    EnemyAttackClips[i].h = 150;
                }
			}

		}
	}
	return success;
}


int main(int argc, char* argv[])
{
    int min = 0;

    if (!Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!LoadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{

     vector<Enemy> enemys;
                    for (int i = 0; i < ENEMYSIZE; i++){
                        Enemy tempEnemy;
                        tempEnemy.SetHealth(LEVEL_GAME);
                        if (i < 3){
                            tempEnemy.SetPosition(CHAR_POS_X/10, CHAR_POS_Y + 30 - (i%3 - 1) * 150, renderer);
                        }
                        else{
                            tempEnemy.SetPosition(SCREEN_WIDTH - CHAR_POS_X/2, CHAR_POS_Y + 30 - (i%3 - 1) * 150, renderer);
                        }
                        enemys.push_back(tempEnemy);
                    }

//    Enemy enemy;
//    enemy.SetHealth(LEVEL_GAME);
//    enemy.SetPosition(SCREEN_WIDTH - CHAR_POS_X/5, CHAR_POS_Y + 5 * 30, renderer);

    while( !quit ){
        Uint32 startick = SDL_GetTicks();
        if (!started){
            std::srand(std::time(nullptr));
            SDL_SetRenderDrawColor( renderer, 60, 60, 60, 0xFF );
            SDL_RenderClear( renderer );
            startbackground.Render(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);

            if( SDL_PollEvent( &e ) ){
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                SDL_GetMouseState(&x, &y);
                if (x >= 360 && x <= 510 && y >= 200 && y <= 350){
                    if (e.type == SDL_MOUSEBUTTONDOWN){
                        switch (e.button.button){
                        case SDL_BUTTON_LEFT:
                            started = true;
                            break;
                        }
                    }
                }
            }

                if (x >= 360 && x <= 510 && y >= 200 && y <= 350){
                    startbutton2.Render(5, 340, 190, 180, 180, renderer, startclips2);
                }
                else{
                    startbutton1.Render(5, 340, 190, 180, 180, renderer, startclips1);
                }
            SDL_RenderPresent(renderer);
        }

        if (started){
                SDL_RenderClear( renderer );

                PlayBackground.Render(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                PlayBackgroundLeft.Render(0, -120, 380, 368, 176, renderer);
                PlayBackgroundRight.Render(0, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 150, 300, 200, renderer);
                PlayBackgroundSprite.Render(1, 30, 300, 200, 200, renderer, PlayBackgroundClips);


            if (!Player.played){
                Player.Run(&RunCatX, CHAR_POS_Y, renderer);
            }
            if( Mix_PlayingMusic() == 0 )
            {
                //Play the music
                Mix_PlayMusic( mainmusic, -1 );
                Mix_SetMusicPosition(5);
            }


            if (Player.played && CHAR_HEALTH > 0){
            Player.RenderHealth(CHAR_HEALTH, 25, 25, renderer);
            if(!scoretexture.LoadFromRenderedText(std::to_string(SCORETEMP), font, textcolor, renderer)){
                cout << " loi load text";
            };
            scoretexture.Render(0, SCREEN_WIDTH - 80, 10, 40, 50, renderer);
            if (SCORETEMP < SCORE){
                SCORETEMP++;
            }
            int delsymbol = 1;
            while( SDL_PollEvent( &e ) != 0 ){
                if( e.type == SDL_QUIT ){
                    quit = true;
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN){
                    switch (e.button.button){
                    case SDL_BUTTON_LEFT:
                        clicked = true;
                        isclick = true;
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        points_dis.push_back({x, y});
                        status.clear();
                        finalstatus.clear();
                        break;
                    }
                }
                else if (e.type == SDL_MOUSEBUTTONUP){
                    switch (e.button.button){
                    case SDL_BUTTON_LEFT:
                        isclick = false;
                        points.clear();
                        points_dis.clear();
                        break;
                    }
                }
                else if (e.type == SDL_MOUSEMOTION && isclick == true){
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    SDL_Point last = points_dis.back();
                    if ((x-last.x)*(x-last.x)+(y-last.y)*(y-last.y) >= 3600) {points_dis.push_back({x, y});}
                    points.push_back({x, y});
                }


                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            }
                if (!drawkill.empty()){
                    drawed = true;
                }
                else{
                    drawed = false;
                }
                 if (points_dis.size() > 1){
                int n = points_dis.size();
                int iter1 = n - 1;
                int iter2 = n - 2;
                    if (points_dis[iter1].x != points_dis[iter2].y){
                        hsgtemp = fabs(points_dis[iter1].y - points_dis[iter2].y)/fabs(points_dis[iter1].x - points[iter2].x);
                    }
                    if (points_dis[iter1].x == points_dis[iter2].x){
                        hsgtemp = -1;
                    }
                    if (hsgtemp >= float(0) && hsgtemp < float(0.2)){
                        status.push_back(HORIZONTAL);
                    }
                    if (hsgtemp > float(5) || hsgtemp == -1){
                        status.push_back(VERTICAL);
                    }
                    if (hsgtemp >= float(0.2) && hsgtemp <= float(5)){
                        if (points_dis[iter1].x > points_dis[iter2].x && points_dis[iter1].y > points_dis[iter2].y){
                            status.push_back(RIGHTDOWN);
                        }
                        if (points_dis[iter1].x > points_dis[iter2].x && points_dis[iter1].y < points_dis[iter2].y){
                            status.push_back(RIGHTUP);
                        }
                        if (points_dis[iter1].x < points_dis[iter2].x && points_dis[iter1].y > points_dis[iter2].y){
                            status.push_back(LEFTDOWN);
                        }
                        if (points_dis[iter1].x < points_dis[iter2].x && points_dis[iter1].y < points_dis[iter2].y){
                            status.push_back(LEFTUP);
                        }
                    }
                    if (status.size() >= 2){
                        int first = status.front();
                        int last = status.back();
                        if (finalstatus.empty()){
                            finalstatus.push_back(first);
                        }
                        else{
                            if (last != finalstatus.back()){
                                finalstatus.push_back(last);
                            }
                        }
                    }
                }
                if (isclick){
                    DrawCat.Render(6, CHAR_POS_X, CHAR_POS_Y, CHAR_WIDTH, CHAR_HEIGHT, renderer, DrawCatClips);
                }
                if (!isclick && !drawed && !beattack){
                    WaitCat.Render(20, CHAR_POS_X, CHAR_POS_Y, CHAR_WIDTH, CHAR_HEIGHT, renderer, WaitCatClips);
                }
                    for (int i = 0; i < enemys.size(); i++){

                            if (enemys[i].health.empty()){
                            enemys[i].RenderDead(8, ENEMY_WIDTH, ENEMY_HEIGHT, renderer, EnemyDeadClips);

                            if (enemys[i].timedie == 30){
                                enemys[i].Free();
                                enemys.erase(enemys.begin() + i);
                                SCORE += LEVEL_GAME*10;
                            }
                        }
                        if (draw[i] && !drawkill.empty() && !enemys[i].health.empty()){
                            enemys[i].RenderHurt(5, ENEMY_WIDTH, ENEMY_HEIGHT, renderer);
                        }
                        else{
                            if (!enemys[i].attack ){
                                if (enemys[i].timemove < 1){
                                    enemys[i].timemove += 1;
                                }
                                else{
                                enemys[i].move(CHAR_MID_X, CHAR_MID_Y);
                                enemys[i].timemove = 0;
                                }
                            }
                            else{
                                beattack = true;
                                Player.RenderHurt(4, CHAR_WIDTH, CHAR_HEIGHT, renderer);

                            }
                            enemys[i].RenderEnemy(0, ENEMY_WIDTH, ENEMY_HEIGHT, renderer, NULL);
                            if (enemys[i].timeattack == 30){
                                enemys[i].Free();
                                enemys.erase(enemys.begin() + i);
                                CHAR_HEALTH--;
                                beattack = false;
                            }
                        }
                        enemys[i].RenderHealth(enemys[i].health.size(), 30, 30, renderer);
                    }
            if (enemys.size() == 0){
                LEVEL_GAME++;
                for (int i = 0; i < ENEMYSIZE; i++){
                    Enemy tempEnemy;
                    tempEnemy.SetHealth(LEVEL_GAME);
                    if (i < 3){
                    tempEnemy.SetPosition(CHAR_POS_X/8, SCREEN_HEIGHT - (i%3 + 1) * 160, renderer);
                }
                else{
                    tempEnemy.SetPosition(SCREEN_WIDTH - CHAR_POS_X/2, SCREEN_HEIGHT - (i%3 + 1) * 160, renderer);
                }
                enemys.push_back(tempEnemy);
                }
            }

            if (clicked == true && isclick == false){
                int ok = 0;


                if (finalstatus.size() == 1){
                    if (finalstatus[0] == HORIZONTAL){
                            for (int i = 0; i < enemys.size(); i++){
                        if ( enemys[i].health.back() == 0){
                            drawkill.push_back(HORIZONTAL);
                            ok++;
                            enemys[i].health.pop_back();
                            finalstatus.clear();
                            draw[i] = 1;
                        }
                        else{
                            draw[i] = 0;
                        }
                            }
                    }
                    else if (finalstatus[0] == VERTICAL){
                            for (int i = 0; i < enemys.size(); i++){
                        if ( enemys[i].health.back() == 1){
                            drawkill.push_back(VERTICAL);
                            ok++;
                            enemys[i].health.pop_back();
                            finalstatus.clear();
                            draw[i] = 1;
                        }
                        else{
                            draw[i] = 0;
                        }
                            }
                    }
                }
                if (finalstatus.size() == 2){
                    if (finalstatus[0] == RIGHTUP && finalstatus[1] == RIGHTDOWN){
                            for (int i = 0; i < enemys.size(); i++){
                        if ( enemys[i].health.back() == 3){
                            drawkill.push_back(BUGLE);
                            ok++;
                            enemys[i].health.pop_back();
                            finalstatus.clear();
                            draw[i] = 1;
                        }
                        else{
                            draw[i] = 0;
                        }
                            }
                    }
                    else if (finalstatus[0] == LEFTUP && finalstatus[1] == LEFTDOWN){
                            for (int i = 0; i < enemys.size(); i++){
                        if ( enemys[i].health.back() == 3){
                            drawkill.push_back(BUGLE);
                            ok++;
                            enemys[i].health.pop_back();
                            finalstatus.clear();
                            draw[i] = 1;
                        }
                        else{
                            draw[i] = 0;
                        }
                            }
                    }
                    else if (finalstatus[0] == RIGHTDOWN && finalstatus[1] == RIGHTUP){
                        for (int i = 0; i < enemys.size(); i++){
                        if ( enemys[i].health.back() == 2){
                            drawkill.push_back(SUNKEN);
                            ok++;
                            enemys[i].health.pop_back();
                            finalstatus.clear();
                            draw[i] = 1;
                        }
                        else{
                            draw[i] = 0;
                        }
                            }
                    }
                    else if (finalstatus[0] == LEFTDOWN && finalstatus[1] == LEFTUP){
                        for (int i = 0; i < enemys.size(); i++){
                        if ( enemys[i].health.back() == 2){
                            drawkill.push_back(SUNKEN);
                            ok++;
                            enemys[i].health.pop_back();
                            finalstatus.clear();
                            draw[i] = 1;
                        }
                        else{
                            draw[i] = 0;
                        }
                        }
                    }
                }

                if (ok == 0){
                    finalstatus.clear();
                }


            }


            if (clicked == true && isclick == false && !drawkill.empty()){
                if (drawkill.front() == HORIZONTAL){
                    if (min < 20){
                        DrawHorizontal.Render(5, CHAR_POS_X, CHAR_POS_Y, CHAR_WIDTH, CHAR_HEIGHT, renderer, DrawHorizontalClips);
                        min++;
                    }
                    else{
                        min = 0;
                        drawkill.clear();
                    }
                }
                if (drawkill.front() == VERTICAL){
                    if (min < 20){
                        DrawVertical.Render(5, CHAR_POS_X, CHAR_POS_Y, CHAR_WIDTH, CHAR_HEIGHT, renderer, DrawVerticalClips);
                        min++;
                    }
                    else{
                        min = 0;
                        drawkill.clear();
                    }
                }
                if (drawkill.front() == SUNKEN){
                    if (min < 25){
                        DrawSunken.Render(5, CHAR_POS_X, CHAR_POS_Y, CHAR_WIDTH, CHAR_HEIGHT, renderer, DrawSunkenClips);
                        min++;
                    }
                    else{
                        min = 0;
                        drawkill.clear();
                    }
                }
                if (drawkill.front() == BUGLE){
                    if (min < 25){
                        DrawBugle.Render(5, CHAR_POS_X, CHAR_POS_Y, CHAR_WIDTH, CHAR_HEIGHT, renderer, DrawBugleClips);
                        min++;
                    }
                    else{
                        min = 0;
                        drawkill.clear();
                    }
                }
            }
            for (int i = 1; i < points.size(); i++){
                SDL_RenderDrawCurve(renderer, points[i].x, points[i].y, points[i - 1].x, points[i-1].y);
            }
            }

            if (Player.played && CHAR_HEALTH == 0 && !gameover){

                PlayBackground.Render(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                PlayBackgroundLeft.Render(0, -120, 380, 368, 176, renderer);
                PlayBackgroundRight.Render(0, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 150, 300, 200, renderer);
                PlayBackgroundSprite.Render(1, 30, 300, 200, 200, renderer, PlayBackgroundClips);
                if(Player.TIMEDIE < 70){Player.RenderDead(renderer);
                }
                else{
                    enemys.clear();
                    gameover = true;
                }
            }
            if (Player.played && CHAR_HEALTH == 0 && gameover){
                SDL_RenderClear( renderer );
                gameoverbackground.Render(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                scoretexture.LoadFromRenderedText(std::to_string(SCORETEMP), font, gameovertextcolor, renderer);
                textgameover.LoadFromRenderedText("Your Score: ", font, gameovertextcolor, renderer);
                textgameover.Render(0, SCREEN_WIDTH - 370, 100, 220, 80, renderer);
                scoretexture.Render(0, SCREEN_WIDTH - 260, 200, 100, 70, renderer);
                if( SDL_PollEvent( &e ) ){
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                SDL_GetMouseState(&x, &y);
                if (x >= SCREEN_WIDTH - 260 && x <= SCREEN_WIDTH - 110 && y >= 250 && y <= 350){
                    if (e.type == SDL_MOUSEBUTTONDOWN){
                        switch (e.button.button){
                        case SDL_BUTTON_LEFT:
                            Player.played = false;
                            started = true;
                            RunCatX = -100;
                            gameover = false;
                            quit = false;
                            isclick = false;
                            clicked = false;
                             frame = 0;
                             played = false;
                             drawed = false;
                             beattack = false;
                             SCORE = 0;
                             SCORETEMP = 0;
                             TIMEDIE = 0;
                             ENEMYSIZE = 6;
                             draw[6];
                             LEVEL_GAME = 1;
                             CHAR_HEALTH = 5;

                    for (int i = 0; i < ENEMYSIZE; i++){
                        Enemy tempEnemy;
                        tempEnemy.SetHealth(LEVEL_GAME);
                        if (i < 3){
                            tempEnemy.SetPosition(CHAR_POS_X/10, CHAR_POS_Y + 30 - (i%3 - 1) * 150, renderer);
                        }
                        else{
                            tempEnemy.SetPosition(SCREEN_WIDTH - CHAR_POS_X/2, CHAR_POS_Y + 30 - (i%3 - 1) * 150, renderer);
                        }
                        enemys.push_back(tempEnemy);
                    }

                            break;
                        }
                    }
                }
            }

                if (x >= SCREEN_WIDTH - 260 && x <= SCREEN_WIDTH - 110 && y >= 250 && y <= 350){
                    startbutton2.Render(5, SCREEN_WIDTH - 260, 250, 100, 100, renderer, startclips2);
                }
                else{
                    startbutton1.Render(5, SCREEN_WIDTH - 260, 250, 100, 100, renderer, startclips1);
                }

            }

        SDL_RenderPresent(renderer);
        }
        Uint32 realtime = SDL_GetTicks() - startick;
        const int fps = 60;
        int timeperframe = 1000/fps;
        if (realtime < timeperframe){
            SDL_Delay(timeperframe-realtime);
        }
    }
	}
	}
 return 0;
}
