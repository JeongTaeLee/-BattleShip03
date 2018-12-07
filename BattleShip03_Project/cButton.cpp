#include "DXUT.h"
#include "cButton.h"




cButton::cButton(const string & key, D3DXVECTOR2 pos, void(*_func)(), RECT rc, BOOL ani)
{
	m_ani = ani;

	LPOBJINFO objInfo = new cObjectInfo(pos);
	LPANIINFO aniInfo = nullptr;

	m_collRect = rc;
	func01 = _func;

	if (m_ani)
		aniInfo = new cAnimationInfo(1, 0, 0, false);

	cGameObject::Init(key, objInfo, aniInfo);
}

cButton::~cButton()
{
}

void cButton::Update()
{
	if (IsPointCollision(INPUTMANAGER->GetMousePos(), m_collRect))
	{
		if (m_ani)
			m_image = (*m_imageList)[1];

		if (INPUTMANAGER->KeyDown(VK_LBUTTON))
		{
			func01();
		}
	}
	else
	{
		if (m_ani)
			m_image = (*m_imageList)[0];
	}
}

void cButton::Render()
{
	m_image->Render(m_info->m_pos.x, m_info->m_pos.y, m_info->m_size, m_info->m_rot, m_info->m_centerPos, m_info->m_color);
}
