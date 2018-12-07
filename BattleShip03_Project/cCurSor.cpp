#include "DXUT.h"
#include "cCurSor.h"


cCurSor::cCurSor()
{
	m_images = IMAGEMANAGER->AddListImage("Cursor", L"./Image/Ui/Cursor/100%02d.png", 0, 10);
	m_onImage = IMAGEMANAGER->AddListImage("ClickCursor", L"./Image/Ui/ClickCursor/100%02d.png", 0, 10);
	m_image = (*m_images)[0];



	m_imageCount = 0;
	m_imageTime = 0;

	m_on = FALSE;
	
}


cCurSor::~cCurSor()
{
	
}

void cCurSor::Update()
{
	if (INPUTMANAGER->KeyPress(VK_LBUTTON))
		m_on = TRUE;
	else
		m_on = FALSE;

	if (m_imageTime < timeGetTime())
	{
		m_imageTime = timeGetTime() + 20;

		if (m_imageCount < 9)
			m_imageCount++;
		else
			m_imageCount = 0;

		if (m_on)
			m_image = (*m_onImage)[m_imageCount];
		else
			m_image = (*m_images)[m_imageCount];
	}
}

void cCurSor::Render()
{
	m_image->Render(INPUTMANAGER->GetMousePos().x, INPUTMANAGER->GetMousePos().y, 1, 0, D3DXVECTOR3(m_image->m_info.Width / 2, m_image->m_info.Height / 2, 0),
		D3DCOLOR_XRGB(255, 255, 255));
}
