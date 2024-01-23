#include "ResourceMgr.h"

map<wstring, JoResource*> ResourceMgr::m_resources{};


void ResourceMgr::Initialize()
{
	ResourceMgr::Load<JoTexture>(L"BG_Chew1", L"Resources/Map/Chew/Chew1.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew2", L"Resources/Map/Chew/Chew2.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew3", L"Resources/Map/Chew/Chew3.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew4", L"Resources/Map/Chew/Chew4.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew5", L"Resources/Map/Chew/Chew5.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew6", L"Resources/Map/Chew/Chew6.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew7", L"Resources/Map/Chew/Chew7.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew8", L"Resources/Map/Chew/Chew8.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew9", L"Resources/Map/Chew/Chew9.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew10", L"Resources/Map/Chew/Chew10.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew11", L"Resources/Map/Chew/Chew11.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew12", L"Resources/Map/Chew/Chew12.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew13", L"Resources/Map/Chew/Chew13.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew14", L"Resources/Map/Chew/Chew14.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew15", L"Resources/Map/Chew/Chew15.png");
	ResourceMgr::Load<JoTexture>(L"BG_Chew16", L"Resources/Map/Chew/Chew16.png");

	ResourceMgr::Load<JoTexture>(L"BG_GiantRoot1", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot1.png");
	ResourceMgr::Load<JoTexture>(L"BG_GiantRoot2", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot2.png");
	ResourceMgr::Load<JoTexture>(L"BG_GiantRoot3", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot3.png");
	ResourceMgr::Load<JoTexture>(L"BG_GiantRoot4", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot4.png");
	ResourceMgr::Load<JoBmp>(L"GiantRoot_Pixel", L"Resources/Map/Rootabyss/GiantRoot/GiantRoot_Pixel.bmp");

	ResourceMgr::Load<JoTexture>(L"BG_AbyssCave1", L"Resources/Map/AbyssCave/�ɿ��ǵ���1.png");
	ResourceMgr::Load<JoTexture>(L"BG_AbyssCave2", L"Resources/Map/AbyssCave/�ɿ��ǵ���2.png");
	ResourceMgr::Load<JoTexture>(L"BG_AbyssCave3", L"Resources/Map/AbyssCave/�ɿ��ǵ���3.png");
	ResourceMgr::Load<JoTexture>(L"BG_AbyssCave4", L"Resources/Map/AbyssCave/�ɿ��ǵ���4.png");
	ResourceMgr::Load<JoBmp>(L"AbyssCave_Pixel", L"Resources/Map/AbyssCave/AbyssCave_Pixel.bmp");

	ResourceMgr::Load<JoTexture>(L"�ǹ��� �ҳ�", L"Resources/Npc/�ҳ�.png");
	ResourceMgr::Load<JoTexture>(L"�ǹ��� �ҳ�_�̸�", L"Resources/UI/Dialog/DialogName_Girl.png");
	ResourceMgr::Load<JoTexture>(L"�ǹ��� �ҳ�_��ȭ", L"Resources/UI/Dialog/Dialog_Girl.png");
	ResourceMgr::Load<JoTexture>(L"����", L"Resources/Npc/����.png");

	ResourceMgr::Load<JoTexture>(L"PhantomBlow", L"Resources/Skill/PhantomBlow/phantomblow.png");
	ResourceMgr::Load<JoTexture>(L"PB_Hit", L"Resources/Skill/PhantomBlow/phantomblow_hit.png");
	ResourceMgr::Load<JoTexture>(L"FlashJump", L"Resources/Skill/FlashJump/FlashJump.png");

	ResourceMgr::Load<JoTexture>(L"Cursor", L"Resources/UI/Cursor.png");
	ResourceMgr::Load<JoTexture>(L"ShopUI", L"Resources/UI/Shop/ShopUI.png");
	ResourceMgr::Load<JoTexture>(L"�÷��̾�_����", L"Resources/UI/Shop/Shop_Selected.png");
	ResourceMgr::Load<JoTexture>(L"����_����", L"Resources/UI/Shop/Shop_Selected_����.png");
	ResourceMgr::Load<JoTexture>(L"Shop_Tab", L"Resources/UI/Shop/Shop_Tab.png");
	ResourceMgr::Load<JoTexture>(L"Item_Number", L"Resources/UI/Item_Num.png");
	ResourceMgr::Load<JoTexture>(L"TitleScreen", L"Resources/TitleScreen.png");
	ResourceMgr::Load<JoTexture>(L"Title_Button", L"Resources/Title_Button.png");
	ResourceMgr::Load<JoTexture>(L"Title_Button_On", L"Resources/Title_Button_On.png");
	ResourceMgr::Load<JoTexture>(L"Portal", L"Resources/Map/Portal/Portal.png");

	ResourceMgr::Load<JoTexture>(L"Damage_Num", L"Resources/UI/DamageNum/damage_num.png");
	ResourceMgr::Load<JoTexture>(L"Damage_Num_Critical", L"Resources/UI/DamageNum/damage_num_critical.png");

	ResourceMgr::Load<JoTexture>(L"Player", L"Resources/Player/Player.png");

	ResourceMgr::Load<JoTexture>(L"Vellum_Idle_L", L"Resources/Enemy/Vellum/Vellum_Idle_L.png");
	ResourceMgr::Load<JoTexture>(L"Vellum_Idle_R", L"Resources/Enemy/Vellum/Vellum_Idle_R.png");
}

void ResourceMgr::Release()
{
	for (auto it = m_resources.begin(); it != m_resources.end(); ++it)
	{
		Safe_Delete<JoResource*>(it->second);
	}

	m_resources.clear();
}
