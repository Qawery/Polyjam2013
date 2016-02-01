#include "viewBox.h"


viewBox::viewBox(void)
	: x(0)
	, y(0)
	, width(0)
	, height(0)
	, drawtypemode(0)
	, angle(0)
{
	memset(color, 0, 3*sizeof(float));
	color[3] = 1;
}


viewBox::~viewBox(void)
{
}


// Sprawdza czy obiekt jest w pozycji podanej przez x i y
bool viewBox::OnPosition(int ix, int iy)
{
	if(ix > this->x-this->width/2 && ix < this->x + this->width/2 && iy > this->y-this->height/2 && iy < this->y + this->height/2)
		return true;
	return false;
}


// Ustawia kolor
void viewBox::SetColor(float r, float g, float b)
{
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
}
void viewBox::SetColor(float r, float g, float b, float a)
{
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
	this->color[3] = a;
}


// Rysuje box'a
void viewBox::Render(void)
{
	glPushAttrib(GL_CURRENT_BIT | GL_TEXTURE_BIT );
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(angle, 0, 0, 1);
	glDisable(GL_TEXTURE_2D);
	glColor4fv(this->color);
	glBegin(this->drawtypemode);
		glVertex2f( -width/2, -height/2);
		glVertex2f( width/2, -height/2);
		glVertex2f( width/2, height/2);
		glVertex2f( -width/2, height/2);
	glEnd();
	glPopMatrix();
	glPopAttrib();
}


// Sposób rysowanie
void viewBox::SetDrawType(int mode)
{
	this->drawtypemode = mode;
}


// Ustawia box'a
void viewBox::SetPosition(float fx, float fy, float fw, float fh)
{
	this->x = fx;
	this->y = fy;
	this->width = fw;
	this->height = fh;
}
void viewBox::SetPosition(float fx, float fy, float fw, float fh, float p_angle)
{
	SetPosition(fx, fy, fw, fh);
	SetPosition(p_angle);
}
void viewBox::SetPosition(float p_angle)
{
	angle = p_angle;
}
