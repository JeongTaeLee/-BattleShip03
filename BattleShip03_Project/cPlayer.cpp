#include "DXUT.h"
#include "cPlayer.h"

#include "cTile.h"
#include "cTileObject.h"

cPlayer::cPlayer()
{
	m_attackComplete		= FALSE;

	m_deleyTurnTime			= 0;
	m_attackTime			= 0;

	m_attackTileX			= 0;
	m_attackTileY			= 0;

	m_addScore				= 100;

	m_attackState			= E_ATTACKPICK;
}


cPlayer::~cPlayer()
{

}

void cPlayer::Update()
{
	Attack();
}

void cPlayer::Attack()
{
	if (GAMEMANAGER->GetTurnOwner() != E_PLAYERTURN)
		return;

	if (m_deleyTurnTime > timeGetTime())
		return;

	switch (m_attackState)
	{
	case E_ATTACKPICK:
		if(INPUTMANAGER->KeyDown(VK_LBUTTON))
			PickAttackTile();
			break;

	case E_ATTACKMOTION:
		AttackMotion();
		break;

	case E_ATTACKTILE:
		AttackTile();
		break;
	}
}

void cPlayer::PickAttackTile()
{
	INT tileX = -1;
	INT tileY = -1;

	for (auto Iter : *OBJECTMANAGER->GetGameObject(EENEMYTILE))
	{
		if (IsPointCollision(INPUTMANAGER->GetMousePos(), Iter->GetRect()))
		{
			cTile * tile = dynamic_cast<cTile*>(Iter);

			tileX = tile->GetArrPosX();
			tileY = tile->GetArrPosY();
		}
	}
	
	if (tileX == -1 || tileY == -1)
		return;

	if (TILEMANAGER->GetEnemyTileArray()[tileY][tileX]->GetBroken())
		return;

	m_attackTileX = tileX;
	m_attackTileY = tileY;

	CAMERAMANAGER->SetCameraTarget(D3DXVECTOR2(0, 0));

	m_attackTime = timeGetTime() + 3500;

	m_attackState = E_ATTACKMOTION;
}

void cPlayer::AttackMotion()
{
	if (CAMERAMANAGER->GetCameraMoving() == FALSE)
	{;
		for (auto Iter : *OBJECTMANAGER->GetGameObject(EPLAYERTILEOBJ))
		{
			cTileObject * tile = dynamic_cast<cTileObject*>(Iter);

			tile->SetAttack();

			if (m_attackComplete == FALSE)
			{
				m_attackComplete = TRUE;
				CAMERAMANAGER->CameraExplosion(20, CAMERAMANAGER->GetCameraPos());
			}

		}


		if (m_attackTime < timeGetTime())
		{
			CAMERAMANAGER->SetCameraTarget(D3DXVECTOR2(-1920, 0));
			m_attackState = E_ATTACKTILE;
		}
	}
}
void cPlayer::AttackTile()
{
	if (CAMERAMANAGER->GetCameraMoving() == FALSE)
	{
		TILEMANAGER->GetEnemyTileArray()[m_attackTileY][m_attackTileX]->SetBrokenTile();
		CAMERAMANAGER->CameraExplosion(30, CAMERAMANAGER->GetCameraPos());

		if (TILEMANAGER->GetEnemyTileArray()[m_attackTileY][m_attackTileX]->GetOnTile())
		{
			GAMEMANAGER->GetScore() += m_addScore;
			m_addScore += 20;
		}
		else
		{
			m_addScore = 100;
			GAMEMANAGER->SetTurnOwner(E_ENEMYTURN);
		}
		
		m_attackComplete = FALSE;
		m_attackState = E_ATTACKPICK;
		m_attackTileX = -1;
		m_attackTileY = -1;
	}
}

void cPlayer::Render()
{
}
