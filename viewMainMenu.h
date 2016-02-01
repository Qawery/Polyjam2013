#pragma once
#include "viewscene.h"
class viewMainMenu :
	public viewScene
{
public:
	viewMainMenu(void);
	~viewMainMenu(void);

	void Init(viewsScene data);
	void Render(Uint32 time);
	int Work(Uint32 time);

	GLuint texGameName;
	GLuint texGameName2;
	GLuint texStart[2];

	viewBox Button;
};

