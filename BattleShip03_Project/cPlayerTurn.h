#pragma once
#include "cGameObject.h"
class cPlayerTurn :
	public cGameObject
{
private:
	BOOL m_printTurn;
	BOOL m_printComplete;

	DWORD m_printTime;
public:
	cPlayerTurn();
	~cPlayerTurn();

	virtual void Update();
	virtual void Render();

	void PrintTurn();
};

