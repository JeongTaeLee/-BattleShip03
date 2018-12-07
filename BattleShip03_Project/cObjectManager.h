#pragma once
#include "singleton.h"

/* cObjectManager.h 
게임에서 사용되는 오브젝트를 관리하는 객체를 선언해놓은 헤더이다.
cGameObject를 상속받는 객체를 저장한 list를 종류별로 분류하여 Map에 저장해둔다.
저장된 모든 오브젝트 할당한 오브젝트 저장, 해제, 업데이트, 렌더를 해준다.*/

enum OBJECTKEY {
	EFRISTMAP,
	ESECONDMAP,
	EPLAYERTILE,
	EENEMYTILE,
	EPLAYERTILEOBJ,
	EENEMYTILEOBJ,
	EEXPLOSIONS,
	EFRISTUI,
	ESECONDUI,
	EADMIN
};

class cGameObject;

class cObjectManager :
	public singleton<cObjectManager>
{
private:
	map<INT, list<cGameObject*>* > m_objList; 
	/* 오브젝트를 모아놓은 List를 분류해 놓은 m_objList*/

	void Init();
	void Release();
public:
	cObjectManager();
	~cObjectManager();

	cGameObject* AddObject(INT key, cGameObject* addObject);
	list<cGameObject*>* GetGameObject(INT key);
	void Reset();
	
	void Update();
	void Render();

};

#define OBJECTMANAGER cObjectManager::GetInstance()