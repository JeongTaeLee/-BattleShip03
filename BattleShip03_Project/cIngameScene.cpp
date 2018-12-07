#include "DXUT.h"
#include "cIngameScene.h"

#include "cLand.h"
#include "cLandScape.h"

#include "cCollocateUi.h"

#include "cAi.h"
#include "cPlayer.h"

cIngameScene::cIngameScene()
{
}


cIngameScene::~cIngameScene()
{
}

void cIngameScene::Init()
{
	SOUNDMANAGER->pPlayBgm(5, 34000);

	OBJECTMANAGER	->Reset();
	GAMEMANAGER		->Reset();
	TILEMANAGER		->Reset();
	CAMERAMANAGER	->Reset();

	OBJECTMANAGER->AddObject(EFRISTMAP, new cLandScape);
	OBJECTMANAGER->AddObject(ESECONDMAP, new cLand);

	TILEMANAGER->CreateTileMap();

	OBJECTMANAGER->AddObject(ESECONDMAP, new cCollocateUi);

	OBJECTMANAGER->AddObject(EADMIN, new cPlayer);
	dynamic_cast<cAi*>(OBJECTMANAGER->AddObject(EADMIN, new cAi))->Init();

}

void cIngameScene::Release()
{
	SOUNDMANAGER->pStopBgm();
}

void cIngameScene::Update()
{
	if(GAMEMANAGER->GetMode() == E_INGAMEMODE)
		CAMERAMANAGER->Update();

	GAMEMANAGER->Update();
	OBJECTMANAGER->Update();
}

void cIngameScene::Render()
{
	OBJECTMANAGER->Render();
	TEXTMANAGER->drawText(TEXT("Ingame"), D3DXVECTOR2(0, 0), 1);

}
