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
	sGameFail,   // ��Ϸʧ��
	sGameWin,	 // ��Ϸʤ��
} GameState;

typedef struct {

	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
}LTexture;
enum{
	LIGHTOFF = 0 ,//�ƹ�
	LIGHTON  ,//�ƿ�
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
	int x;//����Ļ�ϵ�����
	int y;
	int light_on_off;//���ڼ������Ƿ���
	SDL_Rect rect;
}Bulb; 
typedef struct{
	int frame;//֡
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

	int prelevel; //����׷�ٹؿ�
	int level;	//�ؿ�
	int mapmemory[5][5];//���ڼ��䵱ǰ�ĵ�ͼ
	BOOL failmemory;//ʧ�ܺ��������ɵ�ͼ��falg
	
	//��Ϸ��ǰ״̬
	GameState gamestate;
	//��Ϸ��������
	LTexture bgLT;


	TTF_Font *gFont;	//������
	//LTexture step;	//���õĲ���
	LTexture levelLT;//��Ϸ�ؿ�LEVEL����
	LTexture stepLT;
	LTexture successLT[2]; //��Ϸʤ������ʾ 
	LTexture failLT[2];	//��Ϸʧ�ܵ���ʾ 
	LTexture numbersLT[10];//��������
	int DigitW;	//��λ�������ȣ�ȡ0-9���������ֵ
	int DigitH;	//��λ�������ȣ�ȡ0-9���������ֵ

	LTexture btnLT;
	int nbuttonSprite;
	ImageButton restartBtn;	//���¿�ʼ��ť
	ImageButton quitBtn;	//�˳���ť
	ImageButton nextBtn;	//��һ��
	ImageButton lastBtn;	//��һ��


	//Uint32 timeout;		//���ڶ�ʱ���ɵ���

	//����
	LTexture bulbLT[TOTAL];
	Bulb bulbs[5][5];			//һ������5*5�ĵ���
	int bulbsremained;//��¼ʣ�µĵ���
	//˯��С��
	LTexture boyLT[total];
	Boy boy;
	int nboySprite;//С��˯������֡��
	//�����仯
	LTexture brightnessLT[TOTAL];
	Brightness brightness[5][5];	//��ը����֡	 
	int nlightSprite;		//�ƹܱ䰵�ܵ�֡��
	
	//�û�����Ĵ���
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

