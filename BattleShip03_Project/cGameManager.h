#pragma once
#include "singleton.h"

enum GAMEMODE
{
	E_COLLOCATEMODE,
	E_INGAMEMODE,
	E_ENDINGMODE
};

enum TURNOWNER
{
	E_NOTURN,
	E_PLAYERTURN,
	E_ENEMYTURN
};

enum WINNER
{
	E_NOWINNER,
	E_PLAYERWINNER,
	E_ENEMYWINNER
};


class cPlayerTurn;
class cEnemyTurn;

class cGameManager :
	public singleton<cGameManager>
{
private:
	INT		m_nowScore;
	INT     m_bastScore;

	INT		m_gameMode;
	INT		m_winner;
	
	INT		m_turnOwner;
	INT		m_nextTurnOwner;


	DWORD	m_changeTime;
	BOOL	m_cameraChange;
	BOOL	m_changeTurn;

	cPlayerTurn * m_playerTurn;
	cEnemyTurn  * m_enemyTurn;

	//ġƮ 
	BOOL		m_f1;
public:
	cGameManager();
	~cGameManager();

	void Reset();

	void	Update();
	void	ChangeTurn();
	void	chitInput();

	void	SetMode(INT gameMode)		{ m_gameMode = gameMode; }
	INT		GetMode()					{ return m_gameMode; }

	void	SetTurnOwner(INT Owner);
	INT		GetTurnOwner()				{ return m_turnOwner; }

	INT & GetScore()		{	return m_nowScore;	}
	INT & GetBastScore()	{	return m_bastScore; }

	INT & GetWinner() { return m_winner; }

	const BOOL & GetF1() { return m_f1; }
};

#define GAMEMANAGER cGameManager::GetInstance()