#include "DXUT.h"
#include "cFScreen.h"


cFScreen::cFScreen()
{
	cObjectInfo * objectInfo = new cObjectInfo(D3DXVECTOR2(0, 0));

	cGameObject::Init("Screen_GameFAiled", objectInfo, nullptr);

	m_nowText = new TCHAR[15];
	m_bastText = new TCHAR[15];

	SetRect(&rePlayButton, 1407, 640, 1660, 705);
	SetRect(&mainButton, 1410, 790, 1670, 850);
}


cFScreen::~cFScreen()
{
}

void cFScreen::Update()
{
	if (IsPointCollision(INPUTMANAGER->GetMousePos(), rePlayButton))
	{
		if (INPUTMANAGER->KeyDown(VK_LBUTTON))
		{
			GAMEMANAGER->Reset();
			TILEMANAGER->Reset();
			CAMERAMANAGER->Reset();
			SCENEMANAGER->ChangeScene("Ingame");
		}
	}
	if (IsPointCollision(INPUTMANAGER->GetMousePos(), mainButton))
	{
		if (INPUTMANAGER->KeyDown(VK_LBUTTON))
		{
			GAMEMANAGER->Reset();
			TILEMANAGER->Reset();
			CAMERAMANAGER->Reset();
			SCENEMANAGER->ChangeScene("Menu");
		}
	}

	wsprintf(m_nowText, TEXT("%06d"), GAMEMANAGER->GetScore());
	wsprintf(m_bastText, TEXT("%06d"), GAMEMANAGER->GetBastScore());
}

void cFScreen::Render()
{
	m_image->Render(0, 0, 1, 0, D3DXVECTOR3(0, 0, 0));

	TEXTMANAGER->drawText(m_nowText, D3DXVECTOR2(CENTERX - 700, CENTERY - 130), 2, D3DCOLOR_XRGB(0, 0, 0));
	TEXTMANAGER->drawText(m_bastText, D3DXVECTOR2(CENTERX - 200, CENTERY - 130), 2, D3DCOLOR_XRGB(0, 0, 0));
}
