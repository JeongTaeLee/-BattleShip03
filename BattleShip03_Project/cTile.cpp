#include "DXUT.h"
#include "cTile.h"

#include "cExplosion.h"
#include "cLoopExplosion.h"

cTile::cTile(D3DXVECTOR2 pos, INT arrX, INT arrY)
{
	m_tileState = E_TILEIDLE;
	m_onTile	= FALSE;
	
	m_arrX = arrX;
	m_arrY = arrY;

	m_lightTile = FALSE;
	m_lightTime = 0;

	LPOBJINFO objectInfo = new cObjectInfo(pos, 70, 70, FALSE);
	LPANIINFO aniInfo = new cAnimationInfo(1, 0, 0, FALSE);

	m_brokenImage = IMAGEMANAGER->FindImage("Tile_BrokenTile");


	cGameObject::Init("Tile", objectInfo, aniInfo);
}

cTile::~cTile()
{
}

void cTile::Update()
{
	if (m_lightTile)
	{
		if (m_lightTime < timeGetTime())
		{
			m_lightTime = 0;
			m_lightTile = FALSE;
		}
	}


	Animation();

	m_info->CollUpdate(m_info->m_pos + CAMERAMANAGER->GetCameraPos());
}

void cTile::Render()
{

	if (m_onTile)
	{
		if (GAMEMANAGER->GetF1())
			m_info->m_color = D3DCOLOR_XRGB(255, 0, 0);
	}

	if (m_tileState == E_TILEIDLE)
	{
		m_image->Render(m_info->m_pos.x + CAMERAMANAGER->GetCameraPos().x, m_info->m_pos.y + CAMERAMANAGER->GetCameraPos().y,
		m_info->m_size, m_info->m_rot, m_info->m_centerPos, m_info->m_color);
	}
	else if (m_tileState == E_TILEBROKEN && m_onTile == FALSE)
	{
		m_brokenImage->Render(m_info->m_pos.x + CAMERAMANAGER->GetCameraPos().x, m_info->m_pos.y + CAMERAMANAGER->GetCameraPos().y,
		m_info->m_size, m_info->m_rot, m_info->m_centerPos, D3DCOLOR_XRGB(255, 255, 255));
	}

	m_info->m_color = D3DCOLOR_XRGB(255, 255, 255);
}

void cTile::Animation()
{
	switch (m_tileState)
	{
	case E_TILEIDLE:
		if (IsPointCollision(INPUTMANAGER->GetMousePos(), m_info->m_collRect) || m_lightTile)
			m_image = (*m_imageList)[1];
		else
			m_image = (*m_imageList)[0];
		break;

	case E_TILEBROKEN:
		m_image = (*m_imageList)[0];

		break;
	}
}

void cTile::SetBrokenTile()
{
	D3DXVECTOR2 CreatePos = D3DXVECTOR2(m_info->m_pos.x + 35,
		m_info->m_pos.y - 35);

	if (m_onTile)
	{
		OBJECTMANAGER->AddObject(EEXPLOSIONS, new cExplosion("Explosion_OnTileExplosion", CreatePos, 6, 70));
		OBJECTMANAGER->AddObject(EEXPLOSIONS, new cExplosion("Explosion_MainExplosion", D3DXVECTOR2(CreatePos.x, CreatePos.y + 50), 35, 40, 2.0));
		OBJECTMANAGER->AddObject(EEXPLOSIONS, new cLoopExplosion(D3DXVECTOR2(m_info->m_pos.x + 35, m_info->m_pos.y + 35 - 150)));
	}
	else
	{
		OBJECTMANAGER->AddObject(EEXPLOSIONS, new cExplosion("Explosion_NoTileExplosion", CreatePos, 6, 55));
		OBJECTMANAGER->AddObject(EEXPLOSIONS, new cExplosion("Explosion_MainExplosion", D3DXVECTOR2(CreatePos.x, CreatePos.y + 50), 35, 40, 2.0));
	}

	SOUNDMANAGER->pPlaySound(3);
	m_tileState = E_TILEBROKEN;
}

void cTile::LigthTile()
{
	if (m_lightTile == FALSE)
	{
		m_lightTile = TRUE;

		m_lightTime = timeGetTime() + 700;
	}
}
