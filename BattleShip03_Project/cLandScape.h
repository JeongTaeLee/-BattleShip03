#pragma once
#include "cGameObject.h"
class cLandScape :
	public cGameObject
{
public:
	cLandScape();
	~cLandScape();

	virtual void Update()	override;
};

