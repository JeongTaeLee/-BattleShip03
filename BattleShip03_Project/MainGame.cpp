#include "DXUT.h"
#include "MainGame.h"
#include "cLoadingScene.h"
#include "cManuScene.h"
#include "cIngameScene.h"
#include "cEndingScene.h"
#include "cIntroScene.h"

#include "cCurSor.h"
MainGame::MainGame()
{
	srand(time(NULL));
}


MainGame::~MainGame()
{
}

void MainGame::Init()
{
	//마우스 안보이게 하기.
	ShowCursor(false);
	
	
	mouse = new cCurSor;

#pragma region SCENE 추가
	SCENEMANAGER->AddScene("Loading",	new cLoadingScene);
	SCENEMANAGER->AddScene("Menu",		new cManuScene);
	SCENEMANAGER->AddScene("Ingame",	new cIngameScene);
	SCENEMANAGER->AddScene("Ending", 	new cEndingScene);
	SCENEMANAGER->AddScene("Intro", new cIntroScene);
#pragma endregion SCENE 추가
	

	// 처음 실행될 Scene
	SCENEMANAGER->ChangeScene("Loading");
}

void MainGame::Release()
{
	// Manager들 해제하기.
	cImageManager::ReleaseInstance();
	cSceneManager::ReleaseInstance();
	cObjectManager::ReleaseInstance();
	TextManager::ReleaseInstance();
	cInputManager::ReleaseInstance();
	cCameraManager::ReleaseInstance();
	cTileManager::ReleaseInstance();
	cGameManager::ReleaseInstance();
	cSoundManager::ReleaseInstance();
	
	SAFE_DELETE(mouse);
	ShowCursor(TRUE);
}

void MainGame::Update()
{
	mouse->Update();
	INPUTMANAGER->Update();
	SOUNDMANAGER->Update();
	SCENEMANAGER->Update();
}

void MainGame::Render()
{
	IMAGEMANAGER->Begin();
	SCENEMANAGER->Render();
	mouse->Render();
	IMAGEMANAGER->End();
}

void MainGame::ResetDevice()
{
	IMAGEMANAGER->ResetDevice();
}

void MainGame::LostDevice()
{
	IMAGEMANAGER->LostDevice();
}
