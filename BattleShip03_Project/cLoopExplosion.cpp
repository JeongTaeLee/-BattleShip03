#include "DXUT.h"
#include "cLoopExplosion.h"

cLoopExplosion::cLoopExplosion(D3DXVECTOR2 createPos)
{
	LPOBJINFO objInfo = new cObjectInfo(createPos);
	LPANIINFO aniInfo = new cAnimationInfo(6, 0, 50, TRUE);

	cGameObject::Init("Explosion_SmokeExplosion", objInfo, aniInfo);

	m_info->m_centerPos = D3DXVECTOR3(m_image->m_info.Width / 2, m_image->m_info.Height / 2, 0.0f);

	m_info->m_color = D3DCOLOR_ARGB(150, 255, 255, 255);
}

cLoopExplosion::~cLoopExplosion()
{
}

void cLoopExplosion::Update()
{
	Animation();
}

void cLoopExplosion::Animation()
{
	if (m_aniInfo->m_nowTime > timeGetTime())
		return;

	m_aniInfo->m_nowTime = timeGetTime() + m_aniInfo->m_frameTime;

	m_aniInfo->FrameUpdate();

	m_image = (*m_imageList)[m_aniInfo->m_nowIndex];
}
