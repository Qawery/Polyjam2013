#include "viewActionKontakt.h"


viewActionKontakt::viewActionKontakt(void)
{
	ID = 0;
}


viewActionKontakt::~viewActionKontakt(void)
{
}
void viewActionKontakt::Init(viewGraphic *p_Graphic)
{
	viewActionBox::Init(p_Graphic);

	texNormal = Graphic->LoadTexture("graphic/kontakt.png");
	SetColor(1,1,1);
	texIskry[0] = Graphic->LoadTexture("graphic/kontakt01.png");
	texIskry[1] = Graphic->LoadTexture("graphic/kontakt02.png");
	texIskry[2] = Graphic->LoadTexture("graphic/kontakt03.png");

	BasicTex = texNormal;
}

int viewActionKontakt::Work(Uint32 time)
{
	viewActionBox::Work(time);
	switch(step)
	{
	case 1:
		SetPosition(startX + rand()%2 - 1, startY + rand()%2 - 1, width, height, rand()%3);
		if(passedFallTime > fallTime)
		{
			step = 2;
			sys->dzwiek(ID);
			return 1;
		}
		break;
	case 2:
		SetPosition(startX + rand()%2 - 1, startY + rand()%2 - 1, width, height, rand()%3);
		BasicTex = texIskry[rand()%3];
		break;
	}


	return 0;
}

void viewActionKontakt::SetStep(int p_step)
{
	viewActionBox::SetStep(p_step);

	if(p_step == 0) BasicTex = texNormal;
}