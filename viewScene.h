#pragma once

#include "viewGraohic.h"
#include "viewConntrol.h"
#include "viewActionBox.h"
#include "system_Babcia.h"
#include <vector>
#include <math.h>

struct viewsScene
{
	viewGraphic *Graphic;
	viewConntrol *Controller;
	System_babcia *Sys;
};

class viewScene
{
public:
	viewScene(void);
	virtual ~viewScene(void){};
	virtual void PreRender(Uint32 time);
	virtual void Render(Uint32 time) {}
	virtual void PostRender(Uint32 time);
	virtual void Init(viewsScene data);

	viewGraphic *Graphic;
	viewConntrol *Controller;

	virtual int Work(Uint32 time);
	System_babcia *sys;

protected:
	int cycle;
	Uint32 passedTime;

};

