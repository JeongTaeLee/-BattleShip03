#pragma once
#include "singleton.h"

/*InputManager.h
게임에서의 마우느나 키보드의 입력을 확인하고 관리하는 객체를 선언해놓은 헤더파일이다.
마우스 입력, 키보드 입력, 마우스의 위치를 관리한다. 
*/

class cInputManager :
	public singleton<cInputManager>
{
private:
	enum KEYSTATE {
		E_KEYDOWN,	// 키가 눌렸을때.
		E_KEYUP,	// 키가 눌렸다 때어졌을때
		E_KEYPRESS, // 키가 눌리고 있을때.
		E_NONEKEY   // 키가 눌리지 않을때.
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