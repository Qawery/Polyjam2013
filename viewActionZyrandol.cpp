#include "viewActionZyrandol.h"


viewActionZyrandol::viewActionZyrandol(void)
{
	ID = 5;
}


viewActionZyrandol::~viewActionZyrandol(void)
{
}
void viewActionZyrandol::Init(viewGraphic *p_Graphic)
{
	viewActionBox::Init(p_Graphic);

	texNormal = Graphic->LoadTexture("graphic/zyrandol.png");
	texKaput = Graphic->LoadTexture("graphic/zyrandol01.png");
	BasicTex = texNormal;
	SetColor(1,1,1);

	shade.SetColor(0,0,0,0);
	shade.SetPosition(400,300,800,600);
	shade.SetDrawType(GL_QUADS);
}

int viewActionZyrandol::Work(Uint32 time)
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
			sys->dzwiek(ID);
			BasicTex = texKaput;
			return 1;
		}
		break;
	case 2:
		shade.SetColor(0,0,0.3*passedAnimTime/vAZ_SHADE,0.3f*passedAnimTime/vAZ_SHADE);
		passedAnimTime += time;
		if(passedAnimTime > vAZ_SHADE)
		{
			step = 3;
			passedAnimTime = 0;
			return 1;
		}
	}

	return 0;
}

void viewActionZyrandol::Render()
{
	viewActionBox::Render();
	shade.Render();
}