#pragma once
#include "cGameObject.h"

enum TILESTATE
{
	E_TILEIDLE,
	E_TILEBROKEN
};

class cTile :
	public cGameObject
{
private:
	INT m_arrX;
	INT m_arrY;

	INT		m_tileState;

	BOOL	m_onTile;
	BOOL	m_lightTile;

	DWORD	m_lightTime;

	texture * m_brokenImage;
public:
	cTile(D3DXVECTOR2 pos, INT arrX, INT arrY);
	~cTile();

	virtual void Update() override;
	virtual void Render() override;
	
	void Animation();

	BOOL GetOnTile() { return m_onTile; }
	void SetOnTile(BOOL setBool) { m_onTile = setBool; };
	
	BOOL GetBroken()		{ return m_tileState == E_TILEBROKEN; }
	void SetBrokenTile();

	void LigthTile();

	INT GetArrPosX() { return m_arrX; }
	INT GetArrPosY() { return m_arrY; }
};

