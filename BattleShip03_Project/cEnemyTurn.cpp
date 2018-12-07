#include "DXUT.h"
#include "cEnemyTurn.h"


cEnemyTurn::cEnemyTurn()
{
	cObjectInfo * objectInfo = new cObjectInfo(D3DXVECTOR2(1920, -100));

	cGameObject::Init("Ui_EnemyTurn", objectInfo, nullptr);

	m_printTurn = FALSE;
	m_printComplete = FALSE;
	m_printTime = 0;
}


cEnemyTurn::~cEnemyTurn()
{
}

void cEnemyTurn::Update()
{
	if (m_printTurn)
	{
		if (m_info->m_pos.x - 30 >= 1060 && !m_printComplete)
		{
			//DEBUG_LOG("ENemyTUrn");
			m_info->m_pos.x -= 30;
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
				m_info->m_pos.x += 30;

				if (m_info->m_pos.x >= 1920)
				{
					m_printComplete = FALSE;
					m_printTurn = FALSE;
					m_info->m_pos.x = 1920;
				}
			}

		}
	}
}

void cEnemyTurn::Render()
{
	m_image->Render(m_info->m_pos.x, m_info->m_pos.y, m_info->m_size, m_info->m_rot, m_info->m_centerPos);
}

void cEnemyTurn::PrintTurn()
{
	m_printTurn = TRUE;
}
