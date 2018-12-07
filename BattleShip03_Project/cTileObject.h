#pragma once
#include "cGameObject.h"

class cTile;

enum TILEOBJSTATE
{
	E_TILEOBJIDLE,
	E_TILEOBJATTACK,
	E_TILEOBJBROKEN
};

class cTileObject :
	public cGameObject
{
protected:
	vector<texture*> * m_rotateIdle;
	vector<texture*> * m_rotateBroken;
	vector<texture*> * m_noneRotateBroken;
	vector<texture*> * m_rotateAttack;
	vector<texture*> * m_noneRotateAttack;

	vector<texture*> * m_debugImages;
	texture* m_debugImage;

	D3DXVECTOR3 m_rotateCenter;
	D3DXVECTOR3 m_noneRotateCenter;

	INT m_arrPosX;
	INT m_arrPosY;

	INT m_lengthX;
	INT m_lengthY;
	
	INT m_tileObjLife;
	INT m_tileObjState;

	BOOL m_broken;
	BOOL m_rotate;

	list<cTile*> m_onTileList;
public:
	cTileObject();
	virtual ~cTileObject();

	virtual void Update()	override {};
	virtual void Render()	override;


	void Animation();
	virtual void SetAttack();
	void DeadCheck();
	void ChangeXY();
	void LifeCount();

	BOOL GetBroken() { return m_broken; }
	INT GetLife() { return m_tileObjLife; }
};

