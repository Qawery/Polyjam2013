#include "viewConntrol.h"


viewConntrol::viewConntrol(void)
	:quit(false)
{
	memset(&this->key, 0, sizeof(this->key));
	memset(&this->mouse, 0, sizeof(this->mouse));
}


viewConntrol::~viewConntrol(void)
{
}


// Aktualizuje stany przycisków i myszki
void viewConntrol::Update(void)
{
	SDL_Event sdl_event;

	mouse.dl = false;
	mouse.ul = false;
	mouse.dr = false;
	mouse.dl = false;

	while( SDL_PollEvent( &sdl_event ) )
	{

		if( sdl_event.type == SDL_QUIT ||
			( sdl_event.type == SDL_KEYUP && sdl_event.key.keysym.sym == SDLK_ESCAPE) )
		{
			this->quit = true;
		}

		if(sdl_event.type == SDL_KEYDOWN)
		{
			if(sdl_event.key.keysym.sym == 'w' || sdl_event.key.keysym.sym == SDLK_UP)
				this->key.w = true;
			if(sdl_event.key.keysym.sym == 's' || sdl_event.key.keysym.sym == SDLK_DOWN)
				this->key.s = true;
			if(sdl_event.key.keysym.sym == 'd' || sdl_event.key.keysym.sym == SDLK_RIGHT)
				this->key.d = true;			
			if(sdl_event.key.keysym.sym == 'a' || sdl_event.key.keysym.sym == SDLK_LEFT)
				this->key.a = true;
			if(sdl_event.key.keysym.sym == 'r')
				this->key.r = true;
		}
		if(sdl_event.type == SDL_KEYUP)
		{
			if(sdl_event.key.keysym.sym == 'w' || sdl_event.key.keysym.sym == SDLK_UP)
				this->key.w = false;
			if(sdl_event.key.keysym.sym == 's' || sdl_event.key.keysym.sym == SDLK_DOWN)
				this->key.s = false;
			if(sdl_event.key.keysym.sym == 'd' || sdl_event.key.keysym.sym == SDLK_RIGHT)
				this->key.d = false;			
			if(sdl_event.key.keysym.sym == 'a' || sdl_event.key.keysym.sym == SDLK_LEFT)
				this->key.a = false;
			if(sdl_event.key.keysym.sym == 'r')
				this->key.r = false;
		}

		if(sdl_event.type == SDL_MOUSEMOTION) 
		{
			mouse.x = sdl_event.motion.x;
			mouse.y = sdl_event.motion.y;
		}

		if(sdl_event.type == SDL_MOUSEBUTTONDOWN)
		{
			if(sdl_event.button.button == SDL_BUTTON_LEFT)
			{
				mouse.l = true;
				mouse.dl = true;
			}
			if(sdl_event.button.button == SDL_BUTTON_RIGHT)
			{
				mouse.r = true;
				mouse.dr = true;
			}
		}

		if(sdl_event.type == SDL_MOUSEBUTTONUP) 
		{
			if(sdl_event.button.button == SDL_BUTTON_LEFT)
			{
				mouse.l = false;
				mouse.ul = true;
			}
			if(sdl_event.button.button == SDL_BUTTON_RIGHT)
			{
				mouse.r = false;
				mouse.ur = true;
			}
		}
	}
}

