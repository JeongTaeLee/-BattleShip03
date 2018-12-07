#pragma once
#include "cGameObject.h"

class cLand
	:public cGameObject
{
public:
	cLand();
	~cLand();

	virtual void Update()	override;
};

