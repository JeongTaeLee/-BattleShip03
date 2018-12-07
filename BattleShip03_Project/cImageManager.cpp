#include "DXUT.h"
#include "cImageManager.h"

extern LPD3DXSPRITE g_lpSprite = nullptr;

void cImageManager::Init()
{
	//LPD3DXSPRITE��? DirectX���� 2D �̹����� ���ϰ� �����ְ����ش�.
	D3DXCreateSprite(g_device, &m_lpSprite);

	g_lpSprite = m_lpSprite;

}

void cImageManager::Release()
{
	for (auto Iter : m_singleImage)
	{
		(*Iter.second).m_lpTexture->Release();
		(*Iter.second).m_lpTexture = nullptr;

		SAFE_DELETE(Iter.second);
	}
	m_singleImage.clear();


	for (auto Iter : m_listImage)
	{
		for (auto Iter02 : (*Iter.second))
		{
			Iter02->m_lpTexture->Release();
			Iter02->m_lpTexture = nullptr;
			SAFE_DELETE(Iter02);
		}
		(*Iter.second).clear();
	
		SAFE_DELETE(Iter.second);
	}
	m_listImage.clear();

	g_lpSprite = nullptr;
	m_lpSprite->Release();
	m_lpSprite = nullptr;
}

vector<texture*>* cImageManager::AddListImage(const string & key, TCHAR * path, int min, int max)
{
	
	auto find = m_listImage.find(key);


	BOOL FailedLoading = FALSE;


	// �̹� �ִ� �̹��� �ɷ�����
	if (find != m_listImage.end())
	{
		DEBUG_LOG("�̹��� �ε� ����");
		DEBUG_LOG(key);
		DEBUG_LOGW(path);
		DEBUG_LOG("�̹� �ִ� �̹��� �Դϴ�");
		DEBUG_LOG("");
		return nullptr;
	}

	vector<texture*> * tempVector = new vector<texture*>;

	for (int i = min; i <= max; i++)
	{
		LPDIRECT3DTEXTURE9	tempLpSprite;
		D3DXIMAGE_INFO		tempInfo;

		TCHAR * tempChar = new TCHAR[lstrlen(path) + 5];

		wsprintf(tempChar, path, i);

		
		if (D3DXCreateTextureFromFileEx(g_device, tempChar, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &tempInfo, nullptr, &tempLpSprite) == S_OK)
		{
			texture * tempText = new texture(tempLpSprite, tempInfo);
			tempVector->push_back(tempText);
		}
		else
		{
			FailedLoading = TRUE;
		
			DEBUG_LOG("FAILED LISTIMAGE");
			DEBUG_LOG("Key : " << key);
			DEBUG_LOGW(tempChar);
			DEBUG_LOG("��θ� Ȯ�����ּ���");
			DEBUG_LOG("");
			break;
		}

		SAFE_DELETE_ARRAY(tempChar);

	}

	if (FailedLoading == FALSE)
	{
		m_listImage.insert(make_pair(key, tempVector));
		return tempVector;
	}

	return nullptr;
}

texture * cImageManager::AddSingleImage(const string & key, TCHAR * path)
{
	auto find = m_singleImage.find(key);
	
	if (find != m_singleImage.end())
	{
		DEBUG_LOG("�̹��� �ε� ����");
		DEBUG_LOG(key);
		DEBUG_LOG(path);
		DEBUG_LOG("�̹� �ִ� �̹��� �Դϴ�");
		DEBUG_LOG("");
		return nullptr;
	}

	LPDIRECT3DTEXTURE9 tempLpTexture;
	D3DXIMAGE_INFO     tempInfo;

	if (D3DXCreateTextureFromFileEx(g_device, path, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &tempInfo, nullptr, &tempLpTexture) == S_OK)
	{
		texture * tempText = new texture(tempLpTexture, tempInfo);

		m_singleImage.insert(make_pair(key, tempText));

		return tempText;
	}
#pragma region ���� �̹��� �ε� ����
	DEBUG_LOG("FAILED SINGLEIMAGE");
	DEBUG_LOG("Key : " << key);
	DEBUG_LOG(path);
	DEBUG_LOG("��θ� Ȯ�����ּ���");
	DEBUG_LOG("");
#pragma endregion ���� �̹��� �ε� ����
	return nullptr;
}

vector<texture*>* cImageManager::FindListImage(const string & key)
{
	auto find = m_listImage.find(key);

	if (find == m_listImage.end())
	{
		DEBUG_LOG("List�̹��� ã�� ����!");
		DEBUG_LOG("Key " << key);
		DEBUG_LOG("�̹����� �����ϴ�");
		DEBUG_LOG("");
	
		return nullptr;
	}

	return (*find).second;
}

texture * cImageManager::FindImage(const string & key)
{
	auto find = m_singleImage.find(key);

	if (find == m_singleImage.end())
	{
		DEBUG_LOG("single�̹��� ã�� ����!");
		DEBUG_LOG("Key " << key);
		DEBUG_LOG("�̹����� �����ϴ�");
		DEBUG_LOG("");

		return nullptr;
	}

	return (*find).second;
}

void cImageManager::DeleteImage(const string & key)
{
	auto find = m_singleImage.find(key);

	if (find == m_singleImage.end())
	{
		DEBUG_LOG("single�̹��� ���� ����!");
		DEBUG_LOG("KEY" << key);
		return;
	}

	find->second->m_lpTexture->Release();
	find->second->m_lpTexture = nullptr;

	SAFE_DELETE(find->second);

	m_singleImage.erase(find);
}

void cImageManager::DeleteImageList(const string & key)
{
	auto find = m_listImage.find(key);

	if (find == m_listImage.end())
	{
		DEBUG_LOG("list�̹��� ���� ����!");
		DEBUG_LOG("Key " << key);
		return;
	}

	for (auto Iter = (*find->second).begin(); Iter != (*find->second).end();)
	{
		(*Iter)->m_lpTexture->Release();
		SAFE_DELETE((*Iter));

		Iter++;
	}
	(*find->second).clear();
	SAFE_DELETE((find->second));

	m_listImage.erase(find);
}

void cImageManager::Render(texture * _lpTexture, float x, float y, float size, float rot, D3DXVECTOR3 centerPos, D3DCOLOR color)
{
	if (_lpTexture)
	{
		D3DXMATRIXA16 mat;

		D3DXMatrixAffineTransformation2D(&mat, size, nullptr, rot, &D3DXVECTOR2(x, y));
		m_lpSprite->SetTransform(&mat);
		m_lpSprite->Draw(_lpTexture->m_lpTexture, nullptr, &centerPos, nullptr, color);
	}
}

void cImageManager::Render(texture * _lpTexture, float x, float y, float size, float rot, D3DCOLOR color)
{
	if (_lpTexture)
	{
		D3DXMATRIXA16 mat;

		D3DXMatrixAffineTransformation2D(&mat, size, nullptr, rot, &D3DXVECTOR2(x - (_lpTexture->m_info.Width / 2), y - (_lpTexture->m_info.Height / 2)));
		m_lpSprite->SetTransform(&mat);
		m_lpSprite->Draw(_lpTexture->m_lpTexture, nullptr, nullptr, nullptr, color);
	}
}


void texture::Render(float x, float y, float size, float rot, D3DXVECTOR3 centerPos, D3DCOLOR color)
{
	IMAGEMANAGER->Render(this, x, y, size, rot, centerPos, color);
}

void texture::CenterRender(float x, float y, float size, float rot, D3DCOLOR color)
{
	IMAGEMANAGER->Render(this, x, y, size, rot, color);


}
