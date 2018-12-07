#include "DXUT.h"
#include "cManuScene.h"

#include "cButton.h"
#include "cScreen.h"

cManuScene::cManuScene()
{
}


cManuScene::~cManuScene()
{
}

void cManuScene::Init()
{
	SOUNDMANAGER->pPlayBgm(2, 8000);


	OBJECTMANAGER->Reset();

	m_backGround = IMAGEMANAGER->FindImage("Menu_BackGround");

	RECT gameStart = { 1460, 415, 1820, 530 };
	OBJECTMANAGER->AddObject(EFRISTUI, new cButton("Menu_GameStart", D3DXVECTOR2(0, 0),
		[]() { SCENEMANAGER->ChangeScene("Ingame"); }, gameStart, TRUE));

	RECT gameManual = { 1460, 578, 1820, 693 };
	OBJECTMANAGER->AddObject(EFRISTUI, new cButton("Menu_GameManual", D3DXVECTOR2(0, 0),
		[]() { OBJECTMANAGER->AddObject(ESECONDUI, new cScreen("Screen_GameManual")); }, gameManual, TRUE));

	RECT gameAdvice = { 1460, 735, 1820, 851 };
	OBJECTMANAGER->AddObject(EFRISTUI, new cButton("Menu_GameAdvice", D3DXVECTOR2(0, 0),
		[]() { OBJECTMANAGER->AddObject(ESECONDUI, new cScreen("Screen_GameAdvice")); }, gameAdvice, TRUE));

	RECT gameExit = { 1460,915, 1820, 1035 };
	OBJECTMANAGER->AddObject(EFRISTUI, new cButton("Menu_GameExit", D3DXVECTOR2(0, 0),
		[]() { PostQuitMessage(0); }, gameExit, TRUE));
	
}

void cManuScene::Release()
{
	SOUNDMANAGER -> pStopBgm();
}

void cManuScene::Update()
{
	OBJECTMANAGER->Update();
}

void cManuScene::Render()
{
	m_backGround->Render(0, 0, 1, 0, D3DXVECTOR3(0, 0, 0));
	OBJECTMANAGER->Render();
}
