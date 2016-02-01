#include "viewActionObraz.h"


viewActionObraz::viewActionObraz(void)
{
	ID = 4;
}


viewActionObraz::~viewActionObraz(void)
{
}
void viewActionObraz::Init(viewGraphic *p_Graphic)
{
	viewActionBox::Init(p_Graphic);

	texObr[0] = Graphic->LoadTexture("graphic/obraz.png");
	texObr[1] = Graphic->LoadTexture("graphic/obraz01.png");
	texObr[2] = Graphic->LoadTexture("graphic/obraz02.png");
	BasicTex = texObr[0];
	SetColor(1,1,1);
}

int viewActionObraz::Work(Uint32 time)
{
	viewActionBox::Work(time);

	switch(step)
	{
	case 1:
		SetPosition(startX + rand()%2 - 1, startY + rand()%2 - 1, width, height, rand()%3);
		if(passedFallTime > fallTime)
		{
			step = 2;
			passedAnimTime = 0;
		}
		break;
	case 2:
		SetPosition(startX + vAO_FLYR_1*sin((float)passedAnimTime/vAO_FLYTIME_1*M_PI_2), 
			startY + vAO_FLYR_1*cos((float)passedAnimTime/vAO_FLYTIME_1*M_PI_2)-vAO_FLYR_1, 
			width, height, 
			-(float)passedAnimTime/vAO_FLYTIME_1*90);
		passedAnimTime += time;
		if(passedAnimTime > vAO_FLYTIME_1)
		{
			step = 3;
			passedAnimTime = 0;
			BasicTex = texObr[1];
			SetPosition(x, y, 89, 104, 0);
		}
		break;
	case 3:
		SetPosition(startX + vAO_FLYR_1, 
			startY - vAO_FLYR_1 + vAO_DOWN*(float)passedAnimTime/vAO_FLYTIME_2, 
			width, height, 
			-90);
		passedAnimTime += time;
		if(passedAnimTime > vAO_FLYTIME_2)
		{
			step = 4;
			passedAnimTime = 0;
			sys->dzwiek(ID);
			BasicTex = texObr[2];
			SetPosition(x, y, 128, 98, 0);
			return 1;
		}
	}

	return 0;
}