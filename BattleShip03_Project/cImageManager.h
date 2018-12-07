#pragma once
#include "singleton.h"

/*cImageManager.h 는 게임에서 사용하는 이미지를 관리하는 cImageManager와 
texture 구조체를 선언해 놓은 헤더파일이다.*/

//오브젝트가 texture구조체를 통하여 ImageManager로 접근하여 스프라이트를 화면에 그린다. 
struct texture
{
	LPDIRECT3DTEXTURE9	m_lpTexture;
	D3DXIMAGE_INFO		m_info;

	texture(LPDIRECT3DTEXTURE9 lpTexture, D3DXIMAGE_INFO info) 
		: m_lpTexture(lpTexture), m_info(info)
	{};
	~texture() {};

	void Render(float x, float y, float size, float rot, D3DXVECTOR3 centerPos, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender(float x, float y, float size = 1.0f, float rot = 0.0f, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
};

class cImageManager :
	public singleton<cImageManager> /* singleton을 상속 받았다 이 객체는 프로그램 생성시 단 한번만 생성되고 어디서든 접근할 수 있는 
	객체가되었다.*/
{
private:
	map<string, vector<texture*>*>	m_listImage;
	map<string, texture*>			m_singleImage;
		
	LPD3DXSPRITE					m_lpSprite;
	
	void Init();
	void Release();
public:
	cImageManager() { Init(); }
	~cImageManager() { Release(); };

	void Begin() { m_lpSprite->Begin(D3DXSPRITE_ALPHABLEND); }
	void End() { m_lpSprite->End(); }

	// 애니메이션이 각가의 사진으로 나눠져있을때 AddListImage로 한번에 로드한다.
	vector<texture*> *	AddListImage(const string & key, TCHAR * path, int min, int max);
	// 단일 이미지를 로드하는 AddSingleImage
	texture *			AddSingleImage(const string & key	, TCHAR * path);
	

	vector<texture*> *  FindListImage(const string & key);
	texture			 *	FindImage(const string & key);

	void				DeleteImage(const string & key);
	void				DeleteImageList(const string & key);

	void ResetDevice()	{ m_lpSprite->OnResetDevice(); }
	void LostDevice()	{ m_lpSprite->OnLostDevice(); }

	void Render(texture * _lpTexture, float x, float y, float size, float rot, D3DXVECTOR3 centerPos, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void Render(texture * _lpTexture, float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
};

#define IMAGEMANAGER cImageManager::GetInstance()
// 이 객체를 사용할때마다 객체이름::GetInstance()을 매번 사용하면 귀찮기 떄문에
// 편리하게 사용 할 수 있게 만들어준다
// 모든 Manager객체에 이렇게 되어있음.
