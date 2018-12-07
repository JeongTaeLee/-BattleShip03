#include "DXUT.h"
#include "cObjectInfo.h"

cObjectInfo::cObjectInfo(D3DXVECTOR2 pos, float collX, float collY, BOOL centerColl, D3DCOLOR color)
{
	m_pos = pos;
	m_color = color;

	m_size		= 1.0f;
	m_rot		= 0.0f;

	m_collX = collX;
	m_collY = collY;

	m_centerColl = centerColl;

	if (m_centerColl)
		SetRect(&m_collRect, (LONG)m_pos.x - m_collX / 2, (LONG)m_pos.y - m_collY / 2, (LONG)m_pos.x + m_collX / 2, (LONG)m_pos.y + m_collY / 2);
	else
		SetRect(&m_collRect, (LONG)m_pos.x, (LONG)m_pos.y, (LONG)m_pos.x + m_collX, (LONG)m_pos.y + m_collY);

	m_centerPos = D3DXVECTOR3(0.f, 0.f, 0.f);
}

cObjectInfo::~cObjectInfo()
{
}

void cObjectInfo::CollUpdate(D3DXVECTOR2 pos)
{
	if (m_centerColl)
		SetRect(&m_collRect, (LONG)pos.x - m_collX / 2, (LONG)pos.y - m_collY / 2, (LONG)pos.x + m_collX / 2, (LONG)pos.y + m_collY / 2);
	else
		SetRect(&m_collRect, (LONG)pos.x, (LONG)pos.y, (LONG)pos.x + m_collX, (LONG)pos.y + m_collY);

}
