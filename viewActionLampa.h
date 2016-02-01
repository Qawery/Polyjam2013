#pragma once
#include "viewactionbox.h"

#define vAL_FALLTIME 600.0f
#define vAL_BREAK 100.0f
#define vAL_FALLAWAY 250.0f

class viewActionLampa :
	public viewActionBox
{
public:
	viewActionLampa(void);
	~viewActionLampa(void);
	void Init(viewGraphic *p_Graphic);
	int Work(Uint32 time);
private:
	Uint32 animTime;
	Uint32 passedAnimTime;

	float startW, startH;
};

