#include "viewActionBox.h"



viewActionBox::viewActionBox(void)
	:BasicTex(0)
	, passedTime(0)
	, step(0)
{
}


viewActionBox::~viewActionBox(void)
{
	if(BasicTex) Graphic->FreeTexture(BasicTex);
}


int viewActionBox::Work(Uint32 time) 
{ 
	passedTime+= time;
	
	passedFallTime += time*step;

	return ++cycle; 
}
void viewActionBox::Render()
{
	glPushAttrib(GL_CURRENT_BIT | GL_TEXTURE_BIT );
	glBindTexture( GL_TEXTURE_2D, BasicTex );
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(angle, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glColor4fv(this->color);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f( -width/2, -height/2);
		glTexCoord2f(1, 0);
		glVertex2f( width/2, -height/2);
		glTexCoord2f(1, 1);
		glVertex2f( width/2, height/2);
		glTexCoord2f(0, 1);
		glVertex2f( -width/2, height/2);
	glEnd();
	glPopMatrix();
	glPopAttrib();
}
void viewActionBox::Init(viewGraphic *p_Graphic)
{
	Graphic = p_Graphic;
}

void viewActionBox::SetStep(int p_step)
{
	step = p_step;
	if(p_step == 1)
	{
		startX = x;
		startY = y;
		passedFallTime = 0;
	}
}
int viewActionBox::GetStep()
{
	return step;
}