#include "DXUT.h"
#include "cPlayerTIleObject.h"

#include "cTile.h"
#include "cExplosion.h"
cPlayerTileObject::cPlayerTileObject()
{
	m_collocateState = E_COLLOCATEIDLE;
}


cPlayerTileObject::~cPlayerTileObject()
{
	for (auto Iter : m_onTileList)
		Iter->SetOnTile(FALSE);

	m_onTileList.clear();
}

void cPlayerTileObject::Init(const string & key, D3DXVECTOR2 pos, BOOL autoColl)
{
	string idleKey = "";

	LPOBJINFO objInfo = new cObjectInfo(pos);
	LPANIINFO aniInfo = nullptr;

	if (key == "Tank01")
	{
		idleKey = "Player_Tank01_NoneRotateIdle";

		m_rotateIdle = IMAGEMANAGER->FindListImage("Player_Tank01_RotateIdle");
		m_noneRotateAttack = IMAGEMANAGER->FindListImage("Player_Tank01_NoneRotateAttack");
		m_rotateAttack = IMAGEMANAGER->FindListImage("Player_Tank01_RotateAttack");
		m_noneRotateBroken = IMAGEMANAGER->FindListImage("Player_Tank01_NoneRotateBroken");
		m_rotateBroken = IMAGEMANAGER->FindListImage("Player_Tank01_RotateBroken");

		objInfo->m_centerPos = D3DXVECTOR3(40, 60, 0);
		m_noneRotateCenter = objInfo->m_centerPos;
		m_rotateCenter = D3DXVECTOR3(40, 30, 0);


		objInfo->m_collX = 140;
		objInfo->m_collY = 70;

		m_lengthX = 2;
		m_lengthY = 1;

		m_debugImages = IMAGEMANAGER->FindListImage("Debug_TileObject01");
		m_debugImage = (*m_debugImages)[0];
	}	
	else if (key == "Tank02")
	{
		idleKey = "Player_Tank02_NoneRotateIdle";

		m_rotateIdle		= IMAGEMANAGER->FindListImage("Player_Tank02_RotateIdle");
		m_noneRotateAttack	= IMAGEMANAGER->FindListImage("Player_Tank02_NoneRotateAttack");
		m_rotateAttack		= IMAGEMANAGER->FindListImage("Player_Tank02_RotateAttack");
		m_noneRotateBroken	= IMAGEMANAGER->FindListImage("Player_Tank02_NoneRotateBroken");
		m_rotateBroken		= IMAGEMANAGER->FindListImage("Player_Tank02_RotateBroken");
		
		objInfo->m_centerPos = D3DXVECTOR3(28, 115, 0);
		m_noneRotateCenter = objInfo->m_centerPos;
		m_rotateCenter = D3DXVECTOR3(65 ,45, 0);

		objInfo->m_collX = 210;
		objInfo->m_collY = 70;

		m_lengthX = 3;
		m_lengthY = 1;

		m_debugImages = IMAGEMANAGER->FindListImage("Debug_TileObject02");
		m_debugImage = (*m_debugImages)[0];
	}
	else if (key == "Tank03")
	{
		idleKey = "Player_Tank03_NoneRotateIdle";

		m_rotateIdle		= IMAGEMANAGER->FindListImage("Player_Tank03_RotateIdle");
		m_noneRotateAttack	= IMAGEMANAGER->FindListImage("Player_Tank03_NoneRotateAttack");
		m_rotateAttack		= IMAGEMANAGER->FindListImage("Player_Tank03_RotateAttack");
		m_noneRotateBroken	= IMAGEMANAGER->FindListImage("Player_Tank03_NoneRotateBroken");
		m_rotateBroken		= IMAGEMANAGER->FindListImage("Player_Tank03_RotateBroken");

		objInfo->m_centerPos = D3DXVECTOR3(30, 180, 0);
		m_noneRotateCenter = objInfo->m_centerPos;
		m_rotateCenter = D3DXVECTOR3(120, 50, 0);
		
		objInfo->m_collX = 280;
		objInfo->m_collY = 70;

		m_lengthX = 4;
		m_lengthY = 1;

		m_debugImages = IMAGEMANAGER->FindListImage("Debug_TileObject03");
		m_debugImage = (*m_debugImages)[0];

	}

	aniInfo = new cAnimationInfo(20, 0, 100,true);

	cGameObject::Init(idleKey, objInfo, aniInfo);

	if (autoColl)
	{
		m_rotate = IsRandomRgn(0, 1);
		
		if (m_rotate)
		{
			m_info->m_centerPos = m_rotateCenter;
			m_debugImage = (*m_debugImages)[1];
			ChangeXY();
		}
		while (TRUE)
		{
			if (CollocateAuto())
				break;
		}
	}

	m_info->CollUpdate(m_info->m_pos + CAMERAMANAGER->GetCameraPos());
}

void cPlayerTileObject::Update()
{
	if (GAMEMANAGER->GetMode() == E_COLLOCATEMODE)
		Collocate();
	else
	{
		if(m_tileObjState != E_TILEOBJBROKEN)
			DeadCheck();
	}
	
	LifeCount();
	Animation();

	m_info->CollUpdate(m_info->m_pos + CAMERAMANAGER->GetCameraPos());
}

BOOL cPlayerTileObject::CollocateAuto()
{

	
	auto playerTileArray = TILEMANAGER->GetPlayerTileArray();

	INT randomX = IsRandomRgn(0, 9);
	INT randomY = IsRandomRgn(0, 9);

	for (INT addY = 0; addY < m_lengthY; addY++)
	{
		for (INT addX = 0; addX < m_lengthX; addX++)
		{
			if (randomX + addX > 9 || randomY + addY > 9)
				return FALSE;
		}
	}

	for (INT addY = 0; addY < m_lengthY; addY++)
	{
		for (INT addX = 0; addX < m_lengthX; addX++)
		{
			if (playerTileArray[randomY + addY][randomX + addX]->GetOnTile())
				return FALSE;
		}
	}

	for (INT addY = 0; addY < m_lengthY; addY++)
	{
		for (INT addX = 0; addX < m_lengthX; addX++)
		{
			playerTileArray[randomY + addY][randomX + addX]->SetOnTile(TRUE);
			m_onTileList.push_back(playerTileArray[randomY + addY][randomX + addX]);
		}
	}
	
	m_info->m_pos = playerTileArray[randomY][randomX]->GetPos();

	m_arrPosX = randomX;
	m_arrPosY = randomY;
	return TRUE;
}

void cPlayerTileObject::Collocate()
{
	switch (m_collocateState)
	{
	case E_COLLOCATEIDLE:
		if (INPUTMANAGER->KeyDown(VK_LBUTTON))
		{
			if (PickTile())
			{
				INPUTMANAGER->SetMouseState(TRUE);
				m_collocateState = E_COLLOCATEMOVE;
			}
		}
		break;

	case E_COLLOCATEMOVE:
		m_info->m_pos = INPUTMANAGER->GetMousePos();

		if (INPUTMANAGER->KeyDown(VK_LBUTTON))
		{
			if (DropTile())
			{
				INPUTMANAGER->SetMouseState(FALSE);
				m_collocateState = E_COLLOCATEDROP;
			}
		}

		if (INPUTMANAGER->KeyDown(VK_LEFT))
		{
			if (!m_rotate)
			{
				m_rotate = TRUE;
				ChangeXY();
				m_info->m_centerPos = m_rotateCenter;
				m_debugImage = (*m_debugImages)[1];
			}
		}
		else if (INPUTMANAGER->KeyDown(VK_RIGHT))
		{
			if (m_rotate)
			{
				m_rotate = FALSE;
				ChangeXY();
				m_info->m_centerPos = m_noneRotateCenter;
				m_debugImage = (*m_debugImages)[0];
			}
		}

		break;

	case E_COLLOCATEDROP:
		if (INPUTMANAGER->KeyDown(VK_LBUTTON))
		{
			if (PickTile())
			{
				INPUTMANAGER->SetMouseState(TRUE);
				m_collocateState = E_COLLOCATEMOVE;
			}
		}
		break;
	}
}

void cPlayerTileObject::SetAttack()
{
	if (m_tileObjState == E_TILEOBJBROKEN)
		return;

	if (m_tileObjState != E_TILEOBJATTACK)
	{
		m_aniInfo->m_nowIndex = 0;
		m_tileObjState = E_TILEOBJATTACK;

		if (m_lengthX == 1 && m_lengthY == 3)
			OBJECTMANAGER->AddObject(EEXPLOSIONS, new cExplosion("Explosion_MainExplosion", D3DXVECTOR2(m_info->m_pos.x + 280, m_info->m_pos.y + 125), 35, 20, 1.0f));
		else if (m_lengthX == 3 && m_lengthY == 1)
			OBJECTMANAGER->AddObject(EEXPLOSIONS, new cExplosion("Explosion_MainExplosion", D3DXVECTOR2(m_info->m_pos.x + 280, m_info->m_pos.y), 35, 20, 1.0f));
		else if(m_lengthX == 1 && m_lengthY == 2)
			OBJECTMANAGER->AddObject(EEXPLOSIONS, new cExplosion("Explosion_MainExplosion", D3DXVECTOR2(m_info->m_pos.x + 200, m_info->m_pos.y + 35), 35, 20, 1.0f));
		else if(m_lengthX == 4 && m_lengthY == 1)
			OBJECTMANAGER->AddObject(EEXPLOSIONS, new cExplosion("Explosion_MainExplosion", D3DXVECTOR2(m_info->m_pos.x + 230, m_info->m_pos.y - 120), 35, 20, 1.0f));
		else if(m_lengthX = 1 && m_lengthY == 4)
			OBJECTMANAGER->AddObject(EEXPLOSIONS, new cExplosion("Explosion_MainExplosion", D3DXVECTOR2(m_info->m_pos.x + 180, m_info->m_pos.y + 50), 35, 20, 1.0f));
		else
			OBJECTMANAGER->AddObject(EEXPLOSIONS, new cExplosion("Explosion_MainExplosion", D3DXVECTOR2(m_info->m_pos.x + 200, m_info->m_pos.y), 35, 20, 1.0f));

		SOUNDMANAGER->pPlaySound(3);
	}
}

BOOL cPlayerTileObject::PickTile()
{
	if (!IsPointCollision(INPUTMANAGER->GetMousePos(), m_info->m_collRect))
		return FALSE;

	if (INPUTMANAGER->GetMouseState())
		return FALSE;

	for (auto Iter : m_onTileList)
	{
		cTile * tile = dynamic_cast<cTile*>(Iter);
		tile->SetOnTile(FALSE);
	}
	m_onTileList.clear();

	m_info->m_pos = INPUTMANAGER->GetMousePos();

	return TRUE;
}

BOOL cPlayerTileObject::DropTile()
{
	INT targetX = -1;
	INT targetY = -1;

	for (auto Iter : (*OBJECTMANAGER->GetGameObject(EPLAYERTILE)))
	{
		if (IsPointCollision(INPUTMANAGER->GetMousePos(), Iter->GetRect()))
		{
			cTile * tile = dynamic_cast<cTile*>(Iter);
			targetX = tile->GetArrPosX();
			targetY = tile->GetArrPosY();
		}
	}

	if (targetX == -1 || targetY == -1)
		return FALSE;
	
	auto playerTileArray = TILEMANAGER->GetPlayerTileArray();

	for (int addY = 0; addY < m_lengthY; addY++)
	{
		for (int addX = 0; addX < m_lengthX; addX++)
		{
			if (targetX + addX > 9 || targetY + addY > 9)
				return FALSE;
		}
	}

	for (int addY = 0; addY < m_lengthY; addY++)
	{
		for (int addX = 0; addX < m_lengthX; addX++)
		{
			if (playerTileArray[targetY + addY][targetX + addX]->GetOnTile())
				return FALSE;
		}
	}

	for (int addY = 0; addY < m_lengthY; addY++)
	{
		for (int addX = 0; addX < m_lengthX; addX++)
		{
			playerTileArray[targetY + addY][targetX + addX]->SetOnTile(TRUE);
			m_onTileList.push_back(playerTileArray[targetY + addY][targetX + addX]);
		}
	}

	m_arrPosX = targetX;
	m_arrPosY = targetY;

	m_info->m_pos = playerTileArray[targetY][targetX]->GetPos();

	return TRUE;
}
