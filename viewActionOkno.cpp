#include "viewActionOkno.h"


viewActionOkno::viewActionOkno(void)
{
	ID = 8;
}


viewActionOkno::~viewActionOkno(void)
{
	if(texKaput) Graphic->FreeTexture(texKaput);
	if(texNormal) Graphic->FreeTexture(texKaput);
}
void viewActionOkno::Init(viewGraphic *p_Graphic)
{
	viewActionBox::Init(p_Graphic);

	texNormal = Graphic->LoadTexture("graphic/okno.png");
	texKaput = Graphic->LoadTexture("graphic/okno_kaput.png");
	BasicTex = texNormal;
	SetColor(1,1,1);
}

int viewActionOkno::Work(Uint32 time)
{
	viewActionBox::Work(time);

	switch(step)
	{
	case 1:
		BasicTex = texKaput;
		break;
	}

	return 0;
}