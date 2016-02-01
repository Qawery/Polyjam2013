#include "viewWin.h"


viewWin::viewWin(void)
{
}


viewWin::~viewWin(void)
{
	Graphic->FreeTexture(texGameName);
	Graphic->FreeTexture(texStart[0]);
	Graphic->FreeTexture(texStart[1]);
}

void viewWin::Init(viewsScene data)
{
	viewScene::Init(data);
	texGameName = Graphic->LoadTexture("graphic/win.png");


	Button.SetPosition(400,400, 214, 81);
}

void viewWin::Render(Uint32 time)
{
	Graphic->DrawSprite(400, 100, 671, 160, texGameName);


}
int viewWin::Work(Uint32 time)
{
	viewScene::Work(time);

	if(Controller->mouse.ul)
		return 6;

	return 0;
}