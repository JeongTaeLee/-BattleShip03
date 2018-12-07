#pragma once
#include "cGameObject.h"
class cLoopExplosion :
	public cGameObject
{
public:
	cLoopExplosion(D3DXVECTOR2 createPos);
	~cLoopExplosion();

	virtual void Update()	override;
	void Animation();
};

