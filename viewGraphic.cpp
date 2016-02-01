#include "viewGraohic.h"


viewGraphic::viewGraphic(void)
{
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_WM_SetCaption( "Poltergeist - granny saving", NULL );
	TTF_Init();
}


viewGraphic::~viewGraphic(void)
{
	TTF_CloseFont( font );
	TTF_Quit();
	SDL_Quit();
}


void viewGraphic::Init(void)
{
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL );

	InitGL();

	font = TTF_OpenFont( "arial.ttf", 48 );
}


void viewGraphic::InitGL(void)
{
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
 
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	 
	glViewport( 0, 0, 800, 600 );
	 
	glClear( GL_COLOR_BUFFER_BIT );
	 
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	 
	glOrtho(0.0f, 800, 600, 0.0f, -1.0f, 1.0f);
	 
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}


void viewGraphic::Render(Uint32 time)
{
	glClear( GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	//GLuint a = LoadTexture("aaa.png");
	//glColor4f(.5,.5,.5,.5);
	//this->DrawSprite(0+time,0,50,50,a);
	//FreeTexture(a);


	SDL_GL_SwapBuffers();
}


// £aduje do pamiêci teksturê
GLuint viewGraphic::LoadTexture(char* src)
{
	SDL_Surface* loadedImage = NULL;    
	SDL_Surface* optimizedImage = NULL;    
	// Uchwut do nowej tekstury
	GLuint texture;
	GLenum texture_format;
	GLint  nOfColors;

	loadedImage = IMG_Load( src );
	
	if( loadedImage != NULL )
	{
		optimizedImage = SDL_DisplayFormatAlpha( loadedImage );        
		SDL_FreeSurface( loadedImage );

		if( optimizedImage != NULL )
		{
			nOfColors = optimizedImage->format->BytesPerPixel;
		}
		 if (nOfColors == 4)     // contains an alpha channel
		{
				if (optimizedImage->format->Rmask == 0x000000ff)
						texture_format = GL_RGBA;
				else
						texture_format = GL_BGRA;
		} else if (nOfColors == 3)     // no alpha channel
		{
				if (optimizedImage->format->Rmask == 0x000000ff)
						texture_format = GL_RGB;
				else
						texture_format = GL_BGR;
		} else {
				//tu mo¿e pojawiæ siê problem :P
			return 0;
		}
		glGenTextures( 1, &texture );
 
		// Binduj teksturê
		glBindTexture( GL_TEXTURE_2D, texture ); 
		// ustawienia w³aœciwoœci tekstury
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); 
		// za³adowanie danych do karty graficznej
		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, optimizedImage->w, optimizedImage->h, 0,
					  texture_format, GL_UNSIGNED_BYTE, optimizedImage->pixels );

		SDL_FreeSurface ( optimizedImage );
	}
	
	return texture;
}

void viewGraphic::LoadTexture(char* src, StextChunk &chunk)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	// Uchwyt do nowej tekstury
	GLuint texture;
	GLenum texture_format;
	GLint  nOfColors;

	loadedImage = IMG_Load( src );
	
	if( loadedImage != NULL )
	{
		optimizedImage = SDL_DisplayFormatAlpha( loadedImage );        
		SDL_FreeSurface( loadedImage );

		if( optimizedImage != NULL )
		{
			nOfColors = optimizedImage->format->BytesPerPixel;
		}
		 if (nOfColors == 4)     // contains an alpha channel
		{
				if (optimizedImage->format->Rmask == 0x000000ff)
						texture_format = GL_RGBA;
				else
						texture_format = GL_BGRA;
		} else if (nOfColors == 3)     // no alpha channel
		{
				if (optimizedImage->format->Rmask == 0x000000ff)
						texture_format = GL_RGB;
				else
						texture_format = GL_BGR;
		} else {
				//tu mo¿e pojawiæ siê problem :P
			return;
		}
		glGenTextures( 1, &texture );
 
		// Binduj teksturê
		glBindTexture( GL_TEXTURE_2D, texture ); 
		// ustawienia w³aœciwoœci tekstury
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); 
		// za³adowanie danych do karty graficznej
		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, optimizedImage->w, optimizedImage->h, 0,
					  texture_format, GL_UNSIGNED_BYTE, optimizedImage->pixels );

		chunk.w = optimizedImage->w;
		chunk.h = optimizedImage->h;
		chunk.ID = texture;

		SDL_FreeSurface ( optimizedImage );
	}
	
	return;
}


// Zwalnia pamiêæ zajêt¹ przez teksturê
void viewGraphic::FreeTexture(GLuint texture)
{
	glDeleteTextures( 1, &texture );
}
void viewGraphic::FreeTexture(StextChunk &chunk)
{
	this->FreeTexture(chunk.ID);
}


// Tworzy teksturê na podstawie tekstu
GLuint viewGraphic::MakeTextureFromText(char * src, int size)
{
	GLuint texture;
	SDL_Color textColor;
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;

	SDL_Surface *renderedtext = SDL_DisplayFormatAlpha(TTF_RenderUTF8_Blended( font, src, textColor ));

	if( renderedtext != NULL )
	{
		glGenTextures( 1, &texture );
 
		// Binduj teksturê
		glBindTexture( GL_TEXTURE_2D, texture ); 
		// ustawienia w³aœciwoœci tekstury
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); 
		// za³adowanie danych do karty graficznej
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, renderedtext->w, renderedtext->h, 0,
						GL_RGBA, GL_UNSIGNED_BYTE, renderedtext->pixels );

		SDL_FreeSurface ( renderedtext );
	}
	return texture;
}

// Tworzy teksturê i zwraca jej wysokoœæ i szerokoœæ
void viewGraphic::MakeTextureFromText(char * src, int size, StextChunk &chunk)
{
	GLuint texture;
	SDL_Color textColor;
	char *tsrc = new char [size+1];
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	memset(tsrc, 0, size+1);
	memcpy(tsrc, src, size);

	SDL_Surface *temp = TTF_RenderUTF8_Blended( font, tsrc, textColor );
	SDL_Surface *renderedtext = SDL_DisplayFormatAlpha(temp);
	SDL_FreeSurface ( temp );

	if( renderedtext != NULL )
	{
		glGenTextures( 1, &texture );
 
		// Binduj teksturê
		glBindTexture( GL_TEXTURE_2D, texture ); 
		// ustawienia w³aœciwoœci tekstury
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); 
		// za³adowanie danych do karty graficznej
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, renderedtext->w, renderedtext->h, 0,
						GL_RGBA, GL_UNSIGNED_BYTE, renderedtext->pixels );

		chunk.w = renderedtext->w;
		chunk.h = renderedtext->h;
		chunk.ID = texture;

		SDL_FreeSurface ( renderedtext );
	}
	delete [] tsrc;
	return;
}


// Rysuje prostok¹t z tekstur¹
void viewGraphic::DrawSprite(float x, float y, float w, float h, GLuint texture)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_QUADS );
		glTexCoord2i( 0, 1 );
		glVertex2f( -w/2, h/2);
		glTexCoord2i( 0, 0 );
		glVertex2f( -w/2, -h/2);
		glTexCoord2i( 1, 0 );
		glVertex2f( w/2, -h/2);
		glTexCoord2i( 1, 1 );
		glVertex2f( w/2, h/2);
	glEnd();
	glPopMatrix();
}
void viewGraphic::DrawSprite(float x, float y, float w, float h, float angle, GLuint texture)
{
	glTranslatef(x, y, 0);
	glRotatef(angle, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_QUADS );
		glTexCoord2i( 0, 1 );
		glVertex2f( -w/2, h/2);
		glTexCoord2i( 0, 0 );
		glVertex2f( -w/2, -h/2);
		glTexCoord2i( 1, 0 );
		glVertex2f( w/2, -h/2);
		glTexCoord2i( 1, 1 );
		glVertex2f( w/2, h/2);
	glEnd();
	glLoadIdentity();
}
