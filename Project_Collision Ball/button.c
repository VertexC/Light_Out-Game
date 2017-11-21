#include "Turnoffthelight.h"
/************************************************************************/
/*����ԭ�ͣ�void CalcLayout()											*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ���ȡbutton�Ŀ��					 			            */
/************************************************************************/

void CalcLayout()
{
	int x, y;
	int xmove, ymove;//x,y�����ϵ�ƫ��
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
/*����ԭ�ͣ�void scale_downBtn(ImageButton* pCtrl)						*/
/*�����������ťָ��pCtrl												*/
/*�� �� ֵ����						   									*/
/*�������ܣ����°�ť���ð�ť��״��С��90%								*/
/************************************************************************/
void scale_downBtn(ImageButton* pCtrl){

	int x, y, w, h;
	x = pCtrl->rect.x;
	y = pCtrl->rect.y;
	w = pCtrl->rect.w;
	h = pCtrl->rect.h;
	if (!(pCtrl==&theApp.lastBtn&&theApp.level==1))
	{
		//��ť��״��С��90%	
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
/*����ԭ�ͣ�void scale_upBtn(ImageButton* pCtrl)						*/
/*�����������ťָ��pCtrl												*/
/*�� �� ֵ����						   									*/
/*�������ܣ�ʹ��ť��״�ָ�����											*/
/************************************************************************/
void scale_upBtn(ImageButton* pCtrl){

	int x, y, w, h;
	x = pCtrl->rect.x;
	y = pCtrl->rect.y;
	w = pCtrl->rect.w;
	h = pCtrl->rect.h;

	//��ť��״�ָ�����
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
/*����ԭ�ͣ�void releaseBtn(ImageButton* pCtrl)							*/
/*�����������ťָ��pCtrl												*/
/*�� �� ֵ����						   									*/
/*�������ܣ��ͷŰ�ť���ð�ť��״�ָ�����								*/
/************************************************************************/
void releaseBtn(ImageButton* pCtrl){
	SDL_QuitEvent ev;
	//ť��״�ָ�����
	scale_upBtn(pCtrl);
	//����ͷŵ������¿�ʼ
	if (pCtrl == &theApp.restartBtn)
	{
		theApp.failmemory = TRUE;
		postUserEvent(evtStartGame);
	}
	//����ͷŵ����˳�	
	if (pCtrl == &theApp.quitBtn)
	{
		ev.type = SDL_QUIT;
		SDL_PushEvent((SDL_Event *)&ev);
	}
	//����ͷŵ�����һ��
	if (pCtrl == &theApp.nextBtn)
	{
		theApp.level++;
		theApp.failmemory = FALSE;
		postUserEvent(evtStartGame);
	}
	//����ͷŵ�����һ��
	if (pCtrl == &theApp.lastBtn)
	{
		if (theApp.level > 1){
			theApp.level--;
			postUserEvent(evtStartGame);
		}
		
	}
}

/************************************************************************/
/*����ԭ�ͣ�void onLButtonDown(void* pCtrl)								*/
/*���������������ָ��pCtrl												*/
/*�� �� ֵ����  														*/
/*�������ܣ��������������°�ť�¼�									*/
/************************************************************************/
void onLButtonDown(void* pCtrl) 
{

	if (!GameOver())
	{
		scale_downBtn((ImageButton *)pCtrl);
	}

}

/************************************************************************/
/*����ԭ�ͣ�void onLButtonUp(void* pCtrl)								*/
/*���������������ָ��pCtrl												*/
/*�� �� ֵ����  														*/
/*�������ܣ������������ͷ��¼�										*/
/************************************************************************/
void onLButtonUp(void* pCtrl)
{
	if (!pCtrl || GameOver())
		return;
	//���pCtrlָ��ť 
	releaseBtn((ImageButton *)pCtrl);
}

/************************************************************************/
/*����ԭ�ͣ�void onMouseMove(void* pCtrl)								*/
/*���������������ָ��pCtrl												*/
/*�� �� ֵ����  														*/
/*�������ܣ���������ƶ��¼�											*/
/************************************************************************/
void onMouseMove(void * pCtrl)
{
	void * pOld;
	if (GameOver())
		return;
	pOld = theApp.pFocus;
	//�������Ƴ���ť
	if (pOld && (!pCtrl))
	{
		scale_upBtn((ImageButton*)pOld);
		theApp.pFocus=NULL;
	}
}
/************************************************************************/
/*����ԭ�ͣ�int btnW()													*/
/*�����������															*/
/*�� �� ֵ��������ť����Ŀ��											*/
/*�������ܣ���ȡ������ť����Ŀ��										*/
/************************************************************************/
int btnW(){

	return theApp.btnLT.mWidth;
}

/************************************************************************/
/*����ԭ�ͣ�int btnH()													*/
/*�����������															*/
/*�� �� ֵ��������ť����ĸ߶�											*/
/*�������ܣ���ȡ������ť����ĸ߶�										*/
/************************************************************************/
int btnH(){

	return theApp.btnLT.mHeight / theApp.nbuttonSprite;
}

/************************************************************************/
/*����ԭ�ͣ�void * GetFocus()											*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ���ȡ���㲿����ָ��											*/
/************************************************************************/
void * GetFocus()
{
	return theApp.pFocus;
}

/************************************************************************/
/*����ԭ�ͣ�void * SetFocus(void * pCtrl)								*/
/*��������������͵�ָ��												*/
/*�� �� ֵ����															*/
/*�������ܣ��趨����ΪpCtrl 											*/
/************************************************************************/
void * SetFocus(void * pCtrl)
{
	theApp.pFocus = pCtrl;
	return pCtrl;
}

/************************************************************************/
/*����ԭ�ͣ�BOOL HitRectTest(int x, int y, SDL_Rect rect)				*/
/*������������޸ĵ�SDL_Rect��������x,������y�����w���߶�h				*/
/*�� �� ֵ������λ�ھ��������ڷ���TRUE�����򷵻�FALSE					*/
/*�������ܣ��ж����꣨x��y���Ƿ�λ�ھ���������							*/
/************************************************************************/
BOOL HitRectTest(int x, int y, SDL_Rect rect)
{
	return (x >= rect.x && y >= rect.y && x<rect.x + rect.w && y<rect.y + rect.h);
}

/************************************************************************/
/*����ԭ�ͣ�void* GetControlAt(int x,int y)								*/
/*���������������x,������y												*/
/*�� �� ֵ���������ڵĲ���						   						*/
/*�������ܣ���ȡ��Ļ����(x,y)���ڵİ�ť									*/
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
