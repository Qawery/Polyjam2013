#pragma once
#include "viewactionbox.h"

#define vAO_FLYTIME_1 500.0f
#define vAO_FLYTIME_2 300.0f
#define vAO_FLYR_1 150.0f
#define vAO_DOWN 400.0f

class viewActionObraz :
	public viewActionBox
{
public:
	viewActionObraz(void);
	~viewActionObraz(void);
	void Init(viewGraphic *p_Graphic);
	int Work(Uint32 time);
	Uint32 passedAnimTime;
	GLuint texObr[3];
};

