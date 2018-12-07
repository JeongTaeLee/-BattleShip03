#pragma once
#include "cGameObject.h"
enum ATTACKSTATE
{
	E_ATTACKPICK,
	E_ATTACKMOTION,
	E_ATTACKTILE
};

class cPlayer :
	public cGameObject
{
private:
	BOOL	m_attackComplete;

	DWORD	m_deleyTurnTime;
	DWORD   m_attackTime;

	INT		m_attackTileX;
	INT		m_attackTileY;
	INT     m_attackState;

	INT		m_addScore;
public:
	cPlayer();
	~cPlayer();

	virtual void Update()	override;

	void Attack();
	void PickAttackTile();
	void AttackMotion();
	void AttackTile();

	virtual void Render()	override;

};

