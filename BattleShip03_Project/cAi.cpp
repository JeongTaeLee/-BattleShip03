#include "DXUT.h"
#include "cAi.h"

#include "cEnemyTileObject.h"

#include "cTile.h"

cAi::cAi()
{
	
}


cAi::~cAi()
{
}

void cAi::Init()
{
#pragma region CREATEOBJ
	dynamic_cast<cEnemyTileObject*>(OBJECTMANAGER->AddObject(EENEMYTILEOBJ, new cEnemyTileObject))->Init("Tank01");
	dynamic_cast<cEnemyTileObject*>(OBJECTMANAGER->AddObject(EENEMYTILEOBJ, new cEnemyTileObject))->Init("Tank01");
	dynamic_cast<cEnemyTileObject*>(OBJECTMANAGER->AddObject(EENEMYTILEOBJ, new cEnemyTileObject))->Init("Tank02");
	dynamic_cast<cEnemyTileObject*>(OBJECTMANAGER->AddObject(EENEMYTILEOBJ, new cEnemyTileObject))->Init("Tank02");
	dynamic_cast<cEnemyTileObject*>(OBJECTMANAGER->AddObject(EENEMYTILEOBJ, new cEnemyTileObject))->Init("Tank03");
#pragma endregion CREATEOBJ

	m_aiMode		= E_HUNTMODE;
	m_aiDirection	= E_BOTTOMDIRECTION;

	m_pickCount		= 0;
	m_pickTime		= 0; 
	m_pickTile		= FALSE;

	m_delayTime		= 0;

	m_nowTile		= nullptr;
	m_pivotTile		= nullptr;
}

void cAi::Update()
{
	Attack();
}

void cAi::Render()
{
}

void cAi::Attack()
{
	if (GAMEMANAGER->GetTurnOwner() != E_ENEMYTURN)
		return;

	if (m_delayTime > timeGetTime())
		return;

	if(m_pickTile == FALSE)
		PickTile();
	else
	{
		switch (m_aiMode)
		{
		case E_HUNTMODE:
			HuntMode();
			break;

		case E_TARGETMODE:
			TargetMode();
			break;
		}
	}
}



void cAi::PickTile()
{
	if (m_pickCount == 6)
	{
		m_delayTime = timeGetTime() + 1000;
		m_pickTile = TRUE;
		return;
	}

	if (m_pickTime > timeGetTime())
		return;

	m_pickTime = timeGetTime() + 700 * 0.5;
	
	INT randomX = 0;
	INT randomY = 0;

	while (TRUE)
	{
		randomX = IsRandomRgn(0, 9);
		randomY = IsRandomRgn(0, 9);

		if (TILEMANAGER->GetPlayerTileArray()[randomY][randomX]->GetBroken())
			continue;

		TILEMANAGER->GetPlayerTileArray()[randomY][randomX]->LigthTile();
		
		break;
	}

	m_pickCount++;
}

void cAi::HuntMode()
{
	while (TRUE)
	{
		INT randomX = IsRandomRgn(0, 9);
		INT randomY = IsRandomRgn(0, 9);

		if (TILEMANAGER->GetPlayerTileArray()[randomY][randomX]->GetBroken())
			continue;

		TILEMANAGER->GetPlayerTileArray()[randomY][randomX]->SetBrokenTile();

		if (TILEMANAGER->GetPlayerTileArray()[randomY][randomX]->GetOnTile())
		{
			m_pivotTile = TILEMANAGER->GetPlayerTileArray()[randomY][randomX];
			m_nowTile = m_pivotTile;

			m_aiMode = E_TARGETMODE;

			m_delayTime = timeGetTime() + 1000;

			GAMEMANAGER->GetScore() -= 5;

			if (GAMEMANAGER->GetScore() < 0)
				GAMEMANAGER->GetScore() = 0;
		}
		else
		{
			m_pickTile = FALSE;
			m_pickCount = 0;
			
			GAMEMANAGER->SetTurnOwner(E_PLAYERTURN);
		}
		
		CAMERAMANAGER->CameraExplosion(30, CAMERAMANAGER->GetCameraPos());
		
		break;
	}
}

void cAi::TargetMode()
{
	switch (m_aiDirection)
	{
	
	case E_BOTTOMDIRECTION:
		if (m_nowTile->GetArrPosY() + 1 > 9)
		{
			m_aiDirection	= E_LEFTDIRECTION;
			m_nowTile		= m_pivotTile;
			return;
		}

		if (TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY() + 1][m_nowTile->GetArrPosX()]->GetBroken())
		{
			m_aiDirection	= E_LEFTDIRECTION;
			m_nowTile		= m_pivotTile;
			return;
		}

		TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY() + 1][m_nowTile->GetArrPosX()]->SetBrokenTile();

		if (TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY() + 1][m_nowTile->GetArrPosX()]->GetOnTile())
		{
			m_nowTile = TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY() + 1][m_nowTile->GetArrPosX()];
			m_delayTime = timeGetTime() + 1000;

			GAMEMANAGER->GetScore() -= 5;

			if (GAMEMANAGER->GetScore() < 0)
				GAMEMANAGER->GetScore() = 0;
		}
		else
		{
			m_nowTile = m_pivotTile;
			GAMEMANAGER->SetTurnOwner(E_PLAYERTURN);
		}
		break;

	case E_LEFTDIRECTION:
		if (m_nowTile->GetArrPosX() - 1 < 0)
		{
			m_aiDirection = E_TOPDIRECTION;
			m_nowTile = m_pivotTile;
			return;
		}

		if (TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY()][m_nowTile->GetArrPosX() -1]->GetBroken())
		{
			m_aiDirection = E_TOPDIRECTION;
			m_nowTile = m_pivotTile;
			return;
		}

		TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY()][m_nowTile->GetArrPosX() - 1]->SetBrokenTile();

		if (TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY()][m_nowTile->GetArrPosX() - 1]->GetOnTile())
		{
			m_nowTile = TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY()][m_nowTile->GetArrPosX() -1];
			m_delayTime = timeGetTime() + 1000;

			GAMEMANAGER->GetScore() -= 5;

			if (GAMEMANAGER->GetScore() < 0)
				GAMEMANAGER->GetScore() = 0;
		}
		else
		{
			m_nowTile = m_pivotTile;
			GAMEMANAGER->SetTurnOwner(E_PLAYERTURN);
		}
		break;

	case E_TOPDIRECTION:
		if (m_nowTile->GetArrPosY() - 1 < 0)
		{
			m_aiDirection = E_RIGHTDIRECTION;
			m_nowTile = m_pivotTile;
			return;
		}

		if (TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY() - 1][m_nowTile->GetArrPosX()]->GetBroken())
		{
			m_aiDirection = E_RIGHTDIRECTION;
			m_nowTile = m_pivotTile;
			return;
		}

		TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY() - 1][m_nowTile->GetArrPosX()]->SetBrokenTile();

		if (TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY() - 1][m_nowTile->GetArrPosX()]->GetOnTile())
		{
			m_nowTile = TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY() - 1][m_nowTile->GetArrPosX()];
			m_delayTime = timeGetTime() + 1000;

			GAMEMANAGER->GetScore() -= 5;

			if (GAMEMANAGER->GetScore() < 0)
				GAMEMANAGER->GetScore() = 0;
		}
		else
		{
			m_nowTile = m_pivotTile;
			GAMEMANAGER->SetTurnOwner(E_PLAYERTURN);
		}
		break;

	case E_RIGHTDIRECTION:
		if (m_nowTile->GetArrPosX() + 1 > 9)
		{
			m_aiDirection	= E_RIGHTDIRECTION;
			m_aiMode		= E_HUNTMODE;

			m_pickTile = FALSE;
			m_pickCount = 0;
			
			m_nowTile		= nullptr;
			m_pivotTile		= nullptr;
			return;
		}

		if (TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY()][m_nowTile->GetArrPosX() + 1]->GetBroken())
		{
			m_aiDirection	= E_RIGHTDIRECTION;
			m_aiMode		= E_HUNTMODE;
			
			m_pickTile = FALSE;
			m_pickCount = 0;

			m_nowTile		= nullptr;
			m_pivotTile		= nullptr;
			return;
		}

		TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY()][m_nowTile->GetArrPosX() + 1]->SetBrokenTile();

		if (TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY()][m_nowTile->GetArrPosX() + 1]->GetOnTile())
		{
			m_nowTile = TILEMANAGER->GetPlayerTileArray()[m_nowTile->GetArrPosY()][m_nowTile->GetArrPosX() + 1];
			m_delayTime = timeGetTime() + 1000;

			GAMEMANAGER->GetScore() -= 5;

			if (GAMEMANAGER->GetScore() < 0)
				GAMEMANAGER->GetScore() = 0;
		}
		else
		{
			GAMEMANAGER->SetTurnOwner(E_PLAYERTURN);
			
			m_aiMode		= E_HUNTMODE;
			m_aiDirection	= E_RIGHTDIRECTION;
			
			m_pickTile = FALSE;
			m_pickCount = 0;
			
			m_nowTile		= nullptr;
			m_pivotTile		= nullptr;
			
		}
		break;
	
	}
}
