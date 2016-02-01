#include "viewMainMenu.h"


viewMainMenu::viewMainMenu(void)
{
}


viewMainMenu::~viewMainMenu(void)
{
	Graphic->FreeTexture(texGameName);
	Graphic->FreeTexture(texGameName2);
	Graphic->FreeTexture(texStart[0]);
	Graphic->FreeTexture(texStart[1]);
}

void viewMainMenu::Init(viewsScene data)
{
	viewScene::Init(data);
	texGameName = Graphic->LoadTexture("graphic/title.png");
	texGameName2 = Graphic->LoadTexture("graphic/babcia_title.png");
	texStart[0] = Graphic->LoadTexture("graphic/start.png");
	texStart[1] = Graphic->LoadTexture("graphic/start01.png");

	sys->zmienMuzyka(-1);

	Button.SetPosition(400,400, 214, 81);
}

void viewMainMenu::Render(Uint32 time)
{
	Graphic->DrawSprite(400, 100, 671, 160, texGameName);
	Graphic->DrawSprite(500, 350, 1.5*324, 1.5*236, texGameName2);
	if(Button.OnPosition(Controller->mouse.x,Controller->mouse.y))
	{
		Graphic->DrawSprite(220, 450, 214, 81, texStart[1]);
	}else
		Graphic->DrawSprite(220, 450, 214, 81, texStart[0]);

}
int viewMainMenu::Work(Uint32 time)
{
	viewScene::Work(time);

	if(Controller->mouse.ul)
		return 1;

	return 0;
}