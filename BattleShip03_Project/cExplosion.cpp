#include "DXUT.h"
#include "cExplosion.h"

cExplosion::cExplosion(const string & key, D3DXVECTOR2 pos, INT maxIndex, DWORD frameTime, float size)
{
	LPOBJINFO objectInfo	= new cObjectInfo(pos);
	LPANIINFO aniInfo		= new cAnimationInfo(maxIndex, 0, frameTime, FALSE);

	cGameObject::Init(key, objectInfo, aniInfo);

	m_info->m_centerPos = D3DXVECTOR3(m_image->m_info.Width / 2, m_image->m_info.Height / 2, 0.0f);

	if (key == "Explosion_MainExplosion")
		m_info->m_size = size;
}

cExplosion::~cExplosion()
{
}

void cExplosion::Update()
{
	Animation();
}

void cExplosion::Animation()
{
	if (m_aniInfo->m_nowTime > timeGetTime())
		return;

	m_aniInfo->m_nowTime = timeGetTime() + m_aniInfo->m_frameTime;

	m_image = (*m_imageList)[m_aniInfo->m_nowIndex];

	if (m_aniInfo->m_nowIndex < m_aniInfo->m_maxIndex)
		m_aniInfo->m_nowIndex++;
	else
		m_deleteObject = TRUE;

}
