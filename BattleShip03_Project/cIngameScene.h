#pragma once
#include "cScene.h"
class cIngameScene :
	public cScene
{
public:
	cIngameScene();
	~cIngameScene();

	virtual void Init()		override;
	virtual void Release()	override;
	virtual void Update()	override;
	virtual void Render()	override;
};

