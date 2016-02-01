//include biblioteki do liczb losowych
#include <cstdlib>
#include <SDL_mixer.h>

//stale do okreslania maximum leveli i przedmiotow
static const int MAXP=10;	//max przedmiotow na planszy

/*klasa opisujaca przedmiot w danym levelu*/
class Przedmiot
{
	public:
	int moc;	//moc obiektu
	int opoznienie;	//okresla ile czasu jest na zapobiegniecie aktywacji obiektu
	bool gotowy;	//czy mozna aktywowac
	bool bylAktywowany;	//okresla czy byl juz aktywowany
	bool wymagania[MAXP];	//obiekty wymagane, true-jest wymagany
	Mix_Chunk* efekt;
	Przedmiot();	//konstruktor
};

//konstruktor przedmiotu
Przedmiot::Przedmiot()
{
	moc = 0;
	opoznienie = 0;
	gotowy = false;
	bylAktywowany = false;
	for(int i=0; i<MAXP; i++)
	{
		wymagania[i]=false;
	}
	efekt=Mix_LoadWAV("glassbreak.wav");
}

/*funkcje uzywane w levelu*/
class System
{
	public:
	int zycieBabci;	//biezace zycie babci
	int maxAktywnych;	//okresla ile przedmiotow bedzie mozna aktywowac na raz w levelu
	int czasPozostaly;	//okreal ile czasu ma przezyc babcia by pomyslnie ukonczyc level
	int wynik;	//okresla biezacy wynik gracza
	Przedmiot przedmioty[MAXP];	//przedmioty na planszy
	Mix_Music* muzyka;	//biezaca muzyka
	System();	//konstruktor systemu
	
	int getWynik();	//zwraca obecny wynik, import
	int getZycie();	//zwraca obecne zycie,	import
	int getMaxAktywnych();	//zwraca maximum aktywnych na raz przemiotow dla obecnej planszy, imoprt
	int getCzasPozostaly();	//zwraca czas, import
	void setCzasPozostaly(int czas);	//ustawia czas pozostaly do konca levelu, import
	int getOpoznieniePrzedmiotu(int indeks);	//zwraca opoznienie dla danego przemiotu, import
	void freeChunks();	//zwalnia kanaly, muzyke i chunki

	void zaladujLevel(int numerLevelu);	//zmienna oczekujaca na potwierdzenie na zakonczenie levelu, import
	int wylosujObiekt();	//losuje obiekt do aktywacji, import
	void aktywujObiekt(int indeks);	//aktywuje obiekt o indkesie, import
	void zbijObiekt(int indeks);	//informuje ze zapobiezono aktywacji obiektu

	void ustawWymagania(int numerLevelu);	//ustawia wymagania dla przedmiotow na danym levelu, var-numer levelu, inner
	void przeliczZycie(int moc);	//oblicza nowa wartos zycia po odjeciu mocy aktywowanego obiektu "moc", dodatkowo sprawdza warunek przegranej, inner
	void poprawWarunki();	//sprawdza czy ktorys z przedmiotow sie odblokowal, inner
	void sprzatnij();	//przygotowuje level do przyjecia nowych wartosci, zeruje przedmioty i ich wymagania, inner
	void dzwiek(int indeks);	//puszcza dzwiek dla danego przedmiotu
	void zmienMuzyka(int ping);	//zmienia muzke na inna
};

//kreator systemu, zaczynamy od levelu 0
System::System()
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	zycieBabci=0;
	maxAktywnych = 0;
	czasPozostaly = 0;
	wynik =0;
	muzyka = Mix_LoadMUS("pingslow.mp3");
	ustawWymagania(0);
}

//######################################################################################################IMPORT

//zwraca wynik
int System::getWynik()
{
	return wynik;
}

//zwraca obecne zycie
int System::getZycie()
{
	return zycieBabci;
}

//zwraca max ilosc aktywnych na raz przedmiotow w obecnym levelu
int System::getMaxAktywnych()
{
	return maxAktywnych;
}

//zwraca pozostaly czas planszy
int System::getCzasPozostaly()
{
	return czasPozostaly;
}

//ustawia czas pozostaly
void System::setCzasPozostaly(int czas)
{
	if(czas>0)
	{
		czasPozostaly=czas;
	}else
	{
		czasPozostaly=0;
	}
}

//zwraca opoznienie przemiotu
int System::getOpoznieniePrzedmiotu(int indeks)
{
	return przedmioty[indeks].opoznienie;
}

//wczytuje nowy level
void System::zaladujLevel(int numerLevelu)
{
	wynik = wynik + zycieBabci;
	sprzatnij();
	ustawWymagania(numerLevelu);
	zmienMuzyka(0);
}

//losuje obiekt do aktywacji, "ile" okresla ile obiektow mozna aktywowac na raz
int System::wylosujObiekt()
{
	int v=0;
	bool t=false;
	for(;v<MAXP; v++)
	{
		if(przedmioty[v].gotowy)	///sprawdzam czy cos jeszcze mozna aktywowac
		{
			t=true;
			break;
		}
	}
	if(!t) return -1;
	while(t)
	{
		v = (rand()% MAXP);
		if(przedmioty[v].gotowy)
		{
			przedmioty[v].gotowy=false;
			break;
		}
	}
	return v;
}

//aktywuje obiekt
void System::aktywujObiekt(int indeks)
{
	dzwiek(indeks);
	przeliczZycie(przedmioty[indeks].moc);
	przedmioty[indeks].gotowy=false;
	przedmioty[indeks].bylAktywowany=true;
	przedmioty[indeks].moc=0;
	przedmioty[indeks].opoznienie=0;
	poprawWarunki();
	int i=getZycie();
	if(i>60)
	{
		return;
	}else if(i>30 && i<=60)
	{
		zmienMuzyka(1);
		return;
	}else if(i>0 && i<=30)
	{
		zmienMuzyka(2);
		return;
	}else if(i==0)
	{
		zmienMuzyka(3);
		return;
	}
}

//informuje ze zapobiezono aktywacji obiektu
void System::zbijObiekt(int indeks)
{
	przedmioty[indeks].gotowy=true;
}

//zwalnia chunki
void System::freeChunks()
{
	for(int i=0; i<MAXP; i++)
	{
		Mix_FreeChunk(przedmioty[i].efekt);
	}
	Mix_FreeMusic(muzyka);
	Mix_CloseAudio();
}
//######################################################################################################IMPORT
//######################################################################################################INNER

//Ustawia wymagania przedmiotow dla danego levelu
void System::ustawWymagania(int numerLevelu)
{
	switch (numerLevelu)
	{
	case 0:
		{
			zycieBabci=100;
			maxAktywnych = 3;
			czasPozostaly = 20000;
			
			//Kontakt
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=3000;
			przedmioty[0].efekt=Mix_LoadWAV("kontakt.wav");
			
			//Alkochol
			przedmioty[1].moc=20;
			przedmioty[1].opoznienie=1000;
			przedmioty[1].wymagania[0]=true;
			
			//Ksiazki
			przedmioty[2].wymagania[2]=true;
			
			//Radio
			przedmioty[3].gotowy=true;
			przedmioty[3].moc=40;
			przedmioty[3].opoznienie=333;

			//Obraz
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=1000;

			//Zyrandol
			przedmioty[5].gotowy=true;
			przedmioty[5].moc=20;
			przedmioty[5].opoznienie=1000;

			//Wazon
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=1000;

			//Lampa
			przedmioty[7].gotowy=true;
			przedmioty[7].moc=20;
			przedmioty[7].opoznienie=1000;
			
			//Okno
			przedmioty[8].wymagania[8]=true;
			return;
		}
	case 1:
		{
			zycieBabci=100;
			maxAktywnych = 3;
			czasPozostaly = 20000;
			
			//Kontakt
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=3000;
			przedmioty[0].efekt=Mix_LoadWAV("kontakt.wav");
			
			//Alkochol
			przedmioty[1].moc=20;
			przedmioty[1].opoznienie=1000;
			przedmioty[1].wymagania[0]=true;
			
			//Ksiazki
			przedmioty[2].wymagania[2]=true;
			
			//Radio
			przedmioty[3].gotowy=true;
			przedmioty[3].moc=40;
			przedmioty[3].opoznienie=333;

			//Obraz
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=1000;

			//Zyrandol
			przedmioty[5].gotowy=true;
			przedmioty[5].moc=20;
			przedmioty[5].opoznienie=1000;

			//Wazon
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=1000;

			//Lampa
			przedmioty[7].gotowy=true;
			przedmioty[7].moc=20;
			przedmioty[7].opoznienie=1000;
			
			//Okno
			przedmioty[8].wymagania[8]=true;
			return;
		}
	default:
		{
			zycieBabci=100;
			maxAktywnych = 3;
			czasPozostaly = 20000;
			
			//Kontakt
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=3000;
			przedmioty[0].efekt=Mix_LoadWAV("kontakt.wav");
			
			//Alkochol
			przedmioty[1].moc=20;
			przedmioty[1].opoznienie=1000;
			przedmioty[1].wymagania[0]=true;
			
			//Ksiazki
			przedmioty[2].wymagania[2]=true;
			
			//Radio
			przedmioty[3].gotowy=true;
			przedmioty[3].moc=40;
			przedmioty[3].opoznienie=333;

			//Obraz
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=1000;

			//Zyrandol
			przedmioty[5].gotowy=true;
			przedmioty[5].moc=20;
			przedmioty[5].opoznienie=1000;

			//Wazon
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=1000;

			//Lampa
			przedmioty[7].gotowy=true;
			przedmioty[7].moc=20;
			przedmioty[7].opoznienie=1000;
			
			//Okno
			przedmioty[8].wymagania[8]=true;
			return;
		}
	}
}

//Funkcja modyfikuje wartosc zycia o podana wartosc i sprawdza czy spelniono warunek zwyciestwa.
void System::przeliczZycie(int moc)	
{
	zycieBabci = (zycieBabci-moc);
	if(zycieBabci<=0)
	{
		zycieBabci = 0;
	}
}

//sprawdza czy ktos sie odblokowal
void System::poprawWarunki()
{
	bool t=true;
	for(int i=0; i<MAXP; i++)
	{
		t=true;
		if(przedmioty[i].bylAktywowany)
		{
			continue;
		}
		for(int j=0; j<MAXP; j++)
		{
			if(przedmioty[i].wymagania[j])
			{
				t=false;
				break;
			}
		}
		przedmioty[i].gotowy = t;
	}
}

//przygorowuje obiekty i zmienne do zaladowania nowego levelu
void System::sprzatnij()
{
	for(int i=0; i<MAXP; i++)
	{
		przedmioty[i].moc = 0;
		przedmioty[i].opoznienie = 0;
		przedmioty[i].gotowy = false;
		przedmioty[i].bylAktywowany = false;
		przedmioty[i].efekt=Mix_LoadWAV("efekt.wav");
		for(int j=0; j<MAXP; j++)
		{
			przedmioty[i].wymagania[j]=false;
		}
	}
}

//puszcza dzwiek przedmiotu o indeksie
void System::dzwiek(int indeks)
{
	Mix_PlayChannel(-1, przedmioty[indeks].efekt, 0);
}

//zmienia muzyke
void System::zmienMuzyka(int ping)
{
	switch(ping)
	{
		case 0:
		{
			Mix_FreeMusic(muzyka);
			muzyka = Mix_LoadMUS("pingslow.mp3");
			Mix_PlayMusic(muzyka, -1);
			return;
		}
		case 1:
		{
			Mix_FreeMusic(muzyka);
			muzyka = Mix_LoadMUS("pingmedium.mp3");
			Mix_PlayMusic(muzyka, -1);
			return;
		}
		case 2:
		{
			Mix_FreeMusic(muzyka);
			muzyka = Mix_LoadMUS("pingfast.mp3");
			Mix_PlayMusic(muzyka, -1);
			return;
		}
		case 3:
		{
			Mix_FreeMusic(muzyka);
			muzyka = Mix_LoadMUS("pingconst.wav");
			Mix_PlayMusic(muzyka, -1);
			return;
		}
		default:
		{
			return;
		}
	}
}