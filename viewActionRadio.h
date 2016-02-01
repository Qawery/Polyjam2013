#pragma once
#include "viewactionbox.h"
class viewActionRadio :
	public viewActionBox
{
public:
	viewActionRadio(void);
	~viewActionRadio(void);
	void Init(viewGraphic *p_Graphic);
	int Work(Uint32 time);
};

