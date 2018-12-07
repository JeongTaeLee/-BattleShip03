#pragma once
class cScene
{
private:

public:
	cScene();
	~cScene();

	/* 순수 가상함수이다. 순수 가상함수란 선언한 부모클래스에서 자식클래스에게 정의를 미루는 것이다. 
	PURE나 = 0을 붙여주면 순수 가상함수가 된다.  그리고 순수가상 함수가 있다면 그 클래스는 추상클래스가된다.
	추상클래스가되면 그 클래스는 인스턴스를 만들지 못하게된다(인스턴스: 메모리에 실제로 할당되는것.) 추상 클래스가되면
	자식클래스를 파생시켜서 자식클래스가 순수가상함수를 정의 해주면 해당 자식클래스로부터 인스턴스를 다시 생성할 수 있다.*/
	
	// virtual void Init()	= 0;
	virtual void Init()		PURE;
	virtual void Release()	PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
};

