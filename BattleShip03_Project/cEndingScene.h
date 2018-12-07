#pragma once
#include "cScene.h"
class cEndingScene :
	public cScene
{
public:
	cEndingScene();
	~cEndingScene();

	virtual void Init()		override;
	virtual void Release()	override;
	virtual void Update()	override;
	virtual void Render()	override;
};

