#pragma once
#include "viewactionbox.h"
class viewActionOkno :
	public viewActionBox
{
public:
	viewActionOkno(void);
	~viewActionOkno(void);
	void Init(viewGraphic *p_Graphic);
	int Work(Uint32 time);
private:
	GLuint texNormal;
	GLuint texKaput;
};

