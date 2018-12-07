#include "DXUT.h"
#include "cTileObject.h"


#include "cTile.h"

#include "cExplosion.h"


cTileObject::cTileObject()
{
	m_rotateCenter = D3DXVECTOR3(0, 0, 0);

	m_arrPosX		= 0;
	m_arrPosY		= 0;

	m_lengthX		= 0;
	m_lengthY		= 0;

	m_tileObjLife	= 0;

	m_rotate		= FALSE;
	m_broken		= FALSE;
	m_tileObjState	= E_TILEOBJIDLE;

	m_debugImages	= nullptr;
	m_debugImage	= nullptr;
}


cTileObject::~cTileObject()
{
}

void cTileObject::Render()
{	
	m_debugImage->Render(m_info->m_pos.x + CAMERAMANAGER->GetCameraPos().x, m_info->m_pos.y + CAMERAMANAGER->GetCameraPos().y
		, m_info->m_size, m_info->m_rot, D3DXVECTOR3(0, 0, 0),D3DCOLOR_XRGB(255, 255, 255));

	m_image->Render(m_info->m_pos.x + CAMERAMANAGER->GetCameraPos().x, m_info->m_pos.y + CAMERAMANAGER->GetCameraPos().y
		, m_info->m_size, m_info->m_rot, m_info->m_centerPos, m_info->m_color);
	
}

void cTileObject::Animation()
{
	if (m_aniInfo->m_nowTime > timeGetTime())
		return;

	m_aniInfo->m_nowTime = timeGetTime() + m_aniInfo->m_frameTime;

	if (m_rotate)
	{
		switch (m_tileObjState)
		{
		case E_TILEOBJIDLE:
			if (m_aniInfo->m_nowIndex < m_aniInfo->m_maxIndex)
				m_aniInfo->m_nowIndex++;
			else
				m_aniInfo->m_nowIndex = 0;
			
			m_image = (*m_rotateIdle)[m_aniInfo->m_nowIndex];
			break;

		case E_TILEOBJATTACK:
			if (m_aniInfo->m_nowIndex < m_aniInfo->m_maxIndex)
				m_aniInfo->m_nowIndex++;
			else
				m_tileObjState = E_TILEOBJIDLE;

			m_image = (*m_rotateAttack)[m_aniInfo->m_nowIndex];
			break;

		case E_TILEOBJBROKEN:
			if (m_aniInfo->m_nowIndex < m_aniInfo->m_maxIndex)
				m_aniInfo->m_nowIndex++;
			else
				m_broken = TRUE;

			m_image = (*m_rotateBroken)[m_aniInfo->m_nowIndex];
			break;
		}
	}
	else
	{
		switch (m_tileObjState)
		{
		case E_TILEOBJIDLE:
			if (m_aniInfo->m_nowIndex < m_aniInfo->m_maxIndex)
				m_aniInfo->m_nowIndex++;
			else
				m_aniInfo->m_nowIndex = 0;

			m_image = (*m_imageList)[m_aniInfo->m_nowIndex];
			break;

		case E_TILEOBJATTACK:
			if (m_aniInfo->m_nowIndex < m_aniInfo->m_maxIndex)
				m_aniInfo->m_nowIndex++;
			else
				m_tileObjState = E_TILEOBJIDLE;

			m_image = (*m_noneRotateAttack)[m_aniInfo->m_nowIndex];
			break;

		case E_TILEOBJBROKEN:
			if (m_aniInfo->m_nowIndex < m_aniInfo->m_maxIndex)
				m_aniInfo->m_nowIndex++;
			else
				m_broken = TRUE;

			m_image = (*m_noneRotateBroken)[m_aniInfo->m_nowIndex];
			break;
		}
	}
}

void cTileObject::SetAttack()
{
	if (m_tileObjState != E_TILEOBJATTACK)
	{
		m_aniInfo->m_nowIndex	= 0;
		m_tileObjState			= E_TILEOBJATTACK;
	}
}

void cTileObject::DeadCheck()
{
	BOOL deadCheck = FALSE;

	if (m_onTileList.size() == 0)
		return;

	for (auto Iter : m_onTileList)
	{
		if (!Iter->GetBroken())
			deadCheck = TRUE;
	}

	if (deadCheck == FALSE)
	{
		m_tileObjState			= E_TILEOBJBROKEN;
		m_aniInfo->m_nowIndex	= 0;
	}

	// DEAD CHECK ¸¸µé±â
}

void cTileObject::ChangeXY()
{
	INT tempLength	= m_lengthX;
	m_lengthX		= m_lengthY;
	m_lengthY		= tempLength;

	INT tempColl = m_info->m_collX;
	m_info->m_collX = m_info-> m_collY;
	m_info->m_collY = tempColl;

	m_info->m_collX = 70 * m_lengthX;
	m_info->m_collY = 70 * m_lengthY;

	m_info->CollUpdate(m_info->m_pos + CAMERAMANAGER->GetCameraPos());
}

void cTileObject::LifeCount()
{
	INT tempCount = 0;

	for (auto Iter : m_onTileList)
	{
		if (!Iter->GetBroken())
		{
			tempCount++;
		}
	}

	m_tileObjLife = tempCount;
}
