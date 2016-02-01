#pragma once

#include <SDL.h>

struct SKeyboard
{
	bool w, s, a, d, r;
};

struct SMouse
{
	int x, y;
	bool l, r, ul, ur, dl, dr;
};

class viewConntrol
{
public:
	viewConntrol(void);
	~viewConntrol(void);

	// Aktualizuje stany przycisków i myszki
	void Update(void);

	SKeyboard key;
	SMouse mouse;

	bool quit;
};

