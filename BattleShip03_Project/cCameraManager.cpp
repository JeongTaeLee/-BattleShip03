#include "DXUT.h"
#include "cCameraManager.h"

#include "cGameObject.h"

void cCameraManager::Init()
{
	/*
	m_stepX = 0;
	m_posX	= 0;

	m_targetPosX = 0;
	m_explosionCount = 0;
	m_maxExplosionCount = 0;
	frame = 0;

	m_cameraState	= E_CAMERAIDLE;
	m_movingCamera	= FALSE;
	m_cameraExplosion = FALSE;
	*/
	m_cameraMode		= E_CAMERAIDLE;
	m_cameraMoving		= FALSE;
	m_cameraExplosion	= FALSE;

	m_cameraTarget	= D3DXVECTOR2(0, 0);
	m_cameraPos		= D3DXVECTOR2(0, 0);
	m_pastPos		= D3DXVECTOR2(0, 0);

	m_frameCount = 0;
}

void cCameraManager::Release()
{
}

cCameraManager::cCameraManager()
{
	Init();
}


cCameraManager::~cCameraManager()
{
	Release();
}

void cCameraManager::Reset()
{
	m_cameraMode		= E_CAMERAIDLE;
	m_cameraMoving		= FALSE;
	m_cameraExplosion	= FALSE;

	m_cameraTarget = D3DXVECTOR2(0, 0);
	m_cameraPos = D3DXVECTOR2(0, 0);
	m_pastPos = D3DXVECTOR2(0, 0);

	m_frameCount = 0;
}


void cCameraManager::Update()
{

	if (m_cameraExplosion)
	{
		if (m_frameCount > 0)
		{
			m_frameCount--;
			m_cameraPos.x += rand() % 21 - 10;
		}
		else
		{
			m_frameCount		= 0;
			m_cameraPos			= m_pastPos;
			m_cameraExplosion	= FALSE;
		}
	}

	Scrool();
}

void cCameraManager::Scrool()
{
	/*
	switch (m_cameraState)
	{
	case E_CAMERAIDLE:

		if ((-5 < INPUTMANAGER->GetMousePos().x && INPUTMANAGER->GetMousePos().x < 100))
		{
			if (m_stepX + 20 < 0)
			{
				m_posX = 20;
				m_stepX += m_posX;
			}
		}

		if ((1820 < INPUTMANAGER->GetMousePos().x  && INPUTMANAGER->GetMousePos().x < 1925))
		{
			if (m_stepX - 20 > -1920)
			{
				m_posX = -20;
				m_stepX += m_posX;
			}
		}

		break;

	case E_CAMERATARGET:
		if (m_targetPosX < m_stepX)
		{
			m_posX = -20;
			m_stepX += m_posX;

			if (m_stepX - 20 < m_targetPosX)
			{
				m_movingCamera	= FALSE;
				m_cameraState	= E_CAMERAIDLE;
			}
		}
		else if (m_targetPosX > m_stepX)
		{
			m_posX = 20;
			m_stepX += m_posX;

			if (m_stepX + 20 > m_targetPosX)
			{
				m_movingCamera = FALSE;
				m_cameraState = E_CAMERAIDLE;
			}
		}

		break;
	}
	*/

	switch (m_cameraMode)
	{
	case E_CAMERAIDLE:
		if (-50 < INPUTMANAGER->GetMousePos().x && INPUTMANAGER->GetMousePos().x < 100)
		{
			if (m_cameraPos.x + 20 < MAXCAMERAX)
				m_cameraPos.x += 20;
		}
		else if (1820 < INPUTMANAGER->GetMousePos().x && INPUTMANAGER->GetMousePos().x < 1970)
		{
			if (m_cameraPos.x - 20 > MINCAMERAX)
				m_cameraPos.x -= 20;
		}
		break;

	case E_CAMERATARGET:
		
		if (m_cameraPos.x < m_cameraTarget.x)
		{
			m_cameraPos.x += 20;
			
			if (m_cameraPos.x + 20 > m_cameraTarget.x)
			{
				m_cameraMode = E_CAMERAIDLE;
				m_cameraMoving = FALSE;
			}
		}
		else if (m_cameraPos.x > m_cameraTarget.x)
		{
			m_cameraPos.x -= 20;

			if (m_cameraPos.x - 20 < m_cameraTarget.x)
			{
				m_cameraMode = E_CAMERAIDLE;
				m_cameraMoving = FALSE;
			}
		}

		break;
	}
}

void cCameraManager::CameraExplosion(int _frame, D3DXVECTOR2 pos)
{
	if (m_cameraExplosion == FALSE)
	{
		m_frameCount = _frame;
		m_pastPos = pos;
		m_cameraExplosion = TRUE;
	}
}

void cCameraManager::SetCameraTarget(D3DXVECTOR2 pos)
{
	if (m_cameraMoving == FALSE)
	{
		m_cameraMoving	= TRUE;
		m_cameraMode	= E_CAMERATARGET;
		m_cameraTarget	= pos;
	}
}

