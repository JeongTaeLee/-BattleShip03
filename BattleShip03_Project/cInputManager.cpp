#include "DXUT.h"
#include "cInputManager.h"


void cInputManager::Init()
{
	memset(m_pastKey, 0, sizeof(m_pastKey));
	memset(m_nowKey, 0, sizeof(m_nowKey));
	memset(m_keyMap, 0, sizeof(m_keyMap));

	m_mousePos = D3DXVECTOR2(0, 0);
	m_mousePoint = { 0 };

	m_mouseState = FALSE;
}

void cInputManager::Release()
{
}

cInputManager::cInputManager()
{
	Init();
}


cInputManager::~cInputManager()
{
	Release();
}

void cInputManager::Update()
{
	memcpy(m_pastKey, m_nowKey, sizeof(m_pastKey));
	memset(m_nowKey, E_NONEKEY, sizeof(m_nowKey));
	memset(m_keyMap, E_NONEKEY, sizeof(m_keyMap));

	GetKeyboardState(m_nowKey);

	for (INT i = 0; i < 256; i++)
	{
		BYTE nKey = m_nowKey[i] & 0x80;
		m_nowKey[i] = nKey ? 1 : 0;

		BYTE nowKey		= m_nowKey[i];
		BYTE pastkey	= m_pastKey[i];
	
		if (nowKey == 1 && pastkey == 0) m_keyMap[i] = E_KEYDOWN;
		else if (nowKey == 0 && pastkey == 1) m_keyMap[i] = E_KEYUP;
		else if (nowKey == 1 && pastkey == 1) m_keyMap[i] = E_KEYPRESS;
		else m_keyMap[i] = E_NONEKEY;
 	}

	GetCursorPos(&m_mousePoint);
	ScreenToClient(DXUTGetHWND(),&m_mousePoint);

	m_mousePos.x = m_mousePoint.x;
	m_mousePos.y = m_mousePoint.y;
}
