#pragma once

#include "viewScene.h"
#include "viewActionAlkohol.h"
#include "viewActionKontakt.h"
#include "viewActionKsiazki.h"
#include "viewActionLampa.h"
#include "viewActionOkno.h"
#include "viewActionObraz.h"
#include "viewActionRadio.h"
#include "viewActionWazon.h"
#include "viewActionZyrandol.h"

class viewScenTest : public viewScene
{
public:
	viewScenTest(void);
	~viewScenTest(void);

	StextChunk tekst;
	StextChunk tNumbers[10];
	GLint Background;
	GLint Babcia;
	GLint BabciaOczy;
	GLint BabciaKropki;
	GLint BabciaDlonie;
	GLint Level;
	GLint Heart[2];
	viewBox Button;

	viewActionAlkohol Alkohol;
	viewActionKontakt Kontakt;
	viewActionKsiazki Ksiazki;
	viewActionLampa Lampa;
	viewActionObraz Obraz;
	viewActionOkno Okno;
	viewActionRadio Radio;
	viewActionWazon Wazon;
	viewActionZyrandol Zyrandol;

	void Init(viewsScene data);
	void Init(viewsScene data, int level);
	void Render(Uint32 time);
	int Work(Uint32 time);

	static int ActLvl;

private:
	viewActionBox *ActionObjects[9];
	Uint32 lastActivationTime;
	void DrawPoints(int pkt);
	int v_iWynik;
};

