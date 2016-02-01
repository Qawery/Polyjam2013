#pragma once
#include "viewactionbox.h"

#define vAA_FALLTIME 600
#define vAA_WAITTIME 200
#define vAA_BOOKSTIME 300

class viewActionAlkohol :
	public viewActionBox
{
public:
	viewActionAlkohol(void);
	~viewActionAlkohol(void);
	void Init(viewGraphic *p_Graphic);
	int Work(Uint32 time);
private:
	Uint32 animTime;
	Uint32 passedAnimTime;

	GLuint texNormal;
	GLuint texKaput;
};

