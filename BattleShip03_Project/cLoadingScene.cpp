#include "DXUT.h"
#include "cLoadingScene.h"


cLoadingScene::cLoadingScene()
{
}


cLoadingScene::~cLoadingScene()
{
}

void cLoadingScene::Init()
{
	m_imageList = IMAGEMANAGER->AddListImage("LoadingImage", L"./Image/Loading/100%02d.png", 0, 20);
	m_image = (*m_imageList)[0];

	m_imageIndex = 0;
	m_imageTime = 0;

	m_thread01End = FALSE;
	m_thread02End = FALSE;
	m_thread03End = FALSE;

	m_thread01 = thread([&]() { Thread01(); }); // 람다식 대체코드.
	m_thread02 = thread([&]() { Thread02(); });
	m_thread03 = thread([&]() { Thread03(); });

	SOUNDMANAGER->AddSound(L"./Sound/IntroSound.wav");
	SOUNDMANAGER->AddSound(L"./Sound/MenuSound.wav");
	SOUNDMANAGER->AddSound(L"./Sound/Explosions.wav");
	SOUNDMANAGER->AddSound(L"./Sound/WINNER.wav");
	SOUNDMANAGER->AddSound(L"./Sound/Ingame.wav");
	SOUNDMANAGER->AddSound(L"./Sound/FAILED.wav");
}

void cLoadingScene::Release()
{
	IMAGEMANAGER->DeleteImageList("LoadingImage");
}

void cLoadingScene::Update()
{
	Sleep(1);


	if (m_imageTime < timeGetTime())
	{
		m_imageTime = timeGetTime() + 60;

		if (m_imageIndex < 19)
			m_imageIndex++;
		else
			m_imageIndex = 0;

		m_image = (*m_imageList)[m_imageIndex];
	}

	if (m_thread01End && m_thread02End && m_thread03End)
	{
		SCENEMANAGER->ChangeScene("Intro");
	}
}

void cLoadingScene::Render()
{
	m_image->CenterRender(CENTERX, CENTERY);
}

void cLoadingScene::Thread01()
{
	IMAGEMANAGER->AddListImage("Intro", L"./Image/Intro/100%02d.jpg", 0, 90);
}

void cLoadingScene::Thread02()
{
	//Tank01
	IMAGEMANAGER->AddListImage("Player_Tank01_NoneRotateIdle", L"./Image/Object/TileObject/Player/Tank01/Idle/NoneRotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank01_RotateIdle", L"./Image/Object/TileObject/Player/Tank01/Idle/Rotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank01_NoneRotateAttack", L"./Image/Object/TileObject/Player/Tank01/Attack/NoneRotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank01_RotateAttack", L"./Image/Object/TileObject/Player/Tank01/Attack/Rotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank01_NoneRotateBroken", L"./Image/Object/TileObject/Player/Tank01/Broken/NoneRotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank01_RotateBroken", L"./Image/Object/TileObject/Player/Tank01/Broken/Rotate/100%02d.png", 0, 20);

	IMAGEMANAGER->AddListImage("Debug_TileObject01", L"./Image/Object/TileObject/Debug/2_1DebugObject%02d.png", 1, 2);
	
	//Tank02
	IMAGEMANAGER->AddListImage("Player_Tank02_NoneRotateIdle", L"./Image/Object/TileObject/Player/Tank02/Idle/NoneRotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank02_RotateIdle", L"./Image/Object/TileObject/Player/Tank02/Idle/Rotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank02_NoneRotateAttack", L"./Image/Object/TileObject/Player/Tank02/Attack/NoneRotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank02_RotateAttack", L"./Image/Object/TileObject/Player/Tank02/Attack/Rotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank02_NoneRotateBroken", L"./Image/Object/TileObject/Player/Tank02/Broken/NoneRotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank02_RotateBroken", L"./Image/Object/TileObject/Player/Tank02/Broken/Rotate/100%02d.png", 0, 20);

	IMAGEMANAGER->AddListImage("Debug_TileObject02", L"./Image/Object/TileObject/Debug/3_1DebugObject%02d.png", 1, 2);

	//Tank03
	IMAGEMANAGER->AddListImage("Player_Tank03_NoneRotateIdle", L"./Image/Object/TileObject/Player/Tank03/Idle/NoneRotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank03_RotateIdle", L"./Image/Object/TileObject/Player/Tank03/Idle/Rotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank03_NoneRotateAttack", L"./Image/Object/TileObject/Player/Tank03/Attack/NoneRotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank03_RotateAttack", L"./Image/Object/TileObject/Player/Tank03/Attack/Rotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank03_NoneRotateBroken", L"./Image/Object/TileObject/Player/Tank03/Broken/NoneRotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Player_Tank03_RotateBroken", L"./Image/Object/TileObject/Player/Tank03/Broken/Rotate/100%02d.png", 0, 20);

	IMAGEMANAGER->AddListImage("Debug_TileObject03", L"./Image/Object/TileObject/Debug/4_1DebugObject%02d.png", 1, 2);


	m_thread02End = TRUE;
}

void cLoadingScene::Thread03()
{
	//Enemy
	IMAGEMANAGER->AddListImage("Enemy_Tank01_NoneRotate",L"./Image/Object/TileObject/EnemyTileObject/Tank01/Image/NoneRotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Enemy_Tank01_Rotate", L"./Image/Object/TileObject/EnemyTileObject/Tank01/Image/Rotate/100%02d.png", 0, 20);
	
	IMAGEMANAGER->AddListImage("Enemy_Tank02_NoneRotate", L"./Image/Object/TileObject/EnemyTileObject/Tank02/Image/NoneRotate/100%02d.png",0, 20);
	IMAGEMANAGER->AddListImage("Enemy_Tank02_Rotate", L"./Image/Object/TileObject/EnemyTileObject/Tank02/Image/Rotate/100%02d.png", 0, 20);
	
	IMAGEMANAGER->AddListImage("Enemy_Tank03_NoneRotate", L"./Image/Object/TileObject/EnemyTileObject/Tank03/Image/NoneRotate/100%02d.png", 0, 20);
	IMAGEMANAGER->AddListImage("Enemy_Tank03_Rotate", L"./Image/Object/TileObject/EnemyTileObject/Tank03/Image/Rotate/100%02d.png", 0, 20);

	//CollocateUi
	IMAGEMANAGER->AddSingleImage("Ui_CollocateInterface", L"./Image/Ui/CollocateUi/CollocateInterface.png");

	//IngameUi
	IMAGEMANAGER->AddSingleImage("Ui_ScoreBoard", L"./Image/Ui/IngameUi/ScoreBoard/ScoreBoard.png");
	IMAGEMANAGER->AddSingleImage("Ui_StateBoard", L"./Image/Ui/IngameUi/StateBorad/StateBoard.png");
	IMAGEMANAGER->AddListImage("Ui_2TileState", L"./Image/Ui/IngameUi/StateBorad/StateBar/2Tiles/%d.png", 0, 2);
	IMAGEMANAGER->AddListImage("Ui_3TileState", L"./Image/Ui/IngameUi/StateBorad/StateBar/3Tiles/%d.png", 0, 3);
	IMAGEMANAGER->AddListImage("Ui_4TileState", L"./Image/Ui/IngameUi/StateBorad/StateBar/4Tiles/%d.png", 0, 4);

	IMAGEMANAGER->AddSingleImage("Ui_EnemyTurn", L"./Image/Ui/IngameUi/TurnUi/enemyTurn.png");
	IMAGEMANAGER->AddSingleImage("Ui_PlayerTurn", L"./Image/Ui/IngameUi/TurnUi/playerTurn.png");

	IMAGEMANAGER->AddSingleImage("Menu_BackGround", L"./Image/Ui/Menu/BackGround.png");

	IMAGEMANAGER->AddListImage("Menu_GameStart", L"./Image/Ui/Menu/GameButton/GameStart%02d.png", 1, 2);
	IMAGEMANAGER->AddListImage("Menu_GameAdvice", L"./Image/Ui/Menu/GameButton/GameAdvice%02d.png", 1, 2);
	IMAGEMANAGER->AddListImage("Menu_GameManual", L"./Image/Ui/Menu/GameButton/GameManual%02d.png", 1, 2);
	IMAGEMANAGER->AddListImage("Menu_GameExit", L"./Image/Ui/Menu/GameButton/GameExit%02d.png", 1, 2);

	IMAGEMANAGER->AddSingleImage("Screen_GameManual", L"./Image/Ui/Menu/Screen/GameManual.png");
	IMAGEMANAGER->AddSingleImage("Screen_GameAdvice", L"./Image/Ui/Menu/Screen/GameAdivce.png");

	IMAGEMANAGER->AddSingleImage("Screen_GameClear", L"./Image/Ui/Menu/Screen/GameClear/GameClear.png");
	IMAGEMANAGER->AddSingleImage("Screen_GameBastClear", L"./Image/Ui/Menu/Screen/GameClear/BastClear.png");

	IMAGEMANAGER->AddSingleImage("Screen_GameOver", L"./Image/Ui/Menu/Screen/GameOver.png");

	//TILE
	IMAGEMANAGER->AddListImage("Tile", L"./Image/Object/Tile/tile%02d.png", 1, 2);
	IMAGEMANAGER->AddSingleImage("Tile_BrokenTile", L"./Image/Object/Tile/BrokenTile.png");
	IMAGEMANAGER->AddSingleImage("Tile_OnTile", L"./Image/Object/Tile/OnObject.png");

	//IBackGround
	//Ingame
	IMAGEMANAGER->AddSingleImage("Ingame_LandScape", L"./Image/BackGround/Ingame/LandScape.png");
	IMAGEMANAGER->AddSingleImage("Ingame_Land", L"./Image/BackGround/Ingame/Land.png");
	m_thread01End = TRUE;

	//Explosions
	IMAGEMANAGER->AddListImage("Explosion_NoTileExplosion", L"./Image/Object/Explosions/NoTileExplosion/%d.png", 1, 8);
	IMAGEMANAGER->AddListImage("Explosion_OnTileExplosion", L"./Image/Object/Explosions/OnTileExplosion/%d.png", 1, 7);
	IMAGEMANAGER->AddListImage("Explosion_MainExplosion", L"./Image/Object/Explosions/TileObjectExplosion/100%02d.png", 1, 36);
	IMAGEMANAGER->AddListImage("Explosion_SmokeExplosion", L"./Image/Object/Explosions/SmokeExplosion/%d.png", 1, 7);
	


	m_thread03End = TRUE;
}
