#include "DXUT.h"
#include "cScoreBorad.h"


cScoreBorad::cScoreBorad()
{
	LPOBJINFO objInfo = new cObjectInfo(D3DXVECTOR2(0, -300));
	
	cGameObject::Init("Ui_ScoreBoard", objInfo, nullptr);

	m_scoreText			= new TCHAR[15];
	m_bastScoreText		= new TCHAR[15];
}


cScoreBorad::~cScoreBorad()
{
	SAFE_DELETE_ARRAY(m_scoreText);
	SAFE_DELETE_ARRAY(m_bastScoreText);
}

void cScoreBorad::Update()
{
	if (m_info->m_pos.y + 10 <= 0)
		m_info->m_pos.y+= 10;
	wsprintf(m_scoreText, L"%05d", GAMEMANAGER->GetScore());
	wsprintf(m_bastScoreText, L"05d", GAMEMANAGER->GetBastScore());
}

void cScoreBorad::Render()
{
	m_image->Render(m_info->m_pos.x, m_info->m_pos.y, m_info->m_size, m_info->m_rot, m_info->m_centerPos);

	TEXTMANAGER->drawText(m_scoreText, D3DXVECTOR2(875, m_info->m_pos.y + 70), 2);
	TEXTMANAGER->drawText(m_scoreText, D3DXVECTOR2(875, m_info->m_pos.y + 200), 2);
}
