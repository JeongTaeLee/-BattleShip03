#pragma once
#include "cScene.h"
class cLoadingScene :
	public cScene
{
private:
	vector<texture*>*	m_imageList;
	texture *			m_image;
		
	thread				m_thread01;
	thread				m_thread02;
	thread				m_thread03;

	INT				m_imageIndex;
	DWORD			m_imageTime;

	BOOL		m_thread01End;
	BOOL		m_thread02End;
	BOOL		m_thread03End;
public:
	cLoadingScene();
	~cLoadingScene();

	virtual void Init()		override;
	virtual void Release()	override;
	virtual void Update()	override;
	virtual void Render()	override;


	void Thread01();
	void Thread02();
	void Thread03();
};

