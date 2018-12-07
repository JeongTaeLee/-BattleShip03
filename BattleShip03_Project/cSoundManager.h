#pragma once
#include "singleton.h"
/*cSoundManager.h
���ӿ����� Sound�� �����ϴ� ��ü�� �����س��� ��������̴�.

MCI��� ���� ���̺귯���� ����Ͽ� ���带 �ε�, ���, ���� �Ѵ�.
*/

class cSoundManager :
	public singleton<cSoundManager>
{
private:
	MCI_OPEN_PARMS		m_mciOpen;
	MCI_PLAY_PARMS		m_mciPlay;
	PMCI_STATUS_PARMS	m_mciStatus;

	UINT m_deviceID;

	vector<DWORD> m_sounds;

	INT bgm_index;

	DWORD bgm_time;
	DWORD change_time;


	void Init();
	void Release();
public:
	cSoundManager();
	~cSoundManager();

	void Update();

	DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);
	DWORD LoadMp3(HWND hWnd, LPCTSTR lpszMp3);

	void AddSound(LPCTSTR lpszWave);
	void pPlayBgm(int index, DWORD ch_time);
	void pStopBgm();


	void pPlaySound(int index);
	void pStopSOund(int index);


};

#define SOUNDMANAGER cSoundManager::GetInstance()