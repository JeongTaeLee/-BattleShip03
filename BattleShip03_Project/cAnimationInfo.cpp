#include "DXUT.h"
#include "cAnimationInfo.h"


cAnimationInfo::cAnimationInfo(INT maxIndex, INT idleIndex, DWORD frameTime, BOOL loop)
{
	m_maxIndex		= maxIndex;
	m_idleIndex		= idleIndex;
	m_nowIndex		= m_idleIndex;
	m_frameTime		= frameTime;
	m_nowTime		= 0;

	m_loop	= loop;
	m_end	= FALSE;
	
}

cAnimationInfo::~cAnimationInfo()
{
}

void cAnimationInfo::FrameUpdate()
{
	if (m_nowIndex < m_maxIndex)
		m_nowIndex++;
	else
	{
		if (m_loop)
			m_nowIndex = 0;
		else
			m_end = TRUE;
	}
}
