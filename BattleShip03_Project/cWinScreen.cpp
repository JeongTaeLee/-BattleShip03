#include "DXUT.h"
#include "cWinScreen.h"


cWinScreen::cWinScreen()
{
	LPOBJINFO objInfo = new cObjectInfo(D3DXVECTOR2(0, 0));

	cGameObject::Init("Screen_GameClear", objInfo, nullptr);

	m_bastClear = IMAGEMANAGER->FindImage("Screen_GameBastClear");

	if (GAMEMANAGER->GetScore() > GAMEMANAGER->GetBastScore())
	{
		GAMEMANAGER->GetBastScore() = GAMEMANAGER->GetScore();

		m_bast = TRUE;
	}
	else
		m_bast = FALSE;

	m_scoreText = new TCHAR[15];
	m_bastText = new TCHAR[15];

	SetRect(&rePlayButton, 1407, 640, 1660, 705);
	SetRect(&mainButton, 1410, 790, 1670, 850);

}


cWinScreen::~cWinScreen()
{
}

void cWinScreen::Update()
{
	wsprintf(m_scoreText, TEXT("%06d"), GAMEMANAGER->GetScore());
	wsprintf(m_bastText, TEXT("%06d"), GAMEMANAGER->GetBastScore());

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
}

void cWinScreen::Render()
{
	m_image->Render(0, 0, 1, 0, D3DXVECTOR3(0, 0, 0));

	if (m_bast)
		m_bastClear->Render(0, 0, 1, 0, D3DXVECTOR3(0, 0, 0));

	TEXTMANAGER->drawText(m_bastText, D3DXVECTOR2(CENTERX - 700, CENTERY - 150), 2, D3DCOLOR_XRGB(0, 0, 0));
	TEXTMANAGER->drawText(m_scoreText, D3DXVECTOR2(CENTERX - 700, CENTERY + 70), 2, D3DCOLOR_XRGB(0, 0, 0));
}
