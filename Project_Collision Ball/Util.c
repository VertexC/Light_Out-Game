#include"Turnoffthelight.h"
/************************************************************************/
/*函数功能：设定入参SDL_Rect的坐标与宽高								*/
/************************************************************************/
void MakeRect(SDL_Rect *rect, int x, int y, int w, int h) {

	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

/************************************************************************/
/*函数功能：AABB包围盒碰撞检测											*/
/************************************************************************/
/*BOOL IsConflict(SDL_Rect rect1, SDL_Rect rect2) {

	if (rect1.x + rect1.w<rect2.x)
		return FALSE;
	if (rect1.x>rect2.x + rect2.w)
		return FALSE;
	if (rect1.y + rect1.h<rect2.y)
		return FALSE;
	if (rect1.y>rect2.y + rect2.h)
		return FALSE;

	return TRUE;

}*/