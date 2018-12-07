#pragma once
#include "cGameObject.h"
class cFScreen :
	public cGameObject
{
private:
	TCHAR * m_nowText;
	TCHAR * m_bastText;

	RECT rePlayButton;
	RECT mainButton;
public:
	cFScreen();
	~cFScreen();


	virtual void Update()	override;
	virtual void Render()	override;
};

