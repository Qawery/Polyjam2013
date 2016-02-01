#include "System_babcia.h"

//kreator System_babcia, zaczynamy od levelu 0
System_babcia::System_babcia()
{
	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	zycieBabci=0;
	maxAktywnych = 0;
	czasPozostaly = 0;
	wynik =0;
	for(int i=0; i<MAXP; i++)
	{
		przedmioty[i].wymagania[i]=true;
	}
	muzyka = Mix_LoadMUS("music/pingslow.wav");
}

//######################################################################################################IMPORT

//zwraca ilosc max leveli
int System_babcia::getMaxLevel()
{
	return MAXL;
}

//zwraca wynik
int System_babcia::getWynik()
{
	return wynik;
}

//zwraca obecne zycie
int System_babcia::getZycie()
{
	return zycieBabci;
}

//zwraca max ilosc aktywnych na raz przedmiotow w obecnym levelu
int System_babcia::getMaxAktywnych()
{
	return maxAktywnych;
}

//zwraca opoznienie przemiotu
int System_babcia::getOpoznieniePrzedmiotu(int indeks)
{
	return przedmioty[indeks].opoznienie;
}

//zwraca pozostaly czas planszy
int System_babcia::getCzasPozostaly()
{
	return czasPozostaly;
}

//ustawia czas pozostaly
void System_babcia::setCzasPozostaly(int czas)
{
	if(czas>0)
	{
		czasPozostaly=czas;
	}else
	{
		czasPozostaly=0;
	}
}

//wczytuje nowy level
void System_babcia::zaladujLevel(int numerLevelu)
{
	wynik = wynik + zycieBabci;
	sprzatnij();
	ustawWymagania(numerLevelu);
	zmienMuzyka(0);
}

//losuje obiekt do aktywacji, "ile" okresla ile obiektow mozna aktywowac na raz
int System_babcia::wylosujObiekt()
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
void System_babcia::aktywujObiekt(int indeks)
{
	przeliczZycie(przedmioty[indeks].moc);
	przedmioty[indeks].gotowy=false;
	przedmioty[indeks].bylAktywowany=true;
	przedmioty[indeks].moc=0;
	przedmioty[indeks].opoznienie=0;
	for(int i=0; i<MAXP; i++)
	{
		przedmioty[i].wymagania[indeks]=false;
	}
	poprawWarunki();
	int i=getZycie();
	if(i>60)
	{
		zmienMuzyka(0);
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
void System_babcia::zbijObiekt(int indeks)
{
	przedmioty[indeks].gotowy=true;
}

//zwalnia chunki
void System_babcia::freeChunks()
{
	for(int i=0; i<MAXP; i++)
	{
		Mix_FreeChunk(przedmioty[i].efekt);
	}
	//Mix_FreeMusic(muzyka);
	Mix_CloseAudio();
}

//puszcza dzwiek przedmiotu o indeksie
void System_babcia::dzwiek(int indeks)
{
	Mix_PlayChannel(-1, przedmioty[indeks].efekt, 0);
}

//######################################################################################################IMPORT
//######################################################################################################INNER

//Funkcja modyfikuje wartosc zycia o podana wartosc i sprawdza czy spelniono warunek zwyciestwa.
void System_babcia::przeliczZycie(int moc)	
{
	zycieBabci = (zycieBabci-moc);
	if(zycieBabci<=0)
	{
		zycieBabci = 0;
	}
}

//sprawdza czy ktos sie odblokowal
void System_babcia::poprawWarunki()
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

//przygotowuje obiekty i zmienne do zaladowania nowego levelu
void System_babcia::sprzatnij()
{
	for(int i=0; i<MAXP; i++)
	{
		przedmioty[i].moc = 0;
		przedmioty[i].opoznienie = 0;
		przedmioty[i].gotowy = false;
		przedmioty[i].bylAktywowany = false;
		przedmioty[i].efekt=Mix_LoadWAV("music/glassbreak.wav");
		for(int j=0; j<MAXP; j++)
		{
			przedmioty[i].wymagania[j]=false;
		}
		przedmioty[i].wymagania[i]=true;
	}
}

//zmienia muzyke
void System_babcia::zmienMuzyka(int ping)
{
	switch(ping)
	{
		case -1:
		{
			Mix_FreeMusic(muzyka);
			return;
		}
		case 0:
		{
			Mix_FreeMusic(muzyka);
			muzyka = Mix_LoadMUS("music/pingslow.wav");
			Mix_PlayMusic(muzyka, -1);
			return;
		}
		case 1:
		{
			Mix_FreeMusic(muzyka);
			muzyka = Mix_LoadMUS("music/pingmedium.wav");
			Mix_PlayMusic(muzyka, -1);
			return;
		}
		case 2:
		{
			Mix_FreeMusic(muzyka);
			muzyka = Mix_LoadMUS("music/pingfast.wav");
			Mix_PlayMusic(muzyka, -1);
			return;
		}
		case 3:
		{
			Mix_FreeMusic(muzyka);
			muzyka = Mix_LoadMUS("music/pingconst.wav");
			Mix_PlayMusic(muzyka, -1);
			return;
		}
		default:
		{
			return;
		}
	}
}

//Ustawia wymagania przedmiotow dla danego levelu
void System_babcia::ustawWymagania(int numerLevelu)
{
	switch (numerLevelu)
	{
		case 0:
		{
			wynik=0;
			zycieBabci=100;
			maxAktywnych = 1;
			czasPozostaly = 4000;
			
			//Kontakt
			przedmioty[0].wymagania[0]=false;
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=6000;
			przedmioty[0].efekt=Mix_LoadWAV("music/kontakt.wav");
			
			//Obraz
			przedmioty[4].wymagania[4]=false;
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=4000;

			//Wazon
			przedmioty[6].wymagania[6]=false;
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=4000;
			return;
		}
		case 1:
		{
			zycieBabci=100;
			maxAktywnych = 2;
			czasPozostaly = 4000;
			
			//Kontakt
			przedmioty[0].wymagania[0]=false;
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=3000;
			przedmioty[0].efekt=Mix_LoadWAV("music/kontakt.wav");
			
			//Alkochol
			przedmioty[1].wymagania[1]=false;
			przedmioty[1].moc=30;
			przedmioty[1].opoznienie=2000;
			przedmioty[1].wymagania[0]=true;

			//Obraz
			przedmioty[4].wymagania[4]=false;
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=3000;

			//Wazon
			przedmioty[6].wymagania[6]=false;
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=3000;

			return;
		}
		case 2:
		{
			zycieBabci=100;
			maxAktywnych = 2;
			czasPozostaly = 6000;
			
			//Kontakt
			przedmioty[0].wymagania[0]=false;
			przedmioty[0].efekt=Mix_LoadWAV("music/kontakt.wav");
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=2000;

			//Alkochol
			przedmioty[1].wymagania[1]=false;
			przedmioty[1].wymagania[0]=true;
			przedmioty[1].moc=40;
			przedmioty[1].opoznienie=1200;
			
			//Radio
			przedmioty[3].wymagania[3]=false;
			przedmioty[3].gotowy=true;
			przedmioty[3].moc=20;
			przedmioty[3].opoznienie=2000;

			//Obraz
			przedmioty[4].wymagania[4]=false;
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=2000;

			//Zyrandol
			przedmioty[5].wymagania[5]=false;
			przedmioty[5].gotowy=true;
			przedmioty[5].moc=20;
			przedmioty[5].opoznienie=2000;

			//Wazon
			przedmioty[6].wymagania[6]=false;
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=2000;

			//Lampa
			przedmioty[7].wymagania[7]=false;
			przedmioty[7].gotowy=true;
			przedmioty[7].moc=20;
			przedmioty[7].opoznienie=2000;

			return;
		}
		case 3:
		{
			zycieBabci=100;
			maxAktywnych = 3;
			czasPozostaly = 8000;
			
			//Kontakt
			przedmioty[0].wymagania[0]=false;
			przedmioty[0].efekt=Mix_LoadWAV("music/kontakt.wav");
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=1800;

			//Alkochol
			przedmioty[1].wymagania[1]=false;
			przedmioty[1].wymagania[0]=true;
			przedmioty[1].moc=40;
			przedmioty[1].opoznienie=1000;
			
			//Radio
			przedmioty[3].wymagania[3]=false;
			przedmioty[3].gotowy=true;
			przedmioty[3].moc=20;
			przedmioty[3].opoznienie=1800;

			//Obraz
			przedmioty[4].wymagania[4]=false;
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=1800;

			//Zyrandol
			przedmioty[5].wymagania[5]=false;
			przedmioty[5].gotowy=true;
			przedmioty[5].moc=20;
			przedmioty[5].opoznienie=1800;

			//Wazon
			przedmioty[6].wymagania[6]=false;
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=1800;

			//Lampa
			przedmioty[7].wymagania[7]=false;
			przedmioty[7].gotowy=true;
			przedmioty[7].moc=20;
			przedmioty[7].opoznienie=1800;
			
			return;
		}
		case 4:
		{
			zycieBabci=100;
			maxAktywnych = 3;
			czasPozostaly = 9000;
			
			//Kontakt
			przedmioty[0].wymagania[0]=false;
			przedmioty[0].efekt=Mix_LoadWAV("music/kontakt.wav");
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=1600;

			//Alkochol
			przedmioty[1].wymagania[1]=false;
			przedmioty[1].wymagania[0]=true;
			przedmioty[1].moc=40;
			przedmioty[1].opoznienie=1000;
			
			//Radio
			przedmioty[3].wymagania[3]=false;
			przedmioty[3].gotowy=true;
			przedmioty[3].moc=20;
			przedmioty[3].opoznienie=1600;

			//Obraz
			przedmioty[4].wymagania[4]=false;
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=1600;

			//Zyrandol
			przedmioty[5].wymagania[5]=false;
			przedmioty[5].gotowy=true;
			przedmioty[5].moc=20;
			przedmioty[5].opoznienie=1700;

			//Wazon
			przedmioty[6].wymagania[6]=false;
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=1700;

			//Lampa
			przedmioty[7].wymagania[7]=false;
			przedmioty[7].gotowy=true;
			przedmioty[7].moc=20;
			przedmioty[7].opoznienie=1600;
			return;
		}
		
		case 5:
			{
			zycieBabci=100;
			maxAktywnych = 4;
			czasPozostaly = 10000;
			
			//Kontakt
			przedmioty[0].wymagania[0]=false;
			przedmioty[0].efekt=Mix_LoadWAV("music/kontakt.wav");
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=1600;

			//Alkochol
			przedmioty[1].wymagania[1]=false;
			przedmioty[1].wymagania[0]=true;
			przedmioty[1].moc=40;
			przedmioty[1].opoznienie=800;
			
			//Radio
			przedmioty[3].wymagania[3]=false;
			przedmioty[3].gotowy=true;
			przedmioty[3].moc=20;
			przedmioty[3].opoznienie=1600;

			//Obraz
			przedmioty[4].wymagania[4]=false;
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=1400;

			//Zyrandol
			przedmioty[5].wymagania[5]=false;
			przedmioty[5].gotowy=true;
			przedmioty[5].moc=20;
			przedmioty[5].opoznienie=1500;

			//Wazon
			przedmioty[6].wymagania[6]=false;
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=1500;

			//Lampa
			przedmioty[7].wymagania[7]=false;
			przedmioty[7].gotowy=true;
			przedmioty[7].moc=20;
			przedmioty[7].opoznienie=1400;
			return;
			}
		case 6:
			{
			zycieBabci=100;
			maxAktywnych = 4;
			czasPozostaly = 10000;
			
			//Kontakt
			przedmioty[0].wymagania[0]=false;
			przedmioty[0].efekt=Mix_LoadWAV("music/kontakt.wav");
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=500;

			//Alkochol
			przedmioty[1].wymagania[1]=false;
			przedmioty[1].wymagania[0]=true;
			przedmioty[1].moc=40;
			przedmioty[1].opoznienie=360;
			
			//Radio
			przedmioty[3].wymagania[3]=false;
			przedmioty[3].gotowy=true;
			przedmioty[3].moc=20;
			przedmioty[3].opoznienie=500;

			//Obraz
			przedmioty[4].wymagania[4]=false;
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=500;

			//Zyrandol
			przedmioty[5].wymagania[5]=false;
			przedmioty[5].gotowy=true;
			przedmioty[5].moc=20;
			przedmioty[5].opoznienie=500;

			//Wazon
			przedmioty[6].wymagania[6]=false;
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=500;

			//Lampa
			przedmioty[7].wymagania[7]=false;
			przedmioty[7].gotowy=true;
			przedmioty[7].moc=20;
			przedmioty[7].opoznienie=500;
			return;
			}
		case 7:
			{
			zycieBabci=100;
			maxAktywnych = 5;
			czasPozostaly = 12000;
			
			//Kontakt
			przedmioty[0].wymagania[0]=false;
			przedmioty[0].efekt=Mix_LoadWAV("music/kontakt.wav");
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=400;

			//Alkochol
			przedmioty[1].wymagania[1]=false;
			przedmioty[1].wymagania[0]=true;
			przedmioty[1].moc=40;
			przedmioty[1].opoznienie=240;
			
			//Radio
			przedmioty[3].wymagania[3]=false;
			przedmioty[3].gotowy=true;
			przedmioty[3].moc=20;
			przedmioty[3].opoznienie=400;

			//Obraz
			przedmioty[4].wymagania[4]=false;
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=400;

			//Zyrandol
			przedmioty[5].wymagania[5]=false;
			przedmioty[5].gotowy=true;
			przedmioty[5].moc=20;
			przedmioty[5].opoznienie=400;

			//Wazon
			przedmioty[6].wymagania[6]=false;
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=400;

			//Lampa
			przedmioty[7].wymagania[7]=false;
			przedmioty[7].gotowy=true;
			przedmioty[7].moc=20;
			przedmioty[7].opoznienie=400;
			return;
			}
		case 8:
			{
			zycieBabci=100;
			maxAktywnych = 6;
			czasPozostaly = 13000;
			
			//Kontakt
			przedmioty[0].wymagania[0]=false;
			przedmioty[0].efekt=Mix_LoadWAV("music/kontakt.wav");
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=300;

			//Alkochol
			przedmioty[1].wymagania[1]=false;
			przedmioty[1].wymagania[0]=true;
			przedmioty[1].moc=40;
			przedmioty[1].opoznienie=200;
			
			//Radio
			przedmioty[3].wymagania[3]=false;
			przedmioty[3].gotowy=true;
			przedmioty[3].moc=20;
			przedmioty[3].opoznienie=300;

			//Obraz
			przedmioty[4].wymagania[4]=false;
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=300;

			//Zyrandol
			przedmioty[5].wymagania[5]=false;
			przedmioty[5].gotowy=true;
			przedmioty[5].moc=20;
			przedmioty[5].opoznienie=300;

			//Wazon
			przedmioty[6].wymagania[6]=false;
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=300;

			//Lampa
			przedmioty[7].wymagania[7]=false;
			przedmioty[7].gotowy=true;
			przedmioty[7].moc=20;
			przedmioty[7].opoznienie=300;
			return;
			}
		case 9:
			{
			zycieBabci=100;
			maxAktywnych = 7;
			czasPozostaly = 14000;
			
			//Kontakt
			przedmioty[0].wymagania[0]=false;
			przedmioty[0].efekt=Mix_LoadWAV("music/kontakt.wav");
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=100;

			//Alkochol
			przedmioty[1].wymagania[1]=false;
			przedmioty[1].wymagania[0]=true;
			przedmioty[1].moc=40;
			przedmioty[1].opoznienie=60;
			
			//Radio
			przedmioty[3].wymagania[3]=false;
			przedmioty[3].gotowy=true;
			przedmioty[3].moc=20;
			przedmioty[3].opoznienie=100;

			//Obraz
			przedmioty[4].wymagania[4]=false;
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=100;

			//Zyrandol
			przedmioty[5].wymagania[5]=false;
			przedmioty[5].gotowy=true;
			przedmioty[5].moc=20;
			przedmioty[5].opoznienie=100;

			//Wazon
			przedmioty[6].wymagania[6]=false;
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=100;

			//Lampa
			przedmioty[7].wymagania[7]=false;
			przedmioty[7].gotowy=true;
			przedmioty[7].moc=20;
			przedmioty[7].opoznienie=100;
			return;
			}
		default:
		{
			zycieBabci=100;
			maxAktywnych = 7;
			czasPozostaly = 14000;
			
			//Kontakt
			przedmioty[0].wymagania[0]=false;
			przedmioty[0].efekt=Mix_LoadWAV("music/kontakt.wav");
			przedmioty[0].gotowy=true;
			przedmioty[0].moc=20;
			przedmioty[0].opoznienie=100;

			//Alkochol
			przedmioty[1].wymagania[1]=false;
			przedmioty[1].wymagania[0]=true;
			przedmioty[1].moc=40;
			przedmioty[1].opoznienie=60;
			
			//Radio
			przedmioty[3].wymagania[3]=false;
			przedmioty[3].gotowy=true;
			przedmioty[3].moc=20;
			przedmioty[3].opoznienie=100;

			//Obraz
			przedmioty[4].wymagania[4]=false;
			przedmioty[4].gotowy=true;
			przedmioty[4].moc=20;
			przedmioty[4].opoznienie=100;

			//Zyrandol
			przedmioty[5].wymagania[5]=false;
			przedmioty[5].gotowy=true;
			przedmioty[5].moc=20;
			przedmioty[5].opoznienie=100;

			//Wazon
			przedmioty[6].wymagania[6]=false;
			przedmioty[6].gotowy=true;
			przedmioty[6].moc=20;
			przedmioty[6].opoznienie=100;

			//Lampa
			przedmioty[7].wymagania[7]=false;
			przedmioty[7].gotowy=true;
			przedmioty[7].moc=20;
			przedmioty[7].opoznienie=100;
			return;
		}
	}
}