#pragma once
#include "cGameObject.h"

class cTileObject;

struct HpBar
{
public:
	vector<texture*> * m_images;
	texture *		 m_image;

	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 * m_standardPos;
	D3DXVECTOR2 m_addPos;

	cTileObject * m_tileObject;

public:
	HpBar(D3DXVECTOR2 * standardPos, D3DXVECTOR2 addPos, cGameObject* tileObject);
	~HpBar();
	void Update();
	void Render();
};

class cStateBorad :
	public cGameObject
{
private:
	BOOL	m_printUi;

	vector<HpBar*> m_hpBarList;
public:
	cStateBorad();
	~cStateBorad();

	virtual void Update() override;
	virtual void Render() override;
};

