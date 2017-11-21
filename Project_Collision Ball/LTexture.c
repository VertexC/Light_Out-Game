#include"Turnoffthelight.h"



/************************************************************************/
/*函数功能：加载路径path上的图片资源，生成纹理			 				*/
/************************************************************************/
LTexture load_image(char* path) {

	LTexture ltexture;

	SDL_Surface* loadedSurface = IMG_Load(path);

	ltexture.mTexture = NULL;
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s!SDL Error: %s\n", path, SDL_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		ltexture.mTexture = SDL_CreateTextureFromSurface(theApp.gRenderer, loadedSurface);

		if (ltexture.mTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		else {
			ltexture.mWidth = loadedSurface->w;
			ltexture.mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	return ltexture;
}

/************************************************************************/
/*函数功能：在指定位置绘制纹理						 					*/
/************************************************************************/
void renderTexture(LTexture ltexture, int x, int y) {

	SDL_Rect srcRect = { 0, 0, ltexture.mWidth, ltexture.mHeight }, destRect = { x, y, ltexture.mWidth, ltexture.mHeight };

	SDL_RenderCopy(theApp.gRenderer, ltexture.mTexture, &srcRect, &destRect);
}

/************************************************************************/
/*函数功能：释放LTexture资源						 					*/
/************************************************************************/
void freeLTexture(LTexture *ltexture) {

	if (ltexture->mTexture != NULL) {

		SDL_DestroyTexture(ltexture->mTexture);
		ltexture->mWidth = 0;
		ltexture->mHeight = 0;
		ltexture->mTexture = NULL;
	}
}

/************************************************************************/
/*函数功能：生成字符串纹理						 						*/
/************************************************************************/
LTexture load_TTF_text(char *text, TTF_Font* gFont) {

	SDL_Surface* textSurface;
	LTexture textTexture;
	SDL_Color color = { 240, 0, 0, 255 };

	textTexture.mTexture = NULL;

	textSurface = TTF_RenderText_Solid(gFont, text, color);

	if (textSurface != NULL)
	{
		textTexture.mTexture = SDL_CreateTextureFromSurface(theApp.gRenderer, textSurface);
		if (textTexture.mTexture == NULL)
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		else {
			textTexture.mWidth = textSurface->w;
			textTexture.mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	else
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());

	return textTexture;
}

/************************************************************************/
/*函数功能：加载所有纹理，字体，音频资源								*/
/************************************************************************/
BOOL LoadMedia() {
	int i;
	SDL_Color textColor = { 255, 84, 0, 255 };

	//加载游戏背景纹理
	theApp.bgLT = load_image("./media/picture/background3.png");
	if (!theApp.bgLT.mTexture)
	{
		printf("Failed to load background.\n");
		return FALSE;
	}

	//加载字体 
	theApp.gFont = TTF_OpenFont("./media/Arial.ttf", 16);
	if (theApp.gFont == NULL)
	{
		printf("Failed to load TTF.\n");
	}
	//加载灯泡纹理
	theApp.bulbLT[LIGHTON] = load_image("./media/picture/bulb_on_1.bmp");
	if (!theApp.bulbLT[LIGHTON].mTexture)
	{
		printf("Failed to load bomb.\n");
		return FALSE;
	}
	theApp.bulbLT[LIGHTOFF] = load_image("./media/picture/bulb_off_1.bmp");
	if (!theApp.bulbLT[LIGHTOFF].mTexture)
	{
		printf("Failed to load bomb.\n");
		return FALSE;
	}
	//加载明暗变化纹理
	theApp.brightnessLT[LIGHTOFF] = load_image("./media/picture/bulb_up_1.bmp");
	if (!theApp.brightnessLT[LIGHTOFF].mTexture)
	{
		printf("Failed to load gexplosion.\n");
		return FALSE;
	}
	theApp.brightnessLT[LIGHTON] = load_image("./media/picture/bulb_down_1.bmp");
	if (!theApp.brightnessLT[LIGHTON].mTexture)
	{
		printf("Failed to load gexplosion.\n");
		return FALSE;
	}
	theApp.nlightSprite = 5;
	//加载小男孩纹理
	theApp.boyLT[wake] = load_image("./media/picture/child_awake.png");
	if (!theApp.boyLT[wake].mTexture)
	{
		printf("Failed to load gexplosion.\n");
		return FALSE;
	}
	theApp.boyLT[littesleepy] = load_image("./media/picture/child_sleepy.png");
	if (!theApp.boyLT[littesleepy].mTexture)
	{
		printf("Failed to load gexplosion.\n");
		return FALSE;
	}
	theApp.boyLT[sleepy] = load_image("./media/picture/child_asleep.png");
	if (!theApp.boyLT[sleepy].mTexture)
	{
		printf("Failed to load gexplosion.\n");
		return FALSE;
	}
	theApp.boyLT[asleep] = load_image("./media/picture/child_zzzzzz.png");
	if (!theApp.boyLT[sleepy].mTexture)
	{
		printf("Failed to load gexplosion.\n");
		return FALSE;
	}
	theApp.nboySprite = 3;
	//加载按钮纹理
	theApp.btnLT = load_image("./media/picture/button_4.png");
	if (!theApp.btnLT.mTexture)
	{
		printf("Failed to load gexplosion.\n");
		return FALSE;
	}
	theApp.nbuttonSprite = 4;
	//加载音乐纹理
	theApp.gMusic = Mix_LoadMUS("./media/picture/backmusic.mp3");
	if (theApp.gMusic == NULL)
	{
		printf("Failed to load bgmusic music! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	theApp.wavturnon = Mix_LoadWAV("./media/picture/light.wav");
	if (theApp.wavturnon== NULL)
	{
		printf("Failed to load fire sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	theApp.wavsnore = Mix_LoadWAV("./media/picture/snore.wav");
	if (theApp.wavsnore == NULL)
	{
		printf("Failed to load bomb sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	theApp.wavbutton = Mix_LoadWAV("./media/picture/button.wav");
	if (theApp.wavbutton == NULL)
	{
		printf("Failed to load bomb sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	
	//加载游戏结束提示
	theApp.gFont = TTF_OpenFont("./media/Semitalic.ttf", 80);
	theApp.successLT[0] = load_TTF_text("Success", theApp.gFont);
	theApp.failLT[0] = load_TTF_text("Fail", theApp.gFont);
	
	theApp.gFont = TTF_OpenFont("./media/ingleby.ttf", 24);
	theApp.successLT[1] = load_TTF_text("Please press SPACE to next level or ESC to quit.", theApp.gFont);
	theApp.failLT[1] = load_TTF_text("Please press SPACE to restart or ESC to quit.", theApp.gFont);
	//加载数字纹理
	theApp.gFont = TTF_OpenFont("./media/Digit.ttf", 24);
	for (i = 0; i<10; i++)
	{
		theApp.numbersLT[i] = load_Number(i);
	}
	setDigitWH();


	//加载游戏等级提示
	theApp.levelLT = load_TTF_text("Level:", theApp.gFont);
	//加载剩余步数提示
	theApp.stepLT = load_TTF_text("Steps Left:", theApp.gFont);
	
	theApp.level = 1;
    //初始化灯泡

	theApp.failmemory = FALSE;
	CalcLayout();
	postUserEvent(evtStartGame);


	return TRUE;
}
LTexture load_Number(int num){

	char numText[10];
	SDL_Color color = { 255, 255, 255, 255 };
	sprintf(numText, "%d", num);
	return load_TTF_text(numText, theApp.gFont, color);
}
/************************************************************************/
/*函数原型：void setDigitWH()											*/
/*传入参数：无															*/
/*返 回 值：无										   					*/
/*函数功能：设定个位数纹理宽度高度						 				*/
/************************************************************************/
void setDigitWH(){
	int maxw = 0, maxh = 0, i;
	//获取0-9十个数字纹理中宽度与高度的最大值
	for (i = 1; i<10; i++)
	{
		if (theApp.numbersLT[i].mWidth>theApp.numbersLT[maxw].mWidth)
		{
			maxw = i;
		}
		if (theApp.numbersLT[i].mHeight>theApp.numbersLT[maxh].mHeight)
		{
			maxh = i;
		}
	}
	//设定数字纹理为最大值
	theApp.DigitW = theApp.numbersLT[maxw].mWidth;
	theApp.DigitH = theApp.numbersLT[maxh].mHeight;
}