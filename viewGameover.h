#pragma once
#include "viewscene.h"
class viewGameover :
	public viewScene
{
public:
	viewGameover(void);
	~viewGameover(void);

	void Init(viewsScene data);
	void Render(Uint32 time);
	int Work(Uint32 time);

	GLuint texGameName;

	viewBox Button;
};

