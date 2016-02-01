#include "viewGraohic.h"
#include "viewConntrol.h"
#include "viewScenTest.h"
#include "viewMainMenu.h"
#include "viewGameover.h"
#include "viewWin.h"

int main( int argc, char* argv[] )
{
	System_babcia Sys;

	viewGraphic *Graphic;
	Graphic = new viewGraphic();

	Graphic->Init();
	viewConntrol Keys;
	viewScene *Scenka;
	viewsScene data;
	data.Controller = &Keys;
	data.Graphic = Graphic;
	data.Sys = &Sys;

	Scenka = new viewMainMenu;

	Scenka->Init(data);

	//do czasu
	Uint32 lastTime, passedTime = 0, actTime;
	lastTime = SDL_GetTicks();

	while(Keys.quit == false)
	{
		actTime = SDL_GetTicks();
		passedTime += actTime - lastTime;

		Scenka->PreRender(actTime - lastTime);
		Scenka->Render(actTime - lastTime);
		Scenka->PostRender(actTime - lastTime);

		switch(Scenka->Work(actTime- lastTime))
		{
			// reload
		case 1:
			viewScenTest::ActLvl = -1;

		case 10:
			delete Scenka;
			
			Scenka = new viewScenTest;

			viewScenTest::ActLvl++;
			Scenka->Init(data);
			break;

		case 6:
			// do menu
			delete Scenka;
			Scenka = new viewMainMenu;
			Scenka->Init(data);
			break;
		case 5:
			// do game over
			delete Scenka;
			Scenka = new viewGameover;
			Scenka->Init(data);
			break;
		case 7:
			// do Win
			delete Scenka;
			Scenka = new viewWin;
			Scenka->Init(data);
			break;
		}

		if(Keys.key.r)
		{
			delete Scenka;
			Scenka = new viewScenTest;

			Scenka->Init(data);
		}

		lastTime = actTime;
	}

	Sys.freeChunks();
	delete Scenka;

	return 0;
}