#pragma once

/*cGameObject.h 
�ش� ���ӿ����� ��ü���� ��κ� cGameObject�� ��ӹ޴´�. 
������ cGameObject�� ��� ������ cObjectManager���� List�� �����Ͽ�
�����ϱ� ���ϱ� �����̴�.
*/

class cGameObject
{
protected:
	vector<texture*>	* m_imageList;
	texture				* m_image;

	LPOBJINFO m_info;
	LPANIINFO m_aniInfo;

	BOOL m_deleteObject;
public:
	cGameObject();
	virtual ~cGameObject();

	void Init(const string & key, LPOBJINFO info, LPANIINFO aniINfo);

	virtual void Update() PURE;
	virtual void Render();

	bool operator <(cGameObject * a)
	{
		return m_info->m_pos.y < a->GetPos().y;
	}


	void			SetDelete(BOOL setBool) { m_deleteObject = setBool; }
	BOOL	&		GetDelete()				{ return m_deleteObject; }

	D3DXVECTOR2&	GetPos()					{ return m_info->m_pos; }
	LPOBJINFO		GetInfo()					{ return m_info; }
	RECT &			GetRect()					{ return m_info->m_collRect; }
};



