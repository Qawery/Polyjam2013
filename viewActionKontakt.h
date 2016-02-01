#pragma once
#include "viewactionbox.h"
class viewActionKontakt :
	public viewActionBox
{
public:
	viewActionKontakt(void);
	~viewActionKontakt(void);
	void Init(viewGraphic *p_Graphic);
	int Work(Uint32 time);
	void SetStep(int p_step);
private:
	GLuint texIskry[3];
	GLuint texNormal;
};

