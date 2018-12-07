#pragma once
#include "cGameObject.h"

class cTile;

enum AISTATE
{
	E_HUNTMODE,
	E_TARGETMODE
};

enum AIDIRECTION
{
	E_BOTTOMDIRECTION,
	E_LEFTDIRECTION,
	E_TOPDIRECTION,
	E_RIGHTDIRECTION
};

class cAi :
	public cGameObject
{
private:
	INT m_aiMode;
	INT m_aiDirection;

	BOOL	m_pickTile;
	INT		m_pickCount;
	DWORD	m_pickTime;

	DWORD   m_delayTime;

	cTile * m_nowTile;
	cTile * m_pivotTile;
public:
	cAi();
	~cAi();

	void Init();

	virtual void Update() override;
	virtual void Render() override;

	void Attack();
	
	void PickTile();
	void HuntMode();
	void TargetMode();
};

