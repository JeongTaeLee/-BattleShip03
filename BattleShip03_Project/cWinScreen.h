#pragma once
#include "cGameObject.h"
class cWinScreen :
	public cGameObject
{
private:
	texture * m_bastClear;

	BOOL      m_bast;

	TCHAR * m_scoreText;
	TCHAR * m_bastText;

	RECT rePlayButton;
	RECT mainButton;
public:
	cWinScreen();
	~cWinScreen();

	virtual void Update();
	virtual void Render();
};

