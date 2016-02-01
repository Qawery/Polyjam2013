#pragma once
#include "viewactionbox.h"

#define vAZ_SHADE 500.0f

class viewActionZyrandol :
	public viewActionBox
{
public:
	viewActionZyrandol(void);
	~viewActionZyrandol(void);
	void Init(viewGraphic *p_Graphic);
	int Work(Uint32 time);
	void Render();

private:
	viewBox shade;
	Uint32 passedAnimTime;
	GLuint texNormal;
	GLuint texKaput;
};

