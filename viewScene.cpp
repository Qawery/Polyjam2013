#include "viewScene.h"


viewScene::viewScene(void)
	:cycle(0)
	, passedTime(0)
{
}
void viewScene::PreRender(Uint32 time)
{
	glClear( GL_COLOR_BUFFER_BIT);
	glPushMatrix();
}

void viewScene::PostRender(Uint32 time)
{
	glPopMatrix();
	SDL_GL_SwapBuffers();
}

void viewScene::Init(viewsScene data)
{
	this->Graphic = data.Graphic;
	this->Controller = data.Controller;
	this->sys = data.Sys;
}

int viewScene::Work(Uint32 time) 
{ 
	passedTime+= time;
	this->Controller->Update();
	return ++cycle; 
}