#pragma once
#include "cTileObject.h"
class cEnemyTileObject :
	public cTileObject
{
public:
	cEnemyTileObject();
	~cEnemyTileObject();

	void Init(const string & key);
	
	void Update();
	void Animation();

	virtual void Render()	override;

	BOOL Collocate();
};

