#pragma once

#include <SDL_mixer.h>
#include <SDL.h>

const int MAXP=9;	//max przedmiotow na planszy
const int MAXL=10;	//max przedmiotow na leveli

class Przedmioty
{
	public:
	int moc;	//moc obiektu
	int opoznienie;	//okresla ile czasu jest na zapobiegniecie aktywacji obiektu
	bool gotowy;	//czy mozna aktywowac
	bool bylAktywowany;	//okresla czy byl juz aktywowany
	bool wymagania[MAXP];	//obiekty wymagane, true-jest wymagany
	Mix_Chunk* efekt;
	Przedmioty();	//konstruktor
};

