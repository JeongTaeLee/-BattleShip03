#pragma once
#include "cGameObject.h"
class cExplosion :
	public cGameObject
{
public:
	cExplosion(const string & key, D3DXVECTOR2 pos, INT maxIndex, DWORD frameTime, float size = 1.0f);
	~cExplosion();

	virtual void Update() override;
	void Animation();
};

