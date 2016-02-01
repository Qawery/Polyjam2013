#pragma once
#include "viewscene.h"
class viewWin :
	public viewScene
{
public:
	viewWin(void);
	~viewWin(void);

	void Init(viewsScene data);
	void Render(Uint32 time);
	int Work(Uint32 time);

	GLuint texGameName;
	GLuint texStart[2];

	viewBox Button;
};

