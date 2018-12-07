#pragma once
#include "cScene.h"
class cIntroScene :
	public cScene
{
private:
	vector<texture*>* m_images;
	texture * m_image;

	INT m_imageCount;
	DWORD m_imageTime;
public:
	cIntroScene();
	~cIntroScene();

	virtual void Init()		override;
	virtual void Release()	override;
	virtual void Update()	override;
	virtual void Render()	override;
};

