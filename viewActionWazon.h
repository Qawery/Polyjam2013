#pragma once

#define vAW_FALLTIME 800

#include "viewactionbox.h"

class viewActionWazon :
	public viewActionBox
{
public:
	viewActionWazon(void);
	~viewActionWazon(void);
	void Init(viewGraphic *p_Graphic);
	int Work(Uint32 time);
	void SetStep(int p_step);
private:
	Uint32 animTime;
	Uint32 passedAnimTime;

	GLuint texNormal;
	GLuint texKaput;
};

