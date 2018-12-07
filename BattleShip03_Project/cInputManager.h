#pragma once
#include "singleton.h"

/*InputManager.h
���ӿ����� ������� Ű������ �Է��� Ȯ���ϰ� �����ϴ� ��ü�� �����س��� ��������̴�.
���콺 �Է�, Ű���� �Է�, ���콺�� ��ġ�� �����Ѵ�. 
*/

class cInputManager :
	public singleton<cInputManager>
{
private:
	enum KEYSTATE {
		E_KEYDOWN,	// Ű�� ��������.
		E_KEYUP,	// Ű�� ���ȴ� ����������
		E_KEYPRESS, // Ű�� ������ ������.
		E_NONEKEY   // Ű�� ������ ������.
	};

private:
	BYTE m_pastKey[256];
	BYTE m_nowKey[256];	
	BYTE m_keyMap[256];

	D3DXVECTOR2 m_mousePos;
	POINT		m_mousePoint;

	BOOL		m_mouseState;

	void Init();
	void Release();
public:
	cInputManager();
	~cInputManager();

	void Update();

	BOOL KeyDown(INT key)	{ return m_keyMap[key] == E_KEYDOWN; };
	BOOL KeyUp(INT key)		{ return m_keyMap[key] == E_KEYUP; };
	BOOL KeyPress(INT key)	{ return m_keyMap[key] == E_KEYPRESS; };
	
	D3DXVECTOR2 GetMousePos()	{ return m_mousePos; }
	POINT		GetMosuePoint() { return m_mousePoint; }

	void SetMouseState(BOOL setBool) { m_mouseState = setBool; }
	BOOL GetMouseState() { return m_mouseState; }
};

#define INPUTMANAGER cInputManager::GetInstance()