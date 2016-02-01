#include "viewScenTest.h"

int viewScenTest::ActLvl = 0;

viewScenTest::viewScenTest(void)
	:lastActivationTime(0)
	,v_iWynik(0)
{

}


viewScenTest::~viewScenTest(void)
{
	this->Graphic->FreeTexture(tekst);
	this->Graphic->FreeTexture(Babcia);
	this->Graphic->FreeTexture(Background);
	this->Graphic->FreeTexture(Level);
	this->Graphic->FreeTexture(Heart[0]);
	this->Graphic->FreeTexture(Heart[1]);

	for(int i = 0; i < 10; ++i)
		this->Graphic->FreeTexture(this->tNumbers[i]);
}

void viewScenTest::Init(viewsScene data)
{
	viewScene::Init(data);

	//this->Graphic->MakeTextureFromText("Kill Bitch!",11, tekst);
	Background = this->Graphic->LoadTexture("graphic/level1.png");
	Babcia = this->Graphic->LoadTexture("graphic/babcia.png");
	BabciaOczy = this->Graphic->LoadTexture("graphic/oczy_zamkniete.png");
	BabciaDlonie = this->Graphic->LoadTexture("graphic/babcia_dlonie.png");
	BabciaKropki = this->Graphic->LoadTexture("graphic/oczy.png");
	Level = this->Graphic->LoadTexture("graphic/level.png");
	Heart[0] = this->Graphic->LoadTexture("graphic/serce.png");
	Heart[1] = this->Graphic->LoadTexture("graphic/aorty.png");

	// ladowanie liczb
	char temp[32];
	for(int i = 0; i < 10; ++i)
	{
		sprintf(temp, "graphic/%i.png", i);
		Graphic->LoadTexture(temp, tNumbers[i]);
	}

	Button.SetColor(0, 1, 0);
	Button.SetPosition(0, 0, 100, 30);
	Button.SetDrawType(GL_QUADS);

	Alkohol.Init(Graphic);
	Alkohol.SetPosition(101,322,35,49);
	ActionObjects[Alkohol.ID] = (viewActionBox*) &Alkohol;

	Kontakt.Init(Graphic);
	Kontakt.SetPosition(31,477,67,83);
	ActionObjects[Kontakt.ID] = (viewActionBox*) &Kontakt;

	Ksiazki.Init(Graphic);
	Ksiazki.SetPosition(687,353,182,341);
	ActionObjects[Ksiazki.ID] = (viewActionBox*) &Ksiazki;

	Lampa.Init(Graphic);
	Lampa.SetPosition(463,303,63,98);
	ActionObjects[Lampa.ID] = (viewActionBox*) &Lampa;

	Obraz.Init(Graphic);
	Obraz.SetPosition(36,237,49,160);
	ActionObjects[Obraz.ID] = (viewActionBox*) &Obraz;

	Okno.Init(Graphic);
	Okno.SetPosition(309,287,145,137);
	ActionObjects[Okno.ID] = (viewActionBox*) &Okno;

	Radio.Init(Graphic);
	Radio.SetPosition(150,312,42,53);
	ActionObjects[Radio.ID] = (viewActionBox*) &Radio;

	Wazon.Init(Graphic);
	Wazon.SetPosition(556,300,70,116);
	ActionObjects[Wazon.ID] = (viewActionBox*) &Wazon;

	Zyrandol.Init(Graphic);
	Zyrandol.SetPosition(406,132,360,248);
	ActionObjects[Zyrandol.ID] = (viewActionBox*) &Zyrandol;

	for(int i = 0; i< 9; i++)
		ActionObjects[i]->sys = sys;

	this->sys->zaladujLevel(ActLvl);

	v_iWynik = sys->getWynik();

	passedTime = 0;
}

void viewScenTest::Render(Uint32 time)
{
	glColor3f(1,1,1);
	this->Graphic->DrawSprite(400,300,800,600, Background);
	glColor4f(sinf(0.0001f*passedTime)*0.5+0.5f,0,0, 0.5f);

	//this->Graphic->DrawSprite(rand()%5+110, rand()%5+18, tekst.w, tekst.h, passedTime*0.01, tekst.ID);

	//Button.Render();

	Kontakt.Render();
	Ksiazki.Render();
	Obraz.Render();
	Okno.Render();
	Lampa.Render();
	Radio.Render();
	Wazon.Render();

	glColor3f(1,1,1);
	this->Graphic->DrawSprite(400,450,176,246, Babcia);
	if(passedTime % 100 <= 50 && sys->getZycie() < 50)
	this->Graphic->DrawSprite(500-123,453,129,43, BabciaDlonie);

	Alkohol.Render();
	

	Zyrandol.Render();

	// punkty
	glPushMatrix();
		glTranslatef(750, 120, 0);
		glScalef(0.5, 0.5, 0.5);
		this->DrawPoints(v_iWynik);
	glPopMatrix();

	// level
	this->Graphic->DrawSprite(520,50,303,135, Level);
	glPushMatrix();
		glTranslatef(760, 50, 0);
		this->DrawPoints(viewScenTest::ActLvl+1);
	glPopMatrix();

	//zycie
	glPushMatrix();
		glTranslatef(80, 80, 0);
		this->Graphic->DrawSprite(0, 0, 80, 96, Heart[1]);
		glScalef(1 +0.1*sin((float)passedTime/(100+9*sys->getZycie())), 1, 1);
		this->Graphic->DrawSprite(0, 0, 70, 68, Heart[0]);
	glPopMatrix();
}

int viewScenTest::Work(Uint32 time)
{
	viewScene::Work(time);

	//sprawdzenie zakonczenia
	sys->setCzasPozostaly(sys->getCzasPozostaly() - time);

	if(sys->getCzasPozostaly() <= 0)
	{
		// tu zmieniæ wy wygrac
		if(viewScenTest::ActLvl > 8)
		{
			return 7;
		}
		return 10;
	}else if(sys->getZycie() <= 0)
	{
		return 5;
	}

	if(passedTime - lastActivationTime > 1000)
	{
		int v_iActive = sys->wylosujObiekt();
		if(v_iActive > -1)
		{
			if(ActionObjects[v_iActive]->GetStep() == 0)
			{
				ActionObjects[v_iActive]->SetStep(1);
				ActionObjects[v_iActive]->SetFallTime(sys->getOpoznieniePrzedmiotu(v_iActive)); // czas
			}
		}
		lastActivationTime += 1000;
	}

	if(Controller->mouse.dl)
	{
		for(int i = 0; i < 9; ++i)
		{
			if(ActionObjects[i]->OnPosition(Controller->mouse.x, Controller->mouse.y) && ActionObjects[i]->GetStep() == 1)
			{
				ActionObjects[i]->SetStep(0);
				sys->zbijObiekt(i);
			}
		}
	}


	for(int i = 0; i < 9; ++i)
	{
		if(ActionObjects[i]->Work(time))
		{
			sys->aktywujObiekt(i);
			if(i == 7)
			{
				Okno.SetStep(1);
				sys->dzwiek(Okno.ID);
			}
			if(i == 1) Ksiazki.SetStep(1);
		}
	}
	
	return 0;
}


void viewScenTest::DrawPoints(int pkt)
{
	char buff[6];
	ZeroMemory(buff, 6);
	int n, x=0;
	_itoa(pkt, buff, 10);
	for(int i = 5; i >= 0; --i)
	{
		if(buff[i])
		{
			switch(buff[i]){case '0': n=0;break;case '1': n=1;break;case '2': n=2;break;
			case '3': n=3;break;case '4': n=4;break;case '5': n=5;break;case '6': n=6;break;
			case '7': n=7;break;case '8': n=8;break;case '9': n=9;break;}
			this->Graphic->DrawSprite(x, 0, this->tNumbers[n].w/2, this->tNumbers[n].h/2, this->tNumbers[n].ID );
			x-=this->tNumbers[n].w/2;
		}
	}
}