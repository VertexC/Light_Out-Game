#include"Turnoffthelight.h"


/************************************************************************/
/*�������ܣ�ÿ����Ϸ��ʼǰ��ʼ������									*/
/************************************************************************/
void startGame() {
	theApp.boy.frame = 0;//��ʼ��֡
	mapbulb();//�������bulbs�ĵ�ͼ
	//���ű�������
	theApp.step = 0;//���ò���
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(theApp.gMusic, -1);
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();

	
}

/************************************************************************/
/*�������ܣ���SDL�¼������������Զ����¼�								*/
/************************************************************************/
void postUserEvent(int code)
{
	SDL_UserEvent ev;
	ev.type = SDL_USEREVENT;
	ev.code = code;
	ev.data1 = NULL;
	ev.data2 = NULL;

	SDL_PushEvent((SDL_Event*)&ev);
}

/************************************************************************/
/*�������ܣ������Զ�����û��¼�										*/
/************************************************************************/
void onUserEvent(SDL_UserEvent *pEvent) {

	switch (pEvent->code) {

	case evtStartGame:
		startGame();
		theApp.gamestate = sNewGame;
		break;

	case evtStopMusic:
		if (Mix_PausedMusic() == 1)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
		break;

	case evtGameWin:
		if (!GameOver())
		{
			theApp.gamestate = sGameWin;
			Mix_PauseMusic();
			theApp.failmemory = FALSE;
		}
		break;

	case evtGameFail:
		if (!GameOver())
		{
			Mix_PauseMusic();
			theApp.gamestate = sGameFail;
			theApp.failmemory = TRUE;
		}
		break;
	}

	
}

/************************************************************************/
/*�������ܣ��ж���Ϸ�Ƿ��Ѿ�����										*/
/************************************************************************/
BOOL GameOver(){
	if (theApp.gamestate == sGameFail || theApp.gamestate == sGameWin)
		return TRUE;
	return FALSE;

}


/*�������ܣ����ĺ��������ڴ�������Ϸ�еĸ����¼����簴�¸��ְ�����		*/
/************************************************************************/
void routeEvent(SDL_Event* event)
{
	SDL_QuitEvent ev;
	BOOL inside= TRUE;
	int  key;
	void *pNow;
	SDL_MouseButtonEvent* mb = (SDL_MouseButtonEvent*)event;
	SDL_MouseMotionEvent* mm = (SDL_MouseMotionEvent*)event;
	int i, j;
	if ((event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) && !(theApp.gamestate == sGameWin||theApp.gamestate == sGameFail))
	{
		switch (event->type){
		case SDL_MOUSEBUTTONDOWN:
			pNow = GetControlAt(mb->x, mb->y);
			if (!pNow) break;
			theApp.pFocus=pNow;
			if (mb->button == 1)
				onLButtonDown(pNow);
			break;
		case SDL_MOUSEBUTTONUP:
			pNow = GetControlAt(mm->x, mm->y);
			onLButtonUp(pNow);
			break;
		case SDL_MOUSEMOTION:
			pNow = GetControlAt(mm->x, mm->y);
			onMouseMove(pNow);
			break;
		}
		for (i = 0; i < 5; i++){
			for ( j = 0; j < 5; j++)
			{

			    //Mouse is outside the bulbs
				if (!insidebulb(i,j))
				{
					continue;
				}
				//Mouse is inside the bulbs
				else
				{
					//Set mouse over sprite
					switch (event->type)
					{
					case SDL_MOUSEMOTION:
						//����ڵ����ڣ�����������򷢹�
						//if (theApp.bulbs[i][j].light_on_off=TRUE)
						break;

					case SDL_MOUSEBUTTONDOWN:
						//��갴�£�������������
						Light_change(i,j);
						break;

					case SDL_MOUSEBUTTONUP:
						//button->mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
						break;
					}
				}

			}

		}
	}
	switch (event->type)
	{
	case SDL_KEYDOWN:
		key = event->key.keysym.sym;
		if (key == SDLK_ESCAPE)
		{//�˳���Ϸ
			ev.type = SDL_QUIT;
			SDL_PushEvent((SDL_Event*)&ev);
		}
		else if (key == SDLK_p)
		{//��ͣ����
			postUserEvent(evtStopMusic);
		}
		else
			onKeyDown(key);
		break;

	default:
		if (event->type >= SDL_USEREVENT && event->type < SDL_LASTEVENT)
			onUserEvent((SDL_UserEvent*)event);
		break;
	}
}
//�жϵ�ǰ����Ƿ��ڵ�����
BOOL insidebulb(int bulbx,int bulby){
	int x;
	int y;
	BOOL inside=TRUE;
	int light_on_off = theApp.bulbs[bulbx][bulby].light_on_off;
	//Mouse is left of the button
	SDL_GetMouseState(&x, &y);
	if (x < theApp.bulbs[bulbx][bulby].x)
	{
		inside = FALSE;
	}
	//Mouse is right of the button
	else if (x > theApp.bulbs[bulbx][bulby].x + theApp.bulbLT[light_on_off].mWidth)
	{
		inside = FALSE;
	}
	//Mouse above the button
	else if (y < theApp.bulbs[bulbx][bulby].y)
	{
		inside = FALSE;
	}
	//Mouse below the button
	else if (y > theApp.bulbs[bulbx][bulby].y + theApp.bulbLT[light_on_off].mHeight)
	{
		inside = FALSE;
	}
	return inside;

}
/************************************************************************/
/*�������ܣ�������Ϸ����												*/
/************************************************************************/
void onKeyDown(int key){
	if (theApp.gamestate == sGameWin && key == SDLK_SPACE)
	{//���سɹ����Ѷ�����
		theApp.level++;
		postUserEvent(evtStartGame);
	}
	else if (theApp.gamestate == sGameFail && key == SDLK_SPACE)
	{//��Ϸʧ�ܣ��ڱ������¿�ʼ
		postUserEvent(evtStartGame);
	}
}

/************************************************************************/
/*�������ܣ�������Ϸ����												*/
/************************************************************************/
void updateApp()
{


	//���¼Ʋ���Ϣ
	//���µ�����Ϣ  
	updateBulbs();


}

/************************************************************************/
/*�������ܣ���Ϸ����ܣ�������Ҵ������¼� �����ƽ���  					*/
/************************************************************************/
void RunApp()
{
	BOOL quit = 0;
	SDL_Event event;
	Renewbulbs();
	Renewboy();
	mapbulb();
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = TRUE;
				break;

			default:
				routeEvent(&event);
				break;
			}
		}
		//������Ϸ����
		updateApp();
		//������Ϸ����
		renderApp();
	}
}