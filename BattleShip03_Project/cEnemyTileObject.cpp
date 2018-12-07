#include "DXUT.h"
#include "cEnemyTileObject.h"

#include "cTile.h"

cEnemyTileObject::cEnemyTileObject()
{
}


cEnemyTileObject::~cEnemyTileObject()
{
}

void cEnemyTileObject::Init(const string & key)
{
	string idleKey = "";

	LPOBJINFO objInfo = new cObjectInfo(D3DXVECTOR2(0,0 ));
	LPANIINFO aniInfo = new cAnimationInfo(20, 0, 100, false);

	if (key == "Tank01")
	{
		idleKey = "Enemy_Tank01_NoneRotate";
		m_rotateIdle = IMAGEMANAGER->FindListImage("Enemy_Tank01_Rotate");
		
		objInfo->m_collX = 140;
		objInfo->m_collY = 70;

		m_lengthX = 2;
		m_lengthY = 1;


		objInfo->m_centerPos = D3DXVECTOR3(50, 55, 0);
		m_noneRotateCenter = objInfo->m_centerPos;
		m_rotateCenter = D3DXVECTOR3(90, 30, 0);

		m_debugImages = IMAGEMANAGER->FindListImage("Debug_TileObject01");
		m_debugImage = (*m_debugImages)[0];
	}
	else if (key == "Tank02")
	{
		idleKey = "Enemy_Tank02_NoneRotate";
		m_rotateIdle = IMAGEMANAGER->FindListImage("Enemy_Tank02_Rotate");

		objInfo->m_collX = 210;
		objInfo->m_collY = 70;
		
		objInfo->m_centerPos = D3DXVECTOR3(100, 110, 0);
		m_noneRotateCenter = objInfo->m_centerPos;
		m_rotateCenter = D3DXVECTOR3(205, 30, 0);

		m_lengthX = 3;
		m_lengthY = 1;

		m_debugImages = IMAGEMANAGER->FindListImage("Debug_TileObject02");
		m_debugImage = (*m_debugImages)[0];
	}
	else if (key == "Tank03")
	{
		idleKey = "Enemy_Tank03_NoneRotate";
		m_rotateIdle = IMAGEMANAGER->FindListImage("Enemy_Tank03_Rotate");
		
		objInfo->m_collX = 280;
		objInfo->m_collY = 70;

		objInfo->m_centerPos = D3DXVECTOR3(50, 180, 0);
		m_noneRotateCenter = objInfo->m_centerPos;
		m_rotateCenter = D3DXVECTOR3(95, 70, 0);

		m_lengthX = 4;
		m_lengthY = 1;

		m_debugImages = IMAGEMANAGER->FindListImage("Debug_TileObject03");
		m_debugImage = (*m_debugImages)[0];
	}

	cGameObject::Init(idleKey, objInfo, aniInfo);

	
	m_rotate = IsRandomRgn(0, 1);

	if (m_rotate)
	{
		m_info->m_centerPos = m_rotateCenter;
		ChangeXY();
	}

	while (TRUE)
	{
		if (Collocate())
			break;
	}
}

void cEnemyTileObject::Update()
{
	if (GAMEMANAGER->GetMode() == E_INGAMEMODE)
	{
		if(m_tileObjState != E_TILEOBJBROKEN)
			DeadCheck();
	}
	
	Animation();
	LifeCount();

	m_info->CollUpdate(m_info->m_pos + CAMERAMANAGER->GetCameraPos());
}

void cEnemyTileObject::Animation()
{
	if (m_aniInfo->m_nowTime > timeGetTime())
		return;

	m_aniInfo->m_nowTime = timeGetTime() + m_aniInfo->m_frameTime;

	if (m_rotate)
	{
		if (m_tileObjState == E_TILEOBJBROKEN)
		{
			if (m_aniInfo->m_nowIndex < m_aniInfo->m_maxIndex)
				m_aniInfo->m_nowIndex++;
			else
			{
				m_info->m_color = D3DCOLOR_ARGB(100, 255, 255, 255);
				m_broken = TRUE;
			}
			
			m_image = (*m_rotateIdle)[m_aniInfo->m_nowIndex];
		}
		else
			m_image = (*m_rotateIdle)[0];
	}
	else
	{
		if (m_tileObjState == E_TILEOBJBROKEN)
		{
			if (m_aniInfo->m_nowIndex < m_aniInfo->m_maxIndex)
				m_aniInfo->m_nowIndex++;
			else
			{
				m_info->m_color = D3DCOLOR_ARGB(100, 255, 255, 255);
				m_broken = TRUE;
			}
			
			m_image = (*m_imageList)[m_aniInfo->m_nowIndex];
		}
		else
			m_image = (*m_imageList)[0];
	}
}

void cEnemyTileObject::Render()
{
	if (m_tileObjState == E_TILEOBJBROKEN)
	{
		m_image->Render(m_info->m_pos.x + CAMERAMANAGER->GetCameraPos().x, m_info->m_pos.y + CAMERAMANAGER->GetCameraPos().y,
			m_info->m_size, m_info->m_rot, m_info->m_centerPos, m_info->m_color);
	}	
}

BOOL cEnemyTileObject::Collocate()
{
	auto enemyTileArray = TILEMANAGER->GetEnemyTileArray();

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
			if (enemyTileArray[randomY + addY][randomX + addX]->GetOnTile())
				return FALSE;
		}
	}

	for (INT addY = 0; addY < m_lengthY; addY++)
	{
		for (INT addX = 0; addX < m_lengthX; addX++)
		{
			enemyTileArray[randomY + addY][randomX + addX]->SetOnTile(TRUE);
			m_onTileList.push_back(enemyTileArray[randomY + addY][randomX + addX]);
		}
	}

	m_arrPosX = randomX;
	m_arrPosY = randomY;

	m_info->m_pos = enemyTileArray[randomY][randomX]->GetPos();

	return TRUE;
}
