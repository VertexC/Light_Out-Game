#include "Turnoffthelight.h"
/************************************************************************/
/*函数功能：初始化灯泡的信息
/************************************************************************/
void Renewbulbs(){
	int i, j;
	int width, height;
	int movex, movey;
	width = theApp.bulbLT[LIGHTON].mWidth;
	height = theApp.bulbLT[LIGHTON].mHeight;
	movex = (SCREEN_WIDTH - 5 * width) / 2;
	movey = SCREEN_HEIGHT-5*theApp.bulbLT[LIGHTON].mHeight-5;
	for (i = 0; i < 5; i++){
		for (j = 0; j < 5; j++){
			theApp.bulbs[i][j].light_on_off = LIGHTON;
			MakeRect(&theApp.bulbs[i][j].rect, j * width+movex, i *height+movey, width, height);
			Setbulbsposition(i, j, j*width + movex, i*height + movey);
			theApp.brightness[i][j].valid = FALSE;
			theApp.brightness[i][j].frame = 0;
		}
	}

}

/************************************************************************/
/*函数功能：随机生成灯泡的地图
/************************************************************************/
void mapbulb(){
	int i, j;
	int light_on_off;
	int mapdesigned[4][5][5] = { 
	{ 0, 0, 0, 0, 0,
	0, 0, 1, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 1, 0, 0,
	0, 0, 0, 0, 0
	},
	{ 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 1,
	0, 0, 0, 1, 1,
	0, 0, 0, 0, 1
	},
	{ 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0,
	1, 1, 1, 0, 1,
	0, 1, 0, 1, 1,
	0, 0, 0, 0, 1
	},
	{ 0, 0, 0, 0, 0,
	1, 1, 0, 1, 1,
	0, 0, 1, 0, 1,
	1, 0, 1, 0, 1,
	0, 0, 1, 0, 0
	}
	};
	srand(time(0));
	if (theApp.level>=1&&theApp.level<=4)
	{
		if (theApp.failmemory == TRUE)//如果是失败后重新启动的游戏，那么不重新生成地图
		{
			for (i = 0; i < 5; i++)
			for (j = 0; j < 5; j++){
				theApp.bulbs[i][j].light_on_off = theApp.mapmemory[i][j];
			}

		}
		else{
			for (i = 0; i < 5; i++)
			for (j = 0; j < 5; j++){
				light_on_off = rand() % 2;
				theApp.bulbs[i][j].light_on_off = mapdesigned[theApp.level-1][i][j];
				theApp.mapmemory[i][j] = mapdesigned[theApp.level - 1][i][j];
			}
		}
	}
	else{
		if (theApp.failmemory == TRUE)//如果是失败后重新启动的游戏，那么不重新生成地图
		{
			for (i = 0; i < 5; i++)
			for (j = 0; j < 5; j++){
				theApp.bulbs[i][j].light_on_off = theApp.mapmemory[i][j];
			}

		}
		else{
			for (i = 0; i < 5; i++)
			for (j = 0; j < 5; j++){
				light_on_off = rand() % 2;
				theApp.bulbs[i][j].light_on_off = light_on_off;
				theApp.mapmemory[i][j] = light_on_off;
			}
		}
	}
	
	

}
//设置每个灯泡的坐标
void Setbulbsposition(int bulbx, int bulby,int x,int y){
	theApp.bulbs[bulbx][bulby].x = x;
	theApp.bulbs[bulbx][bulby].y = y;
}
/************************************************************************/
/*函数功能：改变灯泡的亮度
/*参数：被鼠标点击灯泡在矩阵中的坐标
/*
/************************************************************************/
void Light_change(int bulb_clicked_x,int bulb_clicked_y) {

	//上灯泡
	int bulb_up_x = bulb_clicked_x ;
	int bulb_up_y = bulb_clicked_y - 1;
	//下灯泡
	int bulb_down_x = bulb_clicked_x;
	int bulb_down_y = bulb_clicked_y + 1;
	//左灯泡
	int bulb_left_x = bulb_clicked_x - 1;
	int bulb_left_y = bulb_clicked_y;
	//右灯泡
	int bulb_right_x = bulb_clicked_x + 1;
	int bulb_right_y = bulb_clicked_y;
	//改变相应灯泡的明暗

	if (!Out_of_range(bulb_clicked_x,bulb_clicked_y))
	{
		if (++theApp.step > 14){
			postUserEvent(evtGameFail);
		}
		stirBrightnessChange(bulb_clicked_x, bulb_clicked_y);
		Change_light_on_off(bulb_clicked_x, bulb_clicked_y);
	
	}
	if (!Out_of_range(bulb_down_x, bulb_down_y))
	{
		stirBrightnessChange(bulb_down_x, bulb_down_y);
		Change_light_on_off(bulb_down_x, bulb_down_y);
	}
	if (!Out_of_range(bulb_up_x, bulb_up_y))
	{
		stirBrightnessChange(bulb_up_x, bulb_up_y);
		Change_light_on_off(bulb_up_x, bulb_up_y);
	}
	if (!Out_of_range(bulb_left_x, bulb_left_y))
	{
		stirBrightnessChange(bulb_left_x, bulb_left_y);
		Change_light_on_off(bulb_left_x, bulb_left_y);
	}
	if (!Out_of_range(bulb_right_x, bulb_right_y))
	{
		stirBrightnessChange(bulb_right_x, bulb_right_y);
		Change_light_on_off(bulb_right_x, bulb_right_y);
	}

}
/************************************************************************/
/*函数功能：判断要变化的灯泡是否存在
/*参数：灯泡在矩阵中的坐标
/*
/************************************************************************/
BOOL Out_of_range(int x, int y){
	if (x<0||x>4)
	{
		return TRUE;
	}
	else if (y<0||y>4)
	{
		return TRUE;
	}
	else return FALSE;
		 
	
}
/************************************************************************/
/*函数功能：改变亮度变化中的valid
/*参数：灯泡在矩阵中的坐标
/*
/************************************************************************/
void stirBrightnessChange(int bulbx,int bulby){
	theApp.brightness[bulbx][bulby].valid = TRUE;

}
/************************************************************************/
/*函数功能：改变灯泡的开关
/*参数：灯泡在矩阵中的坐标
/*
/************************************************************************/
void Change_light_on_off(int x,int y){
	if (theApp.bulbs[x][y].light_on_off==LIGHTON)
	{
		theApp.bulbs[x][y].light_on_off = LIGHTOFF;
	
	}
	else
	{
		theApp.bulbs[x][y].light_on_off = LIGHTON;
		Mix_PlayChannel(-1, theApp.wavturnon, 0);
	}

}
/************************************************************************/
/*函数功能：计算剩余的灯泡											*/
/************************************************************************/
 int Bulbremained(){
	int i, j;
	int number=0;
	for (i = 0; i < 5; i++){
		for (j = 0; j < 5; j++){
			if (theApp.bulbs[i][j].light_on_off == LIGHTON)
				number++;
		}
	}
	if (number==0)
	{
		postUserEvent(evtGameWin);
	}
	return number;
}
/************************************************************************/
/*函数功能：更新所有炮弹的信息											*/
/************************************************************************/

void updateBulbs() {
	
	theApp.bulbsremained = Bulbremained();

}

