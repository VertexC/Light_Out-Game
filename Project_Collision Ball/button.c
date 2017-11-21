#include "Turnoffthelight.h"
/************************************************************************/
/*函数原型：void CalcLayout()											*/
/*传入参数：无															*/
/*返 回 值：无															*/
/*函数功能：获取button的宽高					 			            */
/************************************************************************/

void CalcLayout()
{
	int x, y;
	int xmove, ymove;//x,y方向上的偏移
	//restart button
	xmove = 660;
	ymove = 200;
	x =  xmove;
	y =  ymove;
	MakeRect(&theApp.restartBtn.rect, x, y, btnW(), btnH());

	//quit button
	y = ymove + btnH() * 1 + 20;
	MakeRect(&theApp.quitBtn.rect, x, y, btnW(), btnH());


	//last button
	y = ymove + btnH() * 2 + 40;
	MakeRect(&theApp.lastBtn.rect, x, y, btnW() , btnH());

	//next button
	y = ymove + btnH() * 3 + 60;
	MakeRect(&theApp.nextBtn.rect, x, y, btnW() , btnH());
}
/************************************************************************/
/*函数原型：void scale_downBtn(ImageButton* pCtrl)						*/
/*传入参数：按钮指针pCtrl												*/
/*返 回 值：无						   									*/
/*函数功能：按下按钮，该按钮形状缩小到90%								*/
/************************************************************************/
void scale_downBtn(ImageButton* pCtrl){

	int x, y, w, h;
	x = pCtrl->rect.x;
	y = pCtrl->rect.y;
	w = pCtrl->rect.w;
	h = pCtrl->rect.h;
	if (!(pCtrl==&theApp.lastBtn&&theApp.level==1))
	{
		//按钮形状缩小到90%	
		if (pCtrl->data == btnExposed)
		{
			x = x + w / 18;
			y = y + h / 18;
			w = w * 9 / 10;
			h = h * 9 / 10;
			MakeRect(&pCtrl->rect, x, y, w, h);

			pCtrl->data = btnDown;
		}
	}
	
}

/************************************************************************/
/*函数原型：void scale_upBtn(ImageButton* pCtrl)						*/
/*传入参数：按钮指针pCtrl												*/
/*返 回 值：无						   									*/
/*函数功能：使按钮形状恢复正常											*/
/************************************************************************/
void scale_upBtn(ImageButton* pCtrl){

	int x, y, w, h;
	x = pCtrl->rect.x;
	y = pCtrl->rect.y;
	w = pCtrl->rect.w;
	h = pCtrl->rect.h;

	//按钮形状恢复正常
	if (pCtrl->data == btnDown)
	{
		w = w * 10 / 9;
		h = h * 10 / 9;
		x = x - w / 18;
		y = y - h / 18;
		
		MakeRect(&pCtrl->rect, x, y, w, h);

		pCtrl->data = btnExposed;
	}
}

/************************************************************************/
/*函数原型：void releaseBtn(ImageButton* pCtrl)							*/
/*传入参数：按钮指针pCtrl												*/
/*返 回 值：无						   									*/
/*函数功能：释放按钮，该按钮形状恢复正常								*/
/************************************************************************/
void releaseBtn(ImageButton* pCtrl){
	SDL_QuitEvent ev;
	//钮形状恢复正常
	scale_upBtn(pCtrl);
	//如果释放的是重新开始
	if (pCtrl == &theApp.restartBtn)
	{
		theApp.failmemory = TRUE;
		postUserEvent(evtStartGame);
	}
	//如果释放的是退出	
	if (pCtrl == &theApp.quitBtn)
	{
		ev.type = SDL_QUIT;
		SDL_PushEvent((SDL_Event *)&ev);
	}
	//如果释放的是下一关
	if (pCtrl == &theApp.nextBtn)
	{
		theApp.level++;
		theApp.failmemory = FALSE;
		postUserEvent(evtStartGame);
	}
	//如果释放的是上一关
	if (pCtrl == &theApp.lastBtn)
	{
		if (theApp.level > 1){
			theApp.level--;
			postUserEvent(evtStartGame);
		}
		
	}
}

/************************************************************************/
/*函数原型：void onLButtonDown(void* pCtrl)								*/
/*传入参数：空类型指针pCtrl												*/
/*返 回 值：无  														*/
/*函数功能：处理鼠标左键按下按钮事件									*/
/************************************************************************/
void onLButtonDown(void* pCtrl) 
{

	if (!GameOver())
	{
		scale_downBtn((ImageButton *)pCtrl);
	}

}

/************************************************************************/
/*函数原型：void onLButtonUp(void* pCtrl)								*/
/*传入参数：空类型指针pCtrl												*/
/*返 回 值：无  														*/
/*函数功能：处理鼠标左键释放事件										*/
/************************************************************************/
void onLButtonUp(void* pCtrl)
{
	if (!pCtrl || GameOver())
		return;
	//如果pCtrl指向按钮 
	releaseBtn((ImageButton *)pCtrl);
}

/************************************************************************/
/*函数原型：void onMouseMove(void* pCtrl)								*/
/*传入参数：空类型指针pCtrl												*/
/*返 回 值：无  														*/
/*函数功能：处理鼠标移动事件											*/
/************************************************************************/
void onMouseMove(void * pCtrl)
{
	void * pOld;
	if (GameOver())
		return;
	pOld = theApp.pFocus;
	//如果鼠标移出按钮
	if (pOld && (!pCtrl))
	{
		scale_upBtn((ImageButton*)pOld);
		theApp.pFocus=NULL;
	}
}
/************************************************************************/
/*函数原型：int btnW()													*/
/*传入参数：无															*/
/*返 回 值：单个按钮纹理的宽度											*/
/*函数功能：获取单个按钮纹理的宽度										*/
/************************************************************************/
int btnW(){

	return theApp.btnLT.mWidth;
}

/************************************************************************/
/*函数原型：int btnH()													*/
/*传入参数：无															*/
/*返 回 值：单个按钮纹理的高度											*/
/*函数功能：获取单个按钮纹理的高度										*/
/************************************************************************/
int btnH(){

	return theApp.btnLT.mHeight / theApp.nbuttonSprite;
}

/************************************************************************/
/*函数原型：void * GetFocus()											*/
/*传入参数：无															*/
/*返 回 值：无															*/
/*函数功能：获取焦点部件的指针											*/
/************************************************************************/
void * GetFocus()
{
	return theApp.pFocus;
}

/************************************************************************/
/*函数原型：void * SetFocus(void * pCtrl)								*/
/*传入参数：空类型的指针												*/
/*返 回 值：无															*/
/*函数功能：设定焦点为pCtrl 											*/
/************************************************************************/
void * SetFocus(void * pCtrl)
{
	theApp.pFocus = pCtrl;
	return pCtrl;
}

/************************************************************************/
/*函数原型：BOOL HitRectTest(int x, int y, SDL_Rect rect)				*/
/*传入参数：待修改的SDL_Rect，横坐标x,纵坐标y，宽度w，高度h				*/
/*返 回 值：坐标位于矩形区域内返回TRUE，否则返回FALSE					*/
/*函数功能：判断坐标（x，y）是否位于矩形区域内							*/
/************************************************************************/
BOOL HitRectTest(int x, int y, SDL_Rect rect)
{
	return (x >= rect.x && y >= rect.y && x<rect.x + rect.w && y<rect.y + rect.h);
}

/************************************************************************/
/*函数原型：void* GetControlAt(int x,int y)								*/
/*传入参数：横坐标x,纵坐标y												*/
/*返 回 值：坐标所在的部件						   						*/
/*函数功能：获取屏幕坐标(x,y)所在的按钮									*/
/************************************************************************/
void* GetControlAt(int x, int y){

	void* pFocus = NULL;

	if (HitRectTest(x, y, theApp.restartBtn.rect))
		pFocus = &theApp.restartBtn;

	if (HitRectTest(x, y, theApp.quitBtn.rect))
		pFocus = &theApp.quitBtn;

	if (HitRectTest(x, y, theApp.lastBtn.rect))
		pFocus = &theApp.lastBtn;

	if (HitRectTest(x, y, theApp.nextBtn.rect))
		pFocus = &theApp.nextBtn;

	return pFocus;
}
