#include "viewGameover.h"


viewGameover::viewGameover(void)
{
}


viewGameover::~viewGameover(void)
{
	Graphic->FreeTexture(texGameName);
}

void viewGameover::Init(viewsScene data)
{
	viewScene::Init(data);
	texGameName = Graphic->LoadTexture("graphic/game_over.png");


	Button.SetPosition(400,400, 214, 81);
}

void viewGameover::Render(Uint32 time)
{
	Graphic->DrawSprite(400, 100, 671, 160, texGameName);


}
int viewGameover::Work(Uint32 time)
{
	viewScene::Work(time);

	if(Controller->mouse.ul)
		return 6;

	return 0;
}