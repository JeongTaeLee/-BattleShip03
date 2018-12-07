#pragma once
#include "singleton.h"

/*cCameraManager : 
게임에서 사용되는 카메라를 관리하는 객체를 선언해놓은 헤더파일이다.
*/

#define MINCAMERAX -1920
#define MAXCAMERAX 0

enum CAMERASTATE {
	E_CAMERAIDLE,
	E_CAMERATARGET
};

class cCameraManager :
	public singleton<cCameraManager>
{
private:
	INT			m_cameraMode;

	D3DXVECTOR2 m_cameraPos;
	D3DXVECTOR2 m_cameraTarget;

	BOOL		m_cameraMoving;

	//화면 진동
	INT				m_frameCount;
	BOOL			m_cameraExplosion;
	D3DXVECTOR2     m_pastPos;

	void Init();
	void Release();
public:
	cCameraManager();
	~cCameraManager();

	void Reset();

	void Update();
	void Scrool();

	void CameraExplosion(int _frame, D3DXVECTOR2 pos);
	void SetCameraTarget(D3DXVECTOR2 pos);

	BOOL		GetCameraMoving() { return m_cameraMoving; }
	D3DXVECTOR2 GetCameraPos() { return m_cameraPos; }


	/*
	BOOL GetMovingCamera() { return m_movingCamera; }
	*/
};

#define CAMERAMANAGER cCameraManager::GetInstance()