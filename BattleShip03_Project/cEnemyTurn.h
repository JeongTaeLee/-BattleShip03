#pragma once
#include "cGameObject.h"

class cEnemyTurn
	:public cGameObject
{
private:
	BOOL m_printTurn;
	BOOL m_printComplete;

	DWORD m_printTime;
public:
	cEnemyTurn();
	~cEnemyTurn();

	virtual void Update()	override;
	virtual void Render()	override;

	void PrintTurn();
};

