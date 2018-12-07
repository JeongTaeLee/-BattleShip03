#pragma once
#include "singleton.h"

/* cObjectManager.h 
���ӿ��� ���Ǵ� ������Ʈ�� �����ϴ� ��ü�� �����س��� ����̴�.
cGameObject�� ��ӹ޴� ��ü�� ������ list�� �������� �з��Ͽ� Map�� �����صд�.
����� ��� ������Ʈ �Ҵ��� ������Ʈ ����, ����, ������Ʈ, ������ ���ش�.*/

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
	/* ������Ʈ�� ��Ƴ��� List�� �з��� ���� m_objList*/

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