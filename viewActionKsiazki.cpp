#include "viewActionKsiazki.h"


viewActionKsiazki::viewActionKsiazki(void)
	:passedAnimTime(0)
{
	ID = 2;
}


viewActionKsiazki::~viewActionKsiazki(void)
{
	if(texNormal) Graphic->FreeTexture(texNormal);
	for(int i = 0; i < 4; i++)
	{
		if(texBurn[i]) Graphic->FreeTexture(texBurn[i]);
	}
}
void viewActionKsiazki::Init(viewGraphic *p_Graphic)
{
	viewActionBox::Init(p_Graphic);

	texNormal = Graphic->LoadTexture("graphic/ksiazki.png");
	texBurn[0] = Graphic->LoadTexture("graphic/ksiazki01.png");
	texBurn[1] = Graphic->LoadTexture("graphic/ksiazki02.png");
	texBurn[2] = Graphic->LoadTexture("graphic/ksiazki03.png");
	texBurn[3] = Graphic->LoadTexture("graphic/ksiazki04.png");

	BasicTex = texNormal;


	smooth.Init(p_Graphic);
	smooth.SetBasicTex(texBurn[0]);
	smooth.SetColor(1, 1, 1, 1);
	SetColor(1,1,1);
}

int viewActionKsiazki::Work(Uint32 time)
{
	viewActionBox::Work(time);

	switch(step)
	{
	case 1: case 2: case 3: case 4:
		smooth.SetColor(1,1,1, (float)passedAnimTime/vAK_BURNTIME);
		passedAnimTime += time;
		if(passedAnimTime > vAK_BURNTIME)
		{
			passedAnimTime -= vAK_BURNTIME;
			BasicTex = texBurn[step-1];
			if(step < 4)
				smooth.SetBasicTex(texBurn[step]);
			smooth.SetColor(1,1,1,0);
			step += 1;
		}
		break;
	}

	return 0;
}

void viewActionKsiazki::Render()
{
	viewActionBox::Render();
	smooth.Render();
}

void viewActionKsiazki::SetStep(int p_step)
{
	viewActionBox::SetStep(p_step);
	smooth.SetPosition(x, y, width, height);
}