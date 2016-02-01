#include "viewActionWazon.h"


viewActionWazon::viewActionWazon(void)
{
	ID = 6;
}


viewActionWazon::~viewActionWazon(void)
{
	if(texNormal) Graphic->FreeTexture(texNormal);
	if(texKaput) Graphic->FreeTexture(texKaput);
}

void viewActionWazon::Init(viewGraphic *p_Graphic)
{
	viewActionBox::Init(p_Graphic);

	texNormal = Graphic->LoadTexture("graphic/wazon.png");
	texKaput = Graphic->LoadTexture("graphic/wazon_kaput.png");
	SetColor(1,1,1);
	BasicTex = texNormal;
}

int viewActionWazon::Work(Uint32 time)
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
		SetPosition(x, startY + passedAnimTime*0.2, width, height, (float)passedAnimTime/vAW_FALLTIME*90.0f);
		passedAnimTime += time;
		if(passedAnimTime > vAW_FALLTIME)
		{
			step = 3;
			sys->dzwiek(ID);
		}
		break;
	case 3:
		SetPosition(x, startY + vAW_FALLTIME*0.2, 125, 116, 0);
		BasicTex = texKaput;
		step = 4;

		return 1;
	}

	return 0;
}
void viewActionWazon::SetStep(int p_step)
{
	if(step > 3) BasicTex = texNormal;

	viewActionBox::SetStep(p_step);
	startY = y;
}