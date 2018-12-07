#pragma once

//singleton.h
/* 싱글톤 프로그램이 시작될때 한번만 메모리에 할당하는 디자인 패턴이다.*/

/*
싱글톤을 사용하는 이유
1. 단 한번만 생성되기 때문에 메모리 낭비를 방지할 수 있음.

2. 클래스를 전역변수처럼 사용할 수 있기 때문에 헤더만 참조 한다면 어디서든 데이터를 공유할 수 있음.
	(cImageManager 객체와 같은 프로그램에서 단 한번만 생성되야하는 객체나 여러 객체와 정보를 공유하는 클래스의 사용함.)

싱글톤 단점.
1. 객체들끼리 연관성이 높아짐(한번 만들면 수정하기 어려움 수정한다면 해당 싱글톤 객체와 데이터를 공유하는 모든객체를 수정해야 할 수도 있음.)

*꼭 필요한 곳에만 적절히 사용하면 좋음*

해당 프로젝트에서 Manager가 붙은 클래스는 singleton을 상속함
*/


template <class T>
class singleton
{
private:
	static T * p; // 클래스 속 static 변수는 클래스 밖에서 초기화 해줘야함. (해당 헤더 48 ~ 49줄)
public:
	singleton() { }
	virtual ~singleton() {}
	// 부모클래스라면 virtual을 해주는게 좋다. 그래야 상속받는 클래스의 소멸자까지 호출된다.

	static T * GetInstance() { // 이 함수로 생성한 싱글톤 객체를 얻어온다.
	
		if (!p) // 싱글톤 객체가 NULL(생성이 안됐을때) 
			p = new T; // 생성해준다.

		return p; // 반환 해준다.
	}

	static void ReleaseInstance() { // 생성된 싱글톤 객체를 해제해준다.
		if (p) 
			delete p;// 생성됐다면 해제해준다.
		
		p = nullptr;
	}
};

template<class T>
T * singleton<T>::p = nullptr;