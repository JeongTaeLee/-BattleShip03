#pragma once
#include "cGameObject.h"
class cScoreBorad :
	public cGameObject
{
private:
	TCHAR * m_scoreText;
	TCHAR * m_bastScoreText;
public:
	cScoreBorad();
	~cScoreBorad();

	virtual void Update() override;
	virtual void Render() override;

};

