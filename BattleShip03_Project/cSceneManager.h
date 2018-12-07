#pragma once
#include "singleton.h"


/*cSceneManager.h
cSceneManager는 각각의 Scene을 map으로 저장해 관리하는 객체를 선언해 놓은 헤더이다.
cSceneManager를 이용하여 Scene을 추가하고 Scene을 바꾼다.*/

class cScene;
/*위는 전방 선언이라는 것인데 전방선언은 클래스 속에서 참조할 객체를 미리 위에다 선언 해놓은것이다.(안하면 오류남)
컴파일러한태 cScene이라는 객체가 있다는 것만 알려준다. 그리고 전방선언한 객체는 포인터로만 사용해야한다.
미리 알려주기만하고 나중에 이 헤더파일을 정의하는 소스파일에서 cScene의 헤더파일을 include해주면 된다.

cScene * m_nowScene; : 이렇게 사용하는건 가능하지만.
cScene m_nowScene; : 이렇게 사용하는건 불가능하다.

헤더파일에 다른 헤더파일을 include하는건 헤더파일이 꼬일수도 있고 느리기 때문에 좋지않다.
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
