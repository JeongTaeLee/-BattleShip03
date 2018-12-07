#include "DXUT.h"
#include "cStateBorad.h"

#include "cTileObject.h"
#include "cPlayerTileObject.h"


cStateBorad::cStateBorad()
{
	LPOBJINFO objInfo = new cObjectInfo(D3DXVECTOR2(-320, 0));
	
	cGameObject::Init("Ui_StateBoard", objInfo, nullptr);

	m_printUi = FALSE;

	auto Iter = TILEMANAGER->m_playerTileObjList.begin();
	m_hpBarList.push_back(new HpBar(&m_info->m_pos, D3DXVECTOR2(300, 285),*Iter));
	Iter++;
	m_hpBarList.push_back(new HpBar(&m_info->m_pos, D3DXVECTOR2(300, 406), *Iter));
	Iter++;
	m_hpBarList.push_back(new HpBar(&m_info->m_pos, D3DXVECTOR2(300, 527), *Iter));
	Iter++;
	m_hpBarList.push_back(new HpBar(&m_info->m_pos, D3DXVECTOR2(300, 648), *Iter));
	Iter++;
	m_hpBarList.push_back(new HpBar(&m_info->m_pos, D3DXVECTOR2(300, 769), *Iter));
}


cStateBorad::~cStateBorad()
{
	for (auto Iter = m_hpBarList.begin(); Iter != m_hpBarList.end();)
	{
		SAFE_DELETE(*Iter)
		Iter = m_hpBarList.erase(Iter);
    }
	m_hpBarList.clear();
}

void cStateBorad::Update()
{
	if (INPUTMANAGER->KeyDown(VK_TAB))
		m_printUi = !m_printUi;

	if (m_printUi)
	{
		if (m_info->m_pos.x + 10 <= 0)
			m_info->m_pos.x += 10;
	}
	else 
	{
		if (m_info->m_pos.x - 10 >= -320)
			m_info->m_pos.x -= 10;
	}

	for (auto Iter : m_hpBarList)
	{
		Iter->Update();
	}
	
}

void cStateBorad::Render()
{
	m_image->Render(m_info->m_pos.x, m_info->m_pos.y, m_info->m_size, m_info->m_rot, m_info->m_centerPos, m_info->m_color);

	for (auto Iter : m_hpBarList)
	{
		Iter->Render();
	}
}

HpBar::HpBar(D3DXVECTOR2 * standardPos, D3DXVECTOR2 addPos, cGameObject* tileObject)
{
	m_standardPos = standardPos;
	m_addPos = addPos;

	m_pos = (*m_standardPos) + m_addPos;

	m_tileObject = dynamic_cast<cPlayerTileObject*>(tileObject);

	if (m_tileObject->GetLife() == 2)
	{
		m_images = IMAGEMANAGER->FindListImage("Ui_2TileState");
		m_image = (*m_images)[2];
	}
	if (m_tileObject->GetLife() == 3)
	{
		m_images = IMAGEMANAGER->FindListImage("Ui_3TileState");
		m_image = (*m_images)[3];
	}
	if (m_tileObject->GetLife() == 4)
	{
		m_images = IMAGEMANAGER->FindListImage("Ui_4TileState");
		m_image = (*m_images)[4];
	}
}

HpBar::~HpBar()
{
	m_standardPos = nullptr;

	m_tileObject = nullptr;
}

void HpBar::Update()
{
	m_pos = m_addPos + (*m_standardPos);

	m_image = (*m_images)[m_tileObject->GetLife()];
}

void HpBar::Render()
{
	m_image->Render(m_pos.x, m_pos.y, 0.3, 0.0, D3DXVECTOR3(0, 0, 0));
}
