#include "Turnoffthelight.h"

TurnoffthelightApp theApp;

BOOL InitApp(int argc, char* args[])
{
	memset(&theApp, 0, sizeof(theApp));

	//初始化SDL 
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0)
	{
		printf("SDL could not initialize! SDL error:%s\n", SDL_GetError());
		return FALSE;
	}
	//创建游戏窗口
	theApp.gWindow = SDL_CreateWindow("TurnoftheLight", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (theApp.gWindow == NULL)
	{
		printf("Fail to create SDL window! SDL error:%s\n", SDL_GetError());
		return FALSE;
	}
	//创建游戏窗口的渲染器
	theApp.gRenderer = SDL_CreateRenderer(theApp.gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (theApp.gRenderer == NULL)
	{
		printf("Failed to create renderer!SDL Error:%s\n", SDL_GetError());
		return FALSE;
	}
	//初始化PNG与JPG图片加载模式  
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)))
	{
		printf("IMG_INIT_PNG and IMG_INIT_JPG could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return FALSE;
	}
	//初始化TTF
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return FALSE;
	}

	//初始化SDL_mixer 
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	//加载媒体资源
	if (!LoadMedia())
	{
		printf("Failed in loading files\n");
		return FALSE;
	}

	//postUserEvent(evtStartGame);

	return TRUE;
}

void CleanApp()
{
	//int i;
	//释放纹理
	freeLTexture(&theApp.bgLT);
	TTF_CloseFont(theApp.gFont);
	freeLTexture(&theApp.bulbLT[LIGHTON]);
	freeLTexture(&theApp.bulbLT[LIGHTOFF]);
	freeLTexture(&theApp.brightnessLT[LIGHTON]);
	freeLTexture(&theApp.brightnessLT[LIGHTOFF]);
	freeLTexture(&theApp.boyLT[wake]);
	freeLTexture(&theApp.boyLT[littesleepy]);
	freeLTexture(&theApp.boyLT[sleepy]);
	freeLTexture(&theApp.successLT[0]);
	freeLTexture(&theApp.successLT[1]);
	freeLTexture(&theApp.failLT[0]);
	freeLTexture(&theApp.failLT[1]);
	freeLTexture(&theApp.levelLT);
	freeLTexture(&theApp.stepLT);
	

	//释放音频
	Mix_FreeMusic(theApp.gMusic);
	theApp.gMusic = NULL;
	Mix_FreeChunk(theApp.wavturnon);
	theApp.wavturnon = NULL;
	Mix_FreeChunk(theApp.wavsnore);
	theApp.wavsnore = NULL;


	SDL_DestroyWindow(theApp.gWindow);
	SDL_DestroyRenderer(theApp.gRenderer);

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!InitApp(argc, args))
		return 0;
	RunApp();
	CleanApp();
	return 0;
}