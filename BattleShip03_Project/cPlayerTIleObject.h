#pragma once
#include "cTileObject.h"

enum COLLOCATESTATE
{
	E_COLLOCATEIDLE,
	E_COLLOCATEMOVE,
	E_COLLOCATEDROP,
};

class cPlayerTileObject :
	public cTileObject
{
private:
	INT m_collocateState;

public:
	cPlayerTileObject();
	~cPlayerTileObject();

	void Init(const string & key, D3DXVECTOR2 pos, BOOL autoColl);
	
	virtual void Update()	override;

	BOOL CollocateAuto();
	void Collocate();
	virtual void SetAttack()	override;
	BOOL PickTile();
	BOOL DropTile();
};

