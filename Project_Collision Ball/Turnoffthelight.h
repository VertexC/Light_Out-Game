#ifndef _TURNOFFTHELIGHT_H_
#define _TURNOFFTHELIGHT_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include<time.h>

#define SCREEN_WIDTH 850
#define SCREEN_HEIGHT 650


typedef int BOOL;
#define FALSE 0  
#define TRUE  1  
typedef enum {					// user defined event 
	evtStartGame = 1,			// renew a game 
	evtStopMusic,
	evtRestartGame,
	evtGameWin,
	evtGameFail
} UserEvent;
typedef enum {
	btnExposed = 0,
	btnDown
} BtnState;
typedef enum {
	sNewGame = 0,
	sGameFail,   // 游戏失败
	sGameWin,	 // 游戏胜利
} GameState;

typedef struct {

	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
}LTexture;
enum{
	LIGHTOFF = 0 ,//灯关
	LIGHTON  ,//灯开
	TOTAL
};

enum 
{
	wake = 0,
	littesleepy,
	sleepy,
	asleep,
	total
};
typedef struct{
	int frame;
	int valid;
	SDL_Rect rect;
}Boy;
typedef struct{
	int x;//在屏幕上的坐标
	int y;
	int light_on_off;//用于检测灯泡是否开着
	SDL_Rect rect;
}Bulb; 
typedef struct{
	int frame;//帧
	int valid;
	SDL_Rect rect;

}Brightness;
typedef struct
{
	SDL_Rect rect;
	int data; // data on the button
} ImageButton;
typedef struct
{

	SDL_Window *gWindow;
	SDL_Renderer *gRenderer;

	int prelevel; //用于追踪关卡
	int level;	//关卡
	int mapmemory[5][5];//用于记忆当前的地图
	BOOL failmemory;//失败后重新生成地图的falg
	
	//游戏当前状态
	GameState gamestate;
	//游戏背景纹理
	LTexture bgLT;


	TTF_Font *gFont;	//字纹理
	//LTexture step;	//所用的步数
	LTexture levelLT;//游戏关卡LEVEL纹理
	LTexture stepLT;
	LTexture successLT[2]; //游戏胜利的提示 
	LTexture failLT[2];	//游戏失败的提示 
	LTexture numbersLT[10];//数字纹理
	int DigitW;	//个位数纹理宽度，取0-9纹理中最大值
	int DigitH;	//个位数纹理宽度，取0-9纹理中最大值

	LTexture btnLT;
	int nbuttonSprite;
	ImageButton restartBtn;	//重新开始按钮
	ImageButton quitBtn;	//退出按钮
	ImageButton nextBtn;	//下一关
	ImageButton lastBtn;	//上一关


	//Uint32 timeout;		//用于定时生成单词

	//灯泡
	LTexture bulbLT[TOTAL];
	Bulb bulbs[5][5];			//一共绘制5*5的灯泡
	int bulbsremained;//记录剩下的灯泡
	//睡觉小人
	LTexture boyLT[total];
	Boy boy;
	int nboySprite;//小孩睡觉的总帧数
	//明暗变化
	LTexture brightnessLT[TOTAL];
	Brightness brightness[5][5];	//爆炸序列帧	 
	int nlightSprite;		//灯管变暗总的帧数
	
	//用户点击的次数
	int step;
	void * pFocus;
	
	Mix_Music *gMusic;
	Mix_Chunk *wavturnon;
	Mix_Chunk *wavsnore;
	Mix_Chunk *wavbutton;

} TurnoffthelightApp;
extern TurnoffthelightApp theApp;


#endif

//Texture.c   
void freeLTexture(LTexture *ltexture);
void renderTexture(LTexture ltexture, int x, int y);
LTexture load_Number(int num);
BOOL LoadMedia();
void setDigitWH();

//Event.c
void postUserEvent(int code);
void RunApp();
void handleMouseEvent(Bulb * bulbs, SDL_Event* e);
void onKeyDown(int key);
BOOL GameOver();
//Draw.c
void renderApp();
void DrawBrightnessChange(int bulbx, int bulby);
void drawNum(int x, int y, int num);
void DrawToolBar();
void drawStep();


//Util.c
void MakeRect(SDL_Rect *rect, int x, int y, int w, int h);

//button.c
void scale_downBtn(ImageButton* pCtrl);
void onMouseMove(void * pCtrl);
void onLButtonUp(void* pCtrl);
void onLButtonDown(void* pCtrl);
void releaseBtn(ImageButton* pCtrl);
void scale_upBtn(ImageButton* pCtrl);
void scale_downBtn(ImageButton* pCtrl);
void CalcLayout();



//Bulb.c

void updateBulbs();
void Renewbulbs();
BOOL Out_of_range(int x, int y);
void Change_light_on_off(int x,int y);
void Setbulbsposition(int bulbx, int bulby, int x, int y);
void stirBrightnessChange(int bulbx, int bulby);
int Bulbremained();
void mapbulb();

