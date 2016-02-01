#pragma once

#include <cstdlib>
#include "Przedmioty.h"

class System_babcia
{
public:
	System_babcia();	//konstruktor systemu
	
	int getZycie();	//zwraca obecne zycie
	int getWynik();	//zwraca obecny wynik
	int getMaxAktywnych();	//zwraca maximum aktywnych na raz przemiotow dla obecnej planszy
	int getOpoznieniePrzedmiotu(int indeks);	//zwraca opoznienie dla danego przemiotu
	int getCzasPozostaly();	//zwraca czas
	void setCzasPozostaly(int czas);	//ustawia czas pozostaly do konca levelu
	int getMaxLevel();	//zwraca maxymalny level

	void zaladujLevel(int numerLevelu);	//zmienna oczekujaca na potwierdzenie na zakonczenie levelu
	int wylosujObiekt();	//losuje obiekt do aktywacji
	void aktywujObiekt(int indeks);	//aktywuje obiekt o indkesie
	void zbijObiekt(int indeks);	//informuje ze zapobiezono aktywacji obiektu
	void freeChunks();	//zwalnia kanaly, muzyke i chunki
	void dzwiek(int indeks);	//puszcza dzwiek dla danego przedmiotu
	void zmienMuzyka(int ping);	//zmienia muzke na inna

private:
	int zycieBabci;	//biezace zycie babci
	int wynik;	//okresla biezacy wynik gracza
	int maxAktywnych;	//okresla ile przedmiotow bedzie mozna aktywowac na raz w levelu
	int czasPozostaly;	//okreal ile czasu ma przezyc babcia by pomyslnie ukonczyc level
	Przedmioty przedmioty[MAXP];	//przedmioty na planszy
	Mix_Music* muzyka;	//biezaca muzyka
	
	void ustawWymagania(int numerLevelu);	//ustawia wymagania dla przedmiotow na danym levelu, var-numer levelu, inner
	void przeliczZycie(int moc);	//oblicza nowa wartos zycia po odjeciu mocy aktywowanego obiektu "moc", dodatkowo sprawdza warunek przegranej, inner
	void poprawWarunki();	//sprawdza czy ktorys z przedmiotow sie odblokowal, inner
	void sprzatnij();	//przygotowuje level do przyjecia nowych wartosci, zeruje przedmioty i ich wymagania, inner
};

