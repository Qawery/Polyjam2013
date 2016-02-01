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
	// �aduje do pami�ci tekstur�
	GLuint LoadTexture(char* src);
	void LoadTexture(char* src, StextChunk &chunk);
	// Zwalnia pami�� zaj�t� przez tekstur�
	void FreeTexture(GLuint texture);
	void FreeTexture(StextChunk &chunk);
	// Tworzy tekstur� na podstawie tekstu
	GLuint MakeTextureFromText(char * src, int size);
	// Tworzy tekstur� na podstawie tekstu i zwracja jej wysoko�� i szeroko��
	void MakeTextureFromText(char * src, int size, StextChunk &chunk);
	// Rysuje prostok�t z tekstur�
	void DrawSprite(float x, float y, float w, float h, GLuint texture);
	void DrawSprite(float x, float y, float w, float h, float angle, GLuint texture);
};

