#include"Turnoffthelight.h"

/************************************************************************/
/*�������ܣ�������Ϸ��������							 				*/
/************************************************************************/
void DrawBackground() {

	SDL_Rect srcRect;
	SDL_Rect dstRect;
	MakeRect(&srcRect, 0, 0,SCREEN_WIDTH, SCREEN_HEIGHT);
	MakeRect(&dstRect, 200, 200, 200, 300);

	SDL_RenderCopy(theApp.gRenderer, theApp.bgLT.mTexture, NULL, &srcRect);

}


/************************************************************************/
/*�������ܣ��������е���										 		*/
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
/*�������ܣ����������仯����										 	*/
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
/*�������ܣ�����С��*/
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
/*�������ܣ�������Ϸ�ɹ�����ʧ�ܵ���ʾ��*/
/************************************************************************/
void DrawTips(){

	if (theApp.gamestate == sGameWin)
	{
		//�����Ϸ�ɹ������Ƴɹ���ʾ 
		renderTexture(theApp.successLT[0], SCREEN_WIDTH / 2 - theApp.successLT[0].mWidth / 2, SCREEN_HEIGHT / 4);
		renderTexture(theApp.successLT[1], SCREEN_WIDTH / 2 - theApp.successLT[1].mWidth / 2, SCREEN_HEIGHT / 4 + theApp.successLT[0].mHeight * 2);

	}
	else if (theApp.gamestate == sGameFail)
	{ //�����Ϸʧ�ܣ�����ʧ����ʾ 
		renderTexture(theApp.failLT[0], SCREEN_WIDTH / 2 - theApp.failLT[0].mWidth / 2, SCREEN_HEIGHT / 4);
		renderTexture(theApp.failLT[1], SCREEN_WIDTH / 2 - theApp.failLT[1].mWidth / 2, SCREEN_HEIGHT / 4 + theApp.failLT[0].mHeight * 2);
	}
}
/************************************************************************/
/*����ԭ�ͣ�void drawLevel()											*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ�������Ϸ�Ѷȵȼ�											*/
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
/*����ԭ�ͣ�void drawNum(int x,int y,int num)							*/
/*���������x���꣬y���꣬����num(0-999)								*/
/*�� �� ֵ����															*/
/*�������ܣ��ԣ�x,y��Ϊ���Ļ�������										*/
/************************************************************************/
void drawNum(int x, int y, int num){

	int i = 0, len = 0, width = 0;
	int numbers[3] = { 0 };

	for (i = 0; i<3; i++)
	{
		numbers[i] = -1;
	}
	//��num�ĸ�λ���ִ���numbers���飬������num���������ܳ���
	if (num == 0)
	{
		numbers[0] = 0;
		width = theApp.DigitW;
	}

	i = 0;
	while (num>0)
	{
		numbers[i] = num % 10;
		width += theApp.DigitW;//ÿλ���ִ�Сһ�£����⵹��ʱ�Ķ�������
		num /= 10;
		i++;
	}
	//��λ��������
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
/*����ԭ�ͣ�void drawBtn(ImageButton* btn)								*/
/*�����������ťָ��													*/
/*�� �� ֵ����															*/
/*�������ܣ����ư�ťbtn													*/
/************************************************************************/
void drawBtn(ImageButton* btn){

	int x = 0, y;
	int w = btnW(), h = btnH();

	SDL_Rect srcRect;
	//���ݰ�ťѡ����Ӧ������
	if (btn == &theApp.restartBtn)
		y = 0;//���¿�ʼ����
	else if (btn == &theApp.quitBtn)
		y = btnH();//�˳�����
	else if (btn == &theApp.lastBtn)
		y = btnH() * 2; //��һ������
	else if (btn == &theApp.nextBtn)
		y = btnH() * 3; //��һ������


    MakeRect(&srcRect, x, y, w, h);
	SDL_RenderCopy(theApp.gRenderer, theApp.btnLT.mTexture, &srcRect, &btn->rect);

}
/************************************************************************/
/*����ԭ�ͣ�void DrawToolBar()											*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ�������Ļ������								 			*/
/************************************************************************/
void DrawToolBar(){

	//�����Ѷȵȼ�

	drawStep();
	drawLevel();
	
	//���ư�ť
	drawBtn(&theApp.restartBtn);
	drawBtn(&theApp.quitBtn);
	drawBtn(&theApp.lastBtn);
	drawBtn(&theApp.nextBtn);


}
/************************************************************************/
/*�������ܣ�������Ϸ���в���											*/
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

