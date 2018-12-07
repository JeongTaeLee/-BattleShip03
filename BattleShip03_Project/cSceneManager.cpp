#include "DXUT.h"
#include "cSceneManager.h"

#include "cScene.h"
void cSceneManager::Init()
{
	m_nowScene = nullptr;
	m_nextScene = nullptr;
}

void cSceneManager::Release()
{
	if(m_nowScene)
		m_nowScene->Release();

	m_nowScene	= nullptr;
	m_nextScene = nullptr;
	
	for (auto Iter : m_sceneList)
	{
		SAFE_DELETE(Iter.second);
	}
	m_sceneList.clear();
}

cSceneManager::cSceneManager()
{
	Init();
}


cSceneManager::~cSceneManager()
{
	Release();
}

cScene* cSceneManager::AddScene(const string & key, cScene * addScene)
{
	auto find = m_sceneList.find(key);

	if (find != m_sceneList.end())
	{
		DEBUG_LOG("FAILED AddScene");
		DEBUG_LOG("Key :" << key);
		DEBUG_LOG("이미 있는 Scene입니다.");

		return nullptr;
	}

	m_sceneList.insert(make_pair(key, addScene));

	return addScene;
}

cScene * cSceneManager::ChangeScene(const string & key)
{
	auto find = m_sceneList.find(key);

	if (find == m_sceneList.end())
	{
		DEBUG_LOG("FAILED ChangeScene");
		DEBUG_LOG("Key :" << key);
		DEBUG_LOG("바꿀 scene 없는니다");
		return nullptr;
	}
    
	m_nextScene = find->second;

	return m_nextScene;
}

void cSceneManager::Update()
{
	if (m_nextScene)
	{
		if (m_nowScene)
		{
			m_nowScene->Release();
			m_nowScene = nullptr;
		}
		m_nextScene->Init();
		m_nowScene	= m_nextScene;
		m_nextScene = nullptr;
	}
	else if (m_nowScene)
		m_nowScene->Update();
}

void cSceneManager::Render()
{
	if (m_nowScene)
		m_nowScene->Render();
}
