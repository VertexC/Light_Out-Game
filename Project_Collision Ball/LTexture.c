#include"Turnoffthelight.h"



/************************************************************************/
/*�������ܣ�����·��path�ϵ�ͼƬ��Դ����������			 				*/
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
/*�������ܣ���ָ��λ�û�������						 					*/
/************************************************************************/
void renderTexture(LTexture ltexture, int x, int y) {

	SDL_Rect srcRect = { 0, 0, ltexture.mWidth, ltexture.mHeight }, destRect = { x, y, ltexture.mWidth, ltexture.mHeight };

	SDL_RenderCopy(theApp.gRenderer, ltexture.mTexture, &srcRect, &destRect);
}

/************************************************************************/
/*�������ܣ��ͷ�LTexture��Դ						 					*/
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
/*�������ܣ������ַ�������						 						*/
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
/*�������ܣ����������������壬��Ƶ��Դ								*/
/************************************************************************/
BOOL LoadMedia() {
	int i;
	SDL_Color textColor = { 255, 84, 0, 255 };

	//������Ϸ��������
	theApp.bgLT = load_image("./media/picture/background3.png");
	if (!theApp.bgLT.mTexture)
	{
		printf("Failed to load background.\n");
		return FALSE;
	}

	//�������� 
	theApp.gFont = TTF_OpenFont("./media/Arial.ttf", 16);
	if (theApp.gFont == NULL)
	{
		printf("Failed to load TTF.\n");
	}
	//���ص�������
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
	//���������仯����
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
	//����С�к�����
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
	//���ذ�ť����
	theApp.btnLT = load_image("./media/picture/button_4.png");
	if (!theApp.btnLT.mTexture)
	{
		printf("Failed to load gexplosion.\n");
		return FALSE;
	}
	theApp.nbuttonSprite = 4;
	//������������
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
	
	//������Ϸ������ʾ
	theApp.gFont = TTF_OpenFont("./media/Semitalic.ttf", 80);
	theApp.successLT[0] = load_TTF_text("Success", theApp.gFont);
	theApp.failLT[0] = load_TTF_text("Fail", theApp.gFont);
	
	theApp.gFont = TTF_OpenFont("./media/ingleby.ttf", 24);
	theApp.successLT[1] = load_TTF_text("Please press SPACE to next level or ESC to quit.", theApp.gFont);
	theApp.failLT[1] = load_TTF_text("Please press SPACE to restart or ESC to quit.", theApp.gFont);
	//������������
	theApp.gFont = TTF_OpenFont("./media/Digit.ttf", 24);
	for (i = 0; i<10; i++)
	{
		theApp.numbersLT[i] = load_Number(i);
	}
	setDigitWH();


	//������Ϸ�ȼ���ʾ
	theApp.levelLT = load_TTF_text("Level:", theApp.gFont);
	//����ʣ�ಽ����ʾ
	theApp.stepLT = load_TTF_text("Steps Left:", theApp.gFont);
	
	theApp.level = 1;
    //��ʼ������

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
/*����ԭ�ͣ�void setDigitWH()											*/
/*�����������															*/
/*�� �� ֵ����										   					*/
/*�������ܣ��趨��λ�������ȸ߶�						 				*/
/************************************************************************/
void setDigitWH(){
	int maxw = 0, maxh = 0, i;
	//��ȡ0-9ʮ�����������п����߶ȵ����ֵ
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
	//�趨��������Ϊ���ֵ
	theApp.DigitW = theApp.numbersLT[maxw].mWidth;
	theApp.DigitH = theApp.numbersLT[maxh].mHeight;
}