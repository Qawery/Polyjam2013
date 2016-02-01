#include "viewActionRadio.h"


viewActionRadio::viewActionRadio(void)
{
	ID = 3;
}


viewActionRadio::~viewActionRadio(void)
{
}
void viewActionRadio::Init(viewGraphic *p_Graphic)
{
	viewActionBox::Init(p_Graphic);

	BasicTex = Graphic->LoadTexture("graphic/radio_ok.png");
	SetColor(1,1,1);
}

int viewActionRadio::Work(Uint32 time)
{
	viewActionBox::Work(time);

	switch(step)
	{
	case 1:
		SetPosition(startX + rand()%2 - 1, startY + rand()%2 - 1, width, height, rand()%3);
		break;
	}

	return 0;
}