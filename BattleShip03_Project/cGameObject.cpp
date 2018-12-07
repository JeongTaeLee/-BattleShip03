#include "DXUT.h"
#include "cGameObject.h"


cGameObject::cGameObject()
{
	m_deleteObject = FALSE;
	m_imageList		= nullptr;
	m_image			= nullptr;

	m_info			= nullptr;
	m_aniInfo		= nullptr;
}


cGameObject::~cGameObject()
{
	SAFE_DELETE(m_info);
	SAFE_DELETE(m_aniInfo);
}

void cGameObject::Init(const string & key, LPOBJINFO info, LPANIINFO aniInfo)
{
	m_aniInfo		= aniInfo;
	m_info			= info;

	if (m_aniInfo)
	{
		m_imageList		= IMAGEMANAGER->FindListImage(key);
		m_image			= (*m_imageList)[m_aniInfo->m_nowIndex];
	}
	else
	{
		m_imageList		= nullptr;
		m_image			= IMAGEMANAGER->FindImage(key);
	}
}

void cGameObject::Render()
{
	m_image->Render(m_info->m_pos.x + CAMERAMANAGER->GetCameraPos().x, m_info->m_pos.y + CAMERAMANAGER->GetCameraPos().y
		, m_info->m_size, m_info->m_rot, m_info->m_centerPos, m_info->m_color);
}



/*
void cGameObject::SetCameraPos(float addX)
{
	m_info->m_pos.x += addX;
}
*/
