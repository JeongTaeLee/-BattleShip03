#include "DXUT.h"
#include "cCollocateUi.h"
#include "cPlayerTIleObject.h"

#include "cTile.h"
#include "cScoreBorad.h"
#include "cStateBorad.h"
cCollocateUi::cCollocateUi()
{
	cObjectInfo * objectInfo = new cObjectInfo(D3DXVECTOR2(0, 0));

	cGameObject::Init("Ui_CollocateInterface", objectInfo, nullptr);

	TILEMANAGER->AddTileObject(new cPlayerTileObject)->Init("Tank01", D3DXVECTOR2(200, 260), FALSE);
	TILEMANAGER->AddTileObject(new cPlayerTileObject)->Init("Tank01", D3DXVECTOR2(200, 400), FALSE);
	TILEMANAGER->AddTileObject(new cPlayerTileObject)->Init("Tank02", D3DXVECTOR2(150, 550), FALSE);
	TILEMANAGER->AddTileObject(new cPlayerTileObject)->Init("Tank02", D3DXVECTOR2(150, 680), FALSE);
	TILEMANAGER->AddTileObject(new cPlayerTileObject)->Init("Tank03", D3DXVECTOR2(120, 850), FALSE);
}


cCollocateUi::~cCollocateUi()
{
}

void cCollocateUi::Update()
{
	if (INPUTMANAGER->KeyDown('A'))
	{
		for (auto Iter : (*OBJECTMANAGER->GetGameObject(EPLAYERTILEOBJ)))
			Iter->SetDelete(TRUE);
		TILEMANAGER->m_playerTileObjList.clear();

		TILEMANAGER->AddTileObject(new cPlayerTileObject)->Init("Tank01", D3DXVECTOR2(200, 260), TRUE);
		TILEMANAGER->AddTileObject(new cPlayerTileObject)->Init("Tank01", D3DXVECTOR2(200, 400), TRUE);
		TILEMANAGER->AddTileObject(new cPlayerTileObject)->Init("Tank02", D3DXVECTOR2(150, 550), TRUE);
		TILEMANAGER->AddTileObject(new cPlayerTileObject)->Init("Tank02", D3DXVECTOR2(150, 680), TRUE);
		TILEMANAGER->AddTileObject(new cPlayerTileObject)->Init("Tank03", D3DXVECTOR2(120, 850), TRUE);
	}

	INT count = 0;

	for (auto Iter : (*OBJECTMANAGER->GetGameObject(EPLAYERTILE)))
	{
		cTile * tile = dynamic_cast<cTile*>(Iter);

		if (tile->GetOnTile())
			count++; 
	}

	if (count == 14)
	{
		if (m_info->m_pos.x - 10 > -300)
			m_info->m_pos.x -= 10;

		RECT rect = { 1650 , 0, 1920, 250 };
		
		if (INPUTMANAGER->KeyDown(VK_LBUTTON))
		{
			if (IsPointCollision(INPUTMANAGER->GetMousePos(), rect))
			{
				GAMEMANAGER->SetTurnOwner(E_PLAYERTURN);
				GAMEMANAGER->SetMode(E_INGAMEMODE);

				OBJECTMANAGER->AddObject(EFRISTUI, new cScoreBorad);
				OBJECTMANAGER->AddObject(EFRISTUI, new cStateBorad);
				m_deleteObject = TRUE;
			}
		}
	}

}
