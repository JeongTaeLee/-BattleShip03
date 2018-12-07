#include "DXUT.h"
#include "TextManager.h"

extern LPD3DXSPRITE g_lpSprite;

void TextManager::Init()
{
	D3DXCreateFont(g_device, 50, 0, 0, 0, FALSE, DEFAULT_CHARSET, 0, 0, 0, TEXT("Fixedsys"),  &m_lpFont01);
	D3DXCreateFont(g_device, 70, 0, 0, 0, FALSE, DEFAULT_CHARSET, 0, 0, 0, TEXT("Fixedsys"), &m_lpFont02);
	D3DXCreateFont(g_device, 100, 0, 0, 0, FALSE, DEFAULT_CHARSET, 0, 0, 0, TEXT("Fixedsys"), &m_lpFont03);
	D3DXCreateFont(g_device, 130, 0, 0, 0, FALSE, DEFAULT_CHARSET, 0, 0, 0, TEXT("Fixedsys"), &m_lpFont04);
}

void TextManager::Release()
{
	m_lpFont01->Release();
	m_lpFont02->Release();
	m_lpFont03->Release();
	m_lpFont04->Release();
}

TextManager::TextManager()
{
	Init();
}


TextManager::~TextManager()
{
	Release();
}

void TextManager::drawText(TCHAR * str, D3DXVECTOR2 pos, INT size, D3DCOLOR color)
{
	RECT re = { 0 };

	D3DXMATRIX mat;

	D3DXMatrixTranslation(&mat, pos.x, pos.y, 0.0f);
	
	g_lpSprite->SetTransform(&mat);
	
	switch (size)
	{
	case 1:
		m_lpFont01->DrawText(g_lpSprite, str, lstrlen(str), &re, DT_NOCLIP, color);
		break;

	case 2:
		m_lpFont02->DrawText(g_lpSprite, str, lstrlen(str), &re, DT_NOCLIP, color);
		break;
	
	case 3:
		m_lpFont03->DrawText(g_lpSprite, str, lstrlen(str), &re, DT_NOCLIP, color);
		break;

	case 4:
		m_lpFont04->DrawText(g_lpSprite, str, lstrlen(str), &re, DT_NOCLIP, color);
		break;
	}
}
