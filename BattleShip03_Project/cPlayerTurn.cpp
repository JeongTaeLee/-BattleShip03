#include "DXUT.h"
#include "cPlayerTurn.h"


cPlayerTurn::cPlayerTurn()
{
	m_printComplete = FALSE;
	m_printTurn = FALSE;
	m_printTime = 0;

	cObjectInfo * objectInfo = new cObjectInfo(D3DXVECTOR2(-851, -100));

	cGameObject::Init("Ui_PlayerTurn", objectInfo, nullptr);
}


cPlayerTurn::~cPlayerTurn()
{
}

void cPlayerTurn::Update()
{
	if (m_printTurn)
	{
		if (m_info->m_pos.x + 30 <= 0 && !m_printComplete)
		{
			m_info->m_pos.x += 30;
		}
		else
		{
			if (m_printComplete == FALSE)
			{
				m_printTime = timeGetTime() + 300;
				m_printComplete = TRUE;
			}


			if (m_printTime < timeGetTime())
			{
				m_info->m_pos.x -= 30;

				if (m_info->m_pos.x <= -851)
				{
					m_printComplete = FALSE;
					m_printTurn = FALSE;
					m_info->m_pos.x = -851;
				}
			}

		}
	}
}

void cPlayerTurn::Render()
{
	m_image->Render(m_info->m_pos.x, m_info->m_pos.y,m_info->m_size, m_info->m_rot, m_info->m_centerPos);
}

void cPlayerTurn::PrintTurn()
{
	m_printTurn = TRUE;

	m_printTime = timeGetTime() + 200;
}
