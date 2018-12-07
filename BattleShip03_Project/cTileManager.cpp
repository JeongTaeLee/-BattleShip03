#include "DXUT.h"
#include "cTileManager.h"

#include "cTile.h"
#include "cTileObject.h"
#include "cPlayerTIleObject.h"

void cTileManager::Init()
{
	m_playerTileStartPos	= D3DXVECTOR2(650, 317);
	m_enemyTileStartPos		= D3DXVECTOR2(2500, 317);
}

void cTileManager::Release()
{
}

cTileManager::cTileManager()
{
	Init();
}


cTileManager::~cTileManager()
{
	Release();
}

void cTileManager::Reset()
{
	for (INT y = 0; y < TILEMAPY; y++)
	{
		memset(m_playerTileArray[y], NULL, sizeof(cTile*) * TILEMAPX);
		memset(m_enemyTileArray[y],	 NULL, sizeof(cTile*) * TILEMAPX);
	}

	m_playerTileObjList.clear();
}

void cTileManager::CreateTileMap()
{
	for (INT y = 0; y < TILEMAPY; y++)
	{
		for (INT x = 0; x < TILEMAPX; x++)
		{
			D3DXVECTOR2 createPos01;
			createPos01.x = m_playerTileStartPos.x + 70 * x;
			createPos01.y = m_playerTileStartPos.y + 70 * y;

			cTile * playerTile = dynamic_cast<cTile*>(OBJECTMANAGER->AddObject(OBJECTKEY::EPLAYERTILE, new cTile(createPos01, x, y)));
			m_playerTileArray[y][x] = playerTile;

			createPos01.x = m_enemyTileStartPos.x + 70 * x;
			createPos01.y = m_enemyTileStartPos.y + 70 * y;

			cTile * enemyTile = dynamic_cast<cTile*>(OBJECTMANAGER->AddObject(OBJECTKEY::EENEMYTILE, new cTile(createPos01, x, y)));
			m_enemyTileArray[y][x] = enemyTile;
		}
	}
}

cPlayerTileObject* cTileManager::AddTileObject(cPlayerTileObject * object)
{
	OBJECTMANAGER->AddObject(EPLAYERTILEOBJ, object);

	m_playerTileObjList.push_back(dynamic_cast<cPlayerTileObject*>(object));

	return dynamic_cast<cPlayerTileObject*>(object);
}
