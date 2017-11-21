#include"Turnoffthelight.h"
void Renewboy(){
	int width;
	int height;
	width = theApp.boyLT[wake].mWidth;
	height = theApp.boyLT[wake].mHeight;
	MakeRect(&theApp.boy.rect, (SCREEN_WIDTH - width) / 2,18 , width, height);
}