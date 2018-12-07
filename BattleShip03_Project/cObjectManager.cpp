#include "DXUT.h"
#include "cObjectManager.h"

#include "cGameObject.h"

void cObjectManager::Init()
{
	m_objList.insert(make_pair(EFRISTMAP, new list<cGameObject*>));
	m_objList.insert(make_pair(ESECONDMAP, new list<cGameObject*>));
	m_objList.insert(make_pair(EPLAYERTILE, new list<cGameObject*>));
	m_objList.insert(make_pair(EENEMYTILE, new list<cGameObject*>));
	m_objList.insert(make_pair(EPLAYERTILEOBJ, new list<cGameObject*>));
	m_objList.insert(make_pair(EENEMYTILEOBJ, new list<cGameObject*>));
	m_objList.insert(make_pair(EEXPLOSIONS, new list<cGameObject*>));
	m_objList.insert(make_pair(EFRISTUI, new list<cGameObject*>));
	m_objList.insert(make_pair(ESECONDUI, new list<cGameObject*>));
	m_objList.insert(make_pair(EADMIN, new list<cGameObject*>));
}

void cObjectManager::Release()
{
	Reset();

	for (auto Iter : m_objList)
	{
		(*Iter.second).clear();
		SAFE_DELETE(Iter.second);
	}
	m_objList.clear();

}

cObjectManager::cObjectManager()
{
	Init();
}


cObjectManager::~cObjectManager()
{
	Release();
}

cGameObject * cObjectManager::AddObject(INT key, cGameObject * addObject)
{
	auto find = m_objList.find(key);

	if (find == m_objList.end())
		return nullptr;

	find->second->push_back(addObject);
	
	return addObject;
}

list<cGameObject*>* cObjectManager::GetGameObject(INT key)
{
	auto find = m_objList.find(key);

	if (find == m_objList.end())
		return nullptr;

	return find->second;
}

void cObjectManager::Reset()
{
	for (auto Iter : m_objList)
	{
		for (auto Iter02 : (*Iter.second))
		{
			SAFE_DELETE(Iter02);
		}
		(*Iter.second).clear();
	}
}

void cObjectManager::Update()
{
	for (auto Iter : m_objList)
	{
		for (auto Iter02 : (*Iter.second))
		{
			Iter02->Update(); 
		}
	}

	for (auto Iter : m_objList)
	{
		for (auto Iter02 = (*Iter.second).begin(); Iter02 != (*Iter.second).end();)
		{
			if ((*Iter02)->GetDelete())
			{
				SAFE_DELETE((*Iter02));
				Iter02 = (*Iter.second).erase(Iter02);
			}
			else
				Iter02++;
		}
	}
}

void cObjectManager::Render()
{
	(*OBJECTMANAGER->GetGameObject(EPLAYERTILEOBJ)).sort(compare);
	(*OBJECTMANAGER->GetGameObject(EENEMYTILEOBJ)).sort(compare);

	for (auto Iter : m_objList)
	{
		for (auto Iter02 : (*Iter.second))
		{
			Iter02->Render();
		}
	}
}
