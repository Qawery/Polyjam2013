#include "Przedmioty.h"

//konstruktor przedmiotu
Przedmioty::Przedmioty()
{
	moc = 0;
	opoznienie = 0;
	gotowy = false;
	bylAktywowany = false;
	for(int i=0; i<MAXP; i++)
	{
		wymagania[i]=false;
	}
	efekt=Mix_LoadWAV("music/glassbreak.wav");
}
