#pragma once

#include <SDL_opengl.h>

#define _USE_MATH_DEFINES true
#include <math.h>


class viewBox
{
public:
	viewBox(void);
	~viewBox(void);
	// Sprawdza czy obiekt jest w pozycji podanej przez x i y
	bool OnPosition(int x, int y);
protected:
	// pozycja x
	float x;
	// pozycja y
	float y;
	// szerokoœæ
	float width;
	// wysokoœæ
	float height;
	// Kolor
	float color[4];
	//k¹t
	float angle;
public:
	// Ustawia kolor
	void SetColor(float r, float g, float b);
	void SetColor(float r, float g, float b, float a);
	// Rysuje box'a
	void Render(void);
	// Sposób rysowanie
	void SetDrawType(int mode);
private:
	// Sposób rysowania
	int drawtypemode;
public:
	// Ustawia box'a
	void SetPosition(float fx, float fy, float fw, float fh);
	void SetPosition(float fx, float fy, float fw, float fh, float p_angle);
	void SetPosition(float p_angle);
};

