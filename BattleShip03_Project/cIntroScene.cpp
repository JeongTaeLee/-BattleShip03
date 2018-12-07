#include "DXUT.h"
#include "cIntroScene.h"


cIntroScene::cIntroScene()
{
}


cIntroScene::~cIntroScene()
{
}

void cIntroScene::Init()
{
	m_images = IMAGEMANAGER->FindListImage("Intro");
	m_image = (*m_images)[0];

	m_imageCount = 0;
	m_imageTime = 0;

	SOUNDMANAGER->pPlayBgm(1, 30000);
}

void cIntroScene::Release()
{
	SOUNDMANAGER->pStopBgm();
}

void cIntroScene::Update()
{
	if (m_imageTime < timeGetTime())
	{
		m_imageTime = timeGetTime() + 50;

		if (m_imageCount < 89)
			m_imageCount++;
		else
			SCENEMANAGER->ChangeScene("Menu");

		m_image = (*m_images)[m_imageCount];
	}
}

void cIntroScene::Render()
{
	m_image->CenterRender(WINSIZEX / 2, WINSIZEY / 2, 1, 0);
}
