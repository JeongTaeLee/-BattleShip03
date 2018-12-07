#pragma once

/*cGameObject.h 
해당 게임에서의 객체들은 대부분 cGameObject를 상속받는다. 
이유는 cGameObject를 상속 받으면 cObjectManager에서 List의 저장하여
관리하기 편하기 때문이다.
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



