#pragma once
#include "singleton.h"

/*cImageManager.h �� ���ӿ��� ����ϴ� �̹����� �����ϴ� cImageManager�� 
texture ����ü�� ������ ���� ��������̴�.*/

//������Ʈ�� texture����ü�� ���Ͽ� ImageManager�� �����Ͽ� ��������Ʈ�� ȭ�鿡 �׸���. 
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
	public singleton<cImageManager> /* singleton�� ��� �޾Ҵ� �� ��ü�� ���α׷� ������ �� �ѹ��� �����ǰ� ��𼭵� ������ �� �ִ� 
	��ü���Ǿ���.*/
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

	// �ִϸ��̼��� ������ �������� ������������ AddListImage�� �ѹ��� �ε��Ѵ�.
	vector<texture*> *	AddListImage(const string & key, TCHAR * path, int min, int max);
	// ���� �̹����� �ε��ϴ� AddSingleImage
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
// �� ��ü�� ����Ҷ����� ��ü�̸�::GetInstance()�� �Ź� ����ϸ� ������ ������
// ���ϰ� ��� �� �� �ְ� ������ش�
// ��� Manager��ü�� �̷��� �Ǿ�����.
