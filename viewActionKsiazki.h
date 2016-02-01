#pragma once
#include "viewactionbox.h"

#define vAK_BURNTIME 1000.0f

class viewActionKsiazki :
	public viewActionBox
{
public:
	viewActionKsiazki(void);
	~viewActionKsiazki(void);
	void Init(viewGraphic *p_Graphic);
	int Work(Uint32 time);
	void Render();
	GLuint texNormal;
	GLuint texBurn[4];

	void SetStep(int p_step);
private:
	viewActionBox smooth;
	Uint32 passedAnimTime;
};

