#pragma once
#include "singleton.h"

#define TILEMAPX 10
#define TILEMAPY 10

class cTile;
class cTileObject;
class cGameObject;
class cPlayerTileObject;

class cTileManager :
	public singleton<cTileManager>
{
private:
	cTile * m_playerTileArray[TILEMAPY][TILEMAPX];
	cTile * m_enemyTileArray[TILEMAPY][TILEMAPX];
	D3DXVECTOR2 m_playerTileStartPos;
	D3DXVECTOR2 m_enemyTileStartPos;


	void Init();
	void Release();
public:
	list<cPlayerTileObject*> m_playerTileObjList;
	
	cTileManager();
	~cTileManager();

	void Reset();

	void CreateTileMap();

	cPlayerTileObject* AddTileObject(cPlayerTileObject * object);

	cTile * (*GetPlayerTileArray(void))[TILEMAPX] { return m_playerTileArray; }// 가로사이즈가 들어가야함.
	cTile * (*GetEnemyTileArray(void))[TILEMAPX] { return m_enemyTileArray; }
};

#define TILEMANAGER cTileManager::GetInstance()