#pragma once
#include "GameObject.h"



class Frieto :
    public GameObject
{
	enum class Frieto_State
	{
		First,
		Second,
		Third,
		End,
	};

public:
	Frieto();
	~Frieto();

	void Initialize()  override;
	void Update()	   override;
	void LateUpdate()  override;
	void Render()	   override;
	void Release()	   override;

private:
	bool Check_Rect();

	void First(class MyDialogBox* _pBox);
	void Second(MyDialogBox* _pBox);
	void Third(MyDialogBox* _pBox);

	void Drop_Item();
private:
	JoTexture* m_pTexture;
	JoTexture* m_pDialNameTex;
	JoTexture* m_pDialTex;

	vector<pair<wstring, int>> m_vecDials;
	vector<pair<wstring, int>> m_vecDials2;
	vector<pair<wstring, int>> m_vecDials3;

	RECT	   m_tRect;

	bool		m_bSuccessed;

	Frieto_State m_eState;

	function<void()> ChangeScene_ToGame;
};

