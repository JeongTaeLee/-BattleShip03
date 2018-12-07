#include "DXUT.h"
#include "cGameManager.h"

#include "cPlayerTurn.h"
#include "cEnemyTurn.h"

#include "cTileObject.h"

cGameManager::cGameManager()
{
	m_nowScore	= 0;
	m_bastScore = 0;

	m_gameMode	= E_COLLOCATEMODE;
	m_winner	= E_NOWINNER;
	
	m_changeTime = 0;
	
	m_nextTurnOwner		= E_NOTURN;
	m_turnOwner			= E_NOTURN;

	m_cameraChange		= FALSE;
	m_changeTurn		= FALSE;

	m_playerTurn = new cPlayerTurn;
	OBJECTMANAGER->AddObject(ESECONDUI, m_playerTurn);
	m_enemyTurn = new cEnemyTurn;
	OBJECTMANAGER->AddObject(ESECONDUI, m_enemyTurn);
}


cGameManager::~cGameManager()
{
}

void cGameManager::Reset()
{
	m_nowScore		= 0;
	m_winner = E_NOWINNER;

	m_gameMode		= E_COLLOCATEMODE;

	m_turnOwner		= E_NOTURN;
	m_nextTurnOwner = E_NOTURN;

	m_changeTime	= 0;

	m_cameraChange	= FALSE;

	m_f1			= FALSE;
}

void cGameManager::Update()
{
	ChangeTurn();

	if (m_gameMode == E_INGAMEMODE)
	{
		if (m_winner == E_NOWINNER)
		{
			INT count = 0;

			for (auto Iter : (*OBJECTMANAGER->GetGameObject(EPLAYERTILEOBJ)))
			{
				cTileObject * tile = dynamic_cast<cTileObject*>(Iter);

				if (tile->GetBroken())
					count++;
			}

			if (count == 5)
			{
				m_winner = E_ENEMYWINNER;
				SCENEMANAGER->ChangeScene("Ending");
				return;
			}

			count = 0;

			for (auto Iter : (*OBJECTMANAGER->GetGameObject(EENEMYTILEOBJ)))
			{
				cTileObject * tile = dynamic_cast<cTileObject*>(Iter);

				if (tile->GetBroken())
					count++;
			}

			if (count == 5)
			{
				m_winner = E_PLAYERWINNER;
				SCENEMANAGER->ChangeScene("Ending");
				return;
			}
		}
	}
}

void cGameManager::ChangeTurn()
{
	chitInput();

	if (m_nextTurnOwner == E_NOTURN)
		return;

	if (m_changeTime > timeGetTime())
		return;


	if (m_cameraChange == FALSE)
	{

		if (m_nextTurnOwner == E_PLAYERTURN)
		{
			m_playerTurn->PrintTurn();
			CAMERAMANAGER->SetCameraTarget(D3DXVECTOR2(-1920, 0));

			m_nowScore -= 5;

			if (m_nowScore < 0)
				m_nowScore = 0;
		}
		else if (m_nextTurnOwner == E_ENEMYTURN)
		{
			m_enemyTurn->PrintTurn();
			CAMERAMANAGER->SetCameraTarget(D3DXVECTOR2(0, 0));
		}
		
		m_cameraChange = TRUE;
	}
	
	if (m_cameraChange == TRUE && CAMERAMANAGER->GetCameraMoving() == FALSE)
	{
		m_cameraChange	= FALSE;
		m_changeTurn	= FALSE;
		m_turnOwner		= m_nextTurnOwner;
		m_nextTurnOwner = E_NOTURN;
		m_changeTime	= 0;
	}
}

void cGameManager::chitInput()
{
	if (INPUTMANAGER->KeyDown(VK_F1))
		m_f1 = !m_f1;
}

void cGameManager::SetTurnOwner(INT Owner)
{
	m_turnOwner		= E_NOTURN;
	m_nextTurnOwner = Owner;
	m_changeTime	= timeGetTime() + 2000;
	m_changeTurn = TRUE;
}
