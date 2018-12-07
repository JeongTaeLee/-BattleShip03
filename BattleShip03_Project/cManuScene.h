#pragma once
#include "cScene.h"
class cManuScene :
	public cScene
{
private:
	texture * m_backGround;
public:
	cManuScene();
	~cManuScene();

	virtual void Init()		override;
	virtual void Release()	override;
	virtual void Update()	override;
	virtual void Render()	override;
};

