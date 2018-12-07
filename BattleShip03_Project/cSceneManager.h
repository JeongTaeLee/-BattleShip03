#pragma once
#include "singleton.h"


/*cSceneManager.h
cSceneManager�� ������ Scene�� map���� ������ �����ϴ� ��ü�� ������ ���� ����̴�.
cSceneManager�� �̿��Ͽ� Scene�� �߰��ϰ� Scene�� �ٲ۴�.*/

class cScene;
/*���� ���� �����̶�� ���ε� ���漱���� Ŭ���� �ӿ��� ������ ��ü�� �̸� ������ ���� �س������̴�.(���ϸ� ������)
�����Ϸ����� cScene�̶�� ��ü�� �ִٴ� �͸� �˷��ش�. �׸��� ���漱���� ��ü�� �����ͷθ� ����ؾ��Ѵ�.
�̸� �˷��ֱ⸸�ϰ� ���߿� �� ��������� �����ϴ� �ҽ����Ͽ��� cScene�� ��������� include���ָ� �ȴ�.

cScene * m_nowScene; : �̷��� ����ϴ°� ����������.
cScene m_nowScene; : �̷��� ����ϴ°� �Ұ����ϴ�.

������Ͽ� �ٸ� ��������� include�ϴ°� ��������� ���ϼ��� �ְ� ������ ������ �����ʴ�.
*/
class cSceneManager :
	public singleton<cSceneManager>
{
private:
	map<string, cScene*> m_sceneList;

	cScene * m_nowScene;
	cScene * m_nextScene;
	
	void Init();
	void Release();

public:
	cSceneManager();
	~cSceneManager();

	cScene* AddScene(const string & key, cScene * addScene);
	cScene* ChangeScene(const string & key);

	void Update();
	void Render();
};

#define SCENEMANAGER cSceneManager::GetInstance()
