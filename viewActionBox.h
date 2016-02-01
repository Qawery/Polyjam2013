#pragma once
#include "viewbox.h"
#include "viewGraohic.h"
#include "System_babcia.h"
#include <SDL.h>

class viewActionBox :
	public viewBox
{
public:
	viewActionBox(void);
	~viewActionBox(void);
	virtual void Init(viewGraphic *p_Graphic);
	virtual void Render();
protected:
	int cycle;
	int step;
	Uint32 passedTime;
	Uint32 fallTime;
	Uint32 passedFallTime;
	viewGraphic *Graphic;
	GLuint BasicTex;
	float startX;
	float startY;
public:
	virtual int Work(Uint32 time);
	virtual void SetStep(int p_step);
	virtual int GetStep();
	void SetBasicTex(GLuint p_tex) {BasicTex = p_tex;}
	void SetFallTime(Uint32 time) { fallTime = time; passedFallTime = 0; }
	bool IsFallen();
	int ID;
	System_babcia *sys;
};

