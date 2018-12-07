#pragma once
#include "cGameObject.h"
class cCollocateUi :
	public cGameObject
{
public:
	cCollocateUi();
	~cCollocateUi();

	virtual void Update()	override;
};

