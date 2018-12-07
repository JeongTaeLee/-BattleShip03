
#include "DXUT.h"
#include "cSoundManager.h"

void cSoundManager::Init()
{
	m_deviceID = 0;

	bgm_index = 0;
	bgm_time = 0;
	change_time = 0;
}

void cSoundManager::Release()
{
	int i = 1;
	for (auto Iter : m_sounds)
		mciSendCommand(i++, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);

	m_sounds.clear();
}

cSoundManager::cSoundManager()
{
	Init();
}


cSoundManager::~cSoundManager()
{
	Release();

}

void cSoundManager::Update()
{
	if (bgm_index != 0)
	{
		if (change_time < timeGetTime())
		{
			pPlaySound(bgm_index);
			change_time = timeGetTime() + bgm_time;
		}
	}

}

DWORD cSoundManager::LoadWAV(HWND hWnd, LPCTSTR lpszWave)
{
	DWORD result = 0;

	m_mciOpen.lpstrDeviceType = L"WaveAudio";

	m_mciOpen.lpstrElementName = lpszWave;

	result = mciSendCommand(m_deviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&m_mciOpen);

	if (result)
		return result;

	m_deviceID = m_mciOpen.wDeviceID;

	m_mciPlay.dwCallback = (DWORD)(hWnd);

	if (result)
		return result;


	return 0;
}

DWORD cSoundManager::LoadMp3(HWND hWnd, LPCTSTR lpszMp3)
{
	DWORD result;

	m_mciOpen.lpstrDeviceType = L"MPEGVideo";
	m_mciOpen.lpstrElementName = lpszMp3;

	result = mciSendCommand(m_deviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&m_mciOpen);

	if (result)
		return result;

	m_deviceID = m_mciOpen.wDeviceID;

	m_mciPlay.dwCallback = (DWORD)(hWnd);

	if (result)
		return result;

	return 0;
}

void cSoundManager::AddSound(LPCTSTR lpszWave)
{
	m_sounds.push_back(LoadWAV(DXUTGetHWND(), lpszWave));
}

void cSoundManager::pPlayBgm(int index, DWORD ch_time)
{
	if (bgm_index != 0)
	{
		m_sounds[index - 1] = mciSendCommand(index, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&m_mciPlay);
		m_sounds[index - 1] = mciSendCommand(index, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlay);
	}

	bgm_index = index;
	bgm_time = ch_time + 1000;

	change_time = 0;
}

void cSoundManager::pStopBgm()
{
	pStopSOund(bgm_index);
	bgm_index = 0;
}

void cSoundManager::pPlaySound(int index)
{
	m_sounds[index - 1] = mciSendCommand(index, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&m_mciPlay);
	m_sounds[index - 1] = mciSendCommand(index, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlay);
}

void cSoundManager::pStopSOund(int index)
{
	m_sounds[index - 1] = mciSendCommand(index, MCI_SEEK, MCI_SEEK_TO_END, (DWORD)(LPVOID)&m_mciPlay);
}

