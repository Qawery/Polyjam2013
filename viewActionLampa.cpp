#include "viewActionLampa.h"


viewActionLampa::viewActionLampa(void)
{
	ID = 7;
}


viewActionLampa::~viewActionLampa(void)
{
}
void viewActionLampa::Init(viewGraphic *p_Graphic)
{
	viewActionBox::Init(p_Graphic);

	BasicTex = Graphic->LoadTexture("graphic/lampa.png");
	SetColor(1,1,1);
}

int viewActionLampa::Work(Uint32 time)
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
		SetPosition(startX - 150*sin((float)passedAnimTime/vAL_FALLTIME*M_PI_2), 
			startY - 70*sin((float)passedAnimTime/vAL_FALLTIME*M_PI),
			width, height);

		passedAnimTime += time;

		if(passedAnimTime > vAL_FALLTIME) 
		{
			step = 3;
			startW = width;
			startH = height;
			passedAnimTime = 0;
		}
		break;
	case 3:
		SetPosition(startX - 150, startY, 
			startW-0.1*startW*passedAnimTime/vAL_BREAK, 
			startH-0.1*startH*passedAnimTime/vAL_BREAK);

		passedAnimTime += time;
		if(passedAnimTime > vAL_BREAK)
		{
			passedAnimTime -= vAL_BREAK;
			sys->dzwiek(ID);
			step = 4;
			return 1;
		}
		break;
	case 4:
		SetPosition(startX - 150, startY - 60.0f*passedAnimTime/vAL_FALLAWAY, 
			startW- 0.1*startW -0.9*startW*passedAnimTime/vAL_FALLAWAY, 
			startH- 0.1*startH -0.9*startH*passedAnimTime/vAL_FALLAWAY);

		passedAnimTime += time;
		if(passedAnimTime > vAL_FALLAWAY)
		{
			passedAnimTime = 0;
			step = 5;
		}
		
	}

	return 0;
}