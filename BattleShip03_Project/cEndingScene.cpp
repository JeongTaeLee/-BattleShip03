#include "DXUT.h"
#include "cEndingScene.h"

#include "cWinScreen.h"
#include "cFScreen.h"


cEndingScene::cEndingScene()
{
}


cEndingScene::~cEndingScene()
{
}

void cEndingScene::Init()
{
	OBJECTMANAGER->Reset();


	if (GAMEMANAGER->GetWinner() == E_PLAYERWINNER)
	{
		SOUNDMANAGER->pPlayBgm(4, 8000);
		OBJECTMANAGER->AddObject(ESECONDUI, new cWinScreen);
	}
	else if (GAMEMANAGER->GetWinner() == E_ENEMYWINNER)
	{
		SOUNDMANAGER->pPlayBgm(6, 19000);
		OBJECTMANAGER->AddObject(ESECONDUI, new cFScreen);
	}


}

void cEndingScene::Release()
{
	SOUNDMANAGER->pStopBgm();
}

void cEndingScene::Update()
{
	OBJECTMANAGER->Update();
}

void cEndingScene::Render()
{
	OBJECTMANAGER->Render();
}
