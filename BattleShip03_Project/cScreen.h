#pragma once
#include "cGameObject.h"
class cScreen :
	public cGameObject
{
public:
	cScreen(const string & key);
	~cScreen();
	
	virtual void Update() override;
};

