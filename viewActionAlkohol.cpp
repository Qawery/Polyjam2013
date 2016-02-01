#include "viewActionAlkohol.h"


viewActionAlkohol::viewActionAlkohol(void)
{
	ID = 1;
}


viewActionAlkohol::~viewActionAlkohol(void)
{

}
void viewActionAlkohol::Init(viewGraphic *p_Graphic)
{
	viewActionBox::Init(p_Graphic);

	BasicTex = Graphic->LoadTexture("graphic/alko.png");
	SetColor(1,1,1);
}

int viewActionAlkohol::Work(Uint32 time)
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
		SetPosition(startX, startY + passedAnimTime*0.2, width, height, -(float)passedAnimTime/(float)vAA_FALLTIME*90);
		passedAnimTime += time;
		if(passedAnimTime > vAA_FALLTIME)
		{
			step = 3;
			startY += vAA_FALLTIME*0.2;
			passedAnimTime = 0;
		}
		break;
	case 3:
		SetPosition(startX, startY, width, height, -90);
		passedAnimTime += time;
		if(passedAnimTime > vAA_WAITTIME)
		{
			step = 4;
			passedAnimTime = 0;
		}
		break;
	case 4:
		SetPosition(startX + 580*(float)passedAnimTime/vAA_BOOKSTIME, startY - 100*(float)passedAnimTime/vAA_BOOKSTIME, width, height, -90);
		passedAnimTime += time;
		if(passedAnimTime > vAA_BOOKSTIME)
		{
			step = 5;
			SetPosition(1000, 1000, width, height, -90);
			passedAnimTime = 0;
			return 1;
		}

		break;;
	}

	return 0;
}