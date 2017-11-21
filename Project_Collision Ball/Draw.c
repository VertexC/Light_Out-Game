#include"Turnoffthelight.h"

/************************************************************************/
/*函数功能：绘制游戏背景纹理							 				*/
/************************************************************************/
void DrawBackground() {

	SDL_Rect srcRect;
	SDL_Rect dstRect;
	MakeRect(&srcRect, 0, 0,SCREEN_WIDTH, SCREEN_HEIGHT);
	MakeRect(&dstRect, 200, 200, 200, 300);

	SDL_RenderCopy(theApp.gRenderer, theApp.bgLT.mTexture, NULL, &srcRect);

}


/************************************************************************/
/*函数功能：绘制所有灯泡										 		*/
/************************************************************************/
void DrawBulbs() {

	int i,j;
	int on_off;
	SDL_Rect srcRect;
	MakeRect(&srcRect, 0, 0, theApp.bulbLT[LIGHTON].mWidth, theApp.bulbLT[LIGHTON].mHeight);
	
	for (i = 0; i<5; i++)
	{
		for (j = 0; j < 5; j++){
			on_off = theApp.bulbs[i][j].light_on_off;
			SDL_RenderCopy(theApp.gRenderer, theApp.bulbLT[on_off].mTexture, &srcRect,&theApp.bulbs[i][j].rect );
		}
	
	}
}

/************************************************************************/
/*函数功能：绘制明暗变化纹理										 	*/
/************************************************************************/
void Drawthebrightness() {

	int  x, w, h;
	int i, j;
	int light_on_off;
	SDL_Rect srcRect;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++){
			light_on_off = theApp.bulbs[i][j].light_on_off;
			w = theApp.brightnessLT[light_on_off].mWidth / theApp.nlightSprite;
			h = theApp.brightnessLT[light_on_off].mHeight;
			if (theApp.brightness[i][j].valid == TRUE)
			{
				x = w*(theApp.brightness[i][j].frame/3);
				MakeRect(&srcRect, x, 0, w, h);
				SDL_RenderCopy(theApp.gRenderer, theApp.brightnessLT[light_on_off].mTexture, &srcRect, &theApp.bulbs[i][j].rect);
				if (++theApp.brightness[i][j].frame/3>4){
					theApp.brightness[i][j].valid = FALSE;
					theApp.brightness[i][j].frame = -1;
				}
			}
			else
			{
				continue;
			}
		}
	}
}
/************************************************************************/
/*函数功能：绘制小人*/
/************************************************************************/
void Drawtheboy(){
	int i, j;
	int boystate;
	int width;
	int height;
	int x;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	width = theApp.boyLT[asleep].mWidth/theApp.nboySprite;
	height = theApp.boyLT[asleep].mHeight;
	if (theApp.bulbsremained >= 12) boystate = wake;
	if (theApp.bulbsremained < 12&&theApp.bulbsremained >= 6) boystate = littesleepy;
	if (theApp.bulbsremained < 6) boystate = sleepy;
	if (theApp.bulbsremained ==0) boystate = asleep;
	//MakeRect(&dstRect, (SCREEN_WIDTH - theApp.boyLT[boystate].mWidth) / 2, 0, theApp.boyLT[boystate].mWidth, theApp.boyLT[boystate].mHeight);
	if (boystate == asleep){
		x = (theApp.boy.frame/10)*width;
		MakeRect(&srcRect, x, 0, width, height);
		SDL_RenderCopy(theApp.gRenderer, theApp.boyLT[boystate].mTexture, &srcRect, &theApp.boy.rect);
		if (++theApp.boy.frame/10>=theApp.nboySprite)
		{
			theApp.boy.frame = 0;
		}
	}
	else{
		MakeRect(&srcRect, 0, 0, theApp.boyLT[boystate].mWidth, theApp.boyLT[boystate].mHeight);
		SDL_RenderCopy(theApp.gRenderer, theApp.boyLT[boystate].mTexture, NULL, &theApp.boy.rect);
	}
}
/************************************************************************/
/*函数功能：绘制游戏成功或者失败的提示语*/
/************************************************************************/
void DrawTips(){

	if (theApp.gamestate == sGameWin)
	{
		//如果游戏成功，绘制成功提示 
		renderTexture(theApp.successLT[0], SCREEN_WIDTH / 2 - theApp.successLT[0].mWidth / 2, SCREEN_HEIGHT / 4);
		renderTexture(theApp.successLT[1], SCREEN_WIDTH / 2 - theApp.successLT[1].mWidth / 2, SCREEN_HEIGHT / 4 + theApp.successLT[0].mHeight * 2);

	}
	else if (theApp.gamestate == sGameFail)
	{ //如果游戏失败，绘制失败提示 
		renderTexture(theApp.failLT[0], SCREEN_WIDTH / 2 - theApp.failLT[0].mWidth / 2, SCREEN_HEIGHT / 4);
		renderTexture(theApp.failLT[1], SCREEN_WIDTH / 2 - theApp.failLT[1].mWidth / 2, SCREEN_HEIGHT / 4 + theApp.failLT[0].mHeight * 2);
	}
}
/************************************************************************/
/*函数原型：void drawLevel()											*/
/*传入参数：无															*/
/*返 回 值：无															*/
/*函数功能：绘制游戏难度等级											*/
/************************************************************************/
void drawLevel(){

	renderTexture(theApp.levelLT,10,100/2-theApp.levelLT.mHeight/2);
	drawNum(theApp.levelLT.mWidth + 15 + theApp.DigitW,100 / 2 , theApp.level );
}
void drawStep(){

	renderTexture(theApp.stepLT, 10, 100 / 2 - theApp.levelLT.mHeight / 2+20);
	drawNum(theApp.stepLT.mWidth + 15 + theApp.DigitW, 100 / 2 + 20, (15-theApp.step));
}
/************************************************************************/
/*函数原型：void drawNum(int x,int y,int num)							*/
/*传入参数：x坐标，y坐标，数字num(0-999)								*/
/*返 回 值：无															*/
/*函数功能：以（x,y）为中心绘制数字										*/
/************************************************************************/
void drawNum(int x, int y, int num){

	int i = 0, len = 0, width = 0;
	int numbers[3] = { 0 };

	for (i = 0; i<3; i++)
	{
		numbers[i] = -1;
	}
	//将num的各位数字存入numbers数组，并计算num组合纹理的总长度
	if (num == 0)
	{
		numbers[0] = 0;
		width = theApp.DigitW;
	}

	i = 0;
	while (num>0)
	{
		numbers[i] = num % 10;
		width += theApp.DigitW;//每位数字大小一致，避免倒计时的抖动现象
		num /= 10;
		i++;
	}
	//逐位绘制数字
	for (i = 2; i >= 0; i--)
	{
		if (numbers[i] >= 0)
		{
			renderTexture(theApp.numbersLT[numbers[i]], x - width / 2 + len, y - theApp.DigitH / 2);
			len += theApp.DigitW;
		}
	}
}

/************************************************************************/
/*函数原型：void drawBtn(ImageButton* btn)								*/
/*传入参数：按钮指针													*/
/*返 回 值：无															*/
/*函数功能：绘制按钮btn													*/
/************************************************************************/
void drawBtn(ImageButton* btn){

	int x = 0, y;
	int w = btnW(), h = btnH();

	SDL_Rect srcRect;
	//根据按钮选择相应的纹理
	if (btn == &theApp.restartBtn)
		y = 0;//重新开始纹理
	else if (btn == &theApp.quitBtn)
		y = btnH();//退出纹理
	else if (btn == &theApp.lastBtn)
		y = btnH() * 2; //下一关纹理
	else if (btn == &theApp.nextBtn)
		y = btnH() * 3; //上一关纹理


    MakeRect(&srcRect, x, y, w, h);
	SDL_RenderCopy(theApp.gRenderer, theApp.btnLT.mTexture, &srcRect, &btn->rect);

}
/************************************************************************/
/*函数原型：void DrawToolBar()											*/
/*传入参数：无															*/
/*返 回 值：无															*/
/*函数功能：绘制屏幕工具栏								 			*/
/************************************************************************/
void DrawToolBar(){

	//绘制难度等级

	drawStep();
	drawLevel();
	
	//绘制按钮
	drawBtn(&theApp.restartBtn);
	drawBtn(&theApp.quitBtn);
	drawBtn(&theApp.lastBtn);
	drawBtn(&theApp.nextBtn);


}
/************************************************************************/
/*函数功能：绘制游戏所有部件											*/
/************************************************************************/
void renderApp() {

	SDL_SetRenderDrawColor(theApp.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(theApp.gRenderer);
	DrawBackground();
	Drawtheboy();
	DrawBulbs();
	Drawthebrightness();
	DrawToolBar();
	DrawTips();
    SDL_RenderPresent(theApp.gRenderer);


}

