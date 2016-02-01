#pragma once

//#include "Box.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32

struct StextChunk
{
	GLuint ID;
	int w, h;
};

class viewGraphic
{
public:
	viewGraphic(void);
	~viewGraphic(void);
private:
	SDL_Surface *screen;
	TTF_Font *font;

public:
	void Init(void);
	void InitGL(void);
	void Render(Uint32 time);
	// £aduje do pamiêci teksturê
	GLuint LoadTexture(char* src);
	void LoadTexture(char* src, StextChunk &chunk);
	// Zwalnia pamiêæ zajêt¹ przez teksturê
	void FreeTexture(GLuint texture);
	void FreeTexture(StextChunk &chunk);
	// Tworzy teksturê na podstawie tekstu
	GLuint MakeTextureFromText(char * src, int size);
	// Tworzy teksturê na podstawie tekstu i zwracja jej wysokoœæ i szerokoœæ
	void MakeTextureFromText(char * src, int size, StextChunk &chunk);
	// Rysuje prostok¹t z tekstur¹
	void DrawSprite(float x, float y, float w, float h, GLuint texture);
	void DrawSprite(float x, float y, float w, float h, float angle, GLuint texture);
};

