#include"Turnoffthelight.h"


/************************************************************************/
/*函数功能：每局游戏开始前初始化数据									*/
/************************************************************************/
void startGame() {
	theApp.boy.frame = 0;//初始化帧
	mapbulb();//随机生成bulbs的地图
	//播放背景音乐
	theApp.step = 0;//重置步数
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(theApp.gMusic, -1);
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();

	
}

/************************************************************************/
/*函数功能：向SDL事件队列中推送自定义事件								*/
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
/*函数功能：处理自定义的用户事件										*/
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
/*函数功能：判断游戏是否已经结束										*/
/************************************************************************/
BOOL GameOver(){
	if (theApp.gamestate == sGameFail || theApp.gamestate == sGameWin)
		return TRUE;
	return FALSE;

}


/*函数功能：核心函数，用于处理在游戏中的各种事件（如按下各种按键）		*/
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
						//鼠标在灯泡内，灯泡如果亮则发光
						//if (theApp.bulbs[i][j].light_on_off=TRUE)
						break;

					case SDL_MOUSEBUTTONDOWN:
						//鼠标按下，触发灯泡亮暗
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
		{//退出游戏
			ev.type = SDL_QUIT;
			SDL_PushEvent((SDL_Event*)&ev);
		}
		else if (key == SDLK_p)
		{//暂停音乐
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
//判断当前鼠标是否在灯泡内
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
/*函数功能：更新游戏数据												*/
/************************************************************************/
void onKeyDown(int key){
	if (theApp.gamestate == sGameWin && key == SDLK_SPACE)
	{//闯关成功，难度增加
		theApp.level++;
		postUserEvent(evtStartGame);
	}
	else if (theApp.gamestate == sGameFail && key == SDLK_SPACE)
	{//游戏失败，在本关重新开始
		postUserEvent(evtStartGame);
	}
}

/************************************************************************/
/*函数功能：更新游戏数据												*/
/************************************************************************/
void updateApp()
{


	//更新计步信息
	//更新灯泡信息  
	updateBulbs();


}

/************************************************************************/
/*函数功能：游戏主框架，接受玩家触发的事件 ，绘制界面  					*/
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
		//更新游戏数据
		updateApp();
		//绘制游戏界面
		renderApp();
	}
}