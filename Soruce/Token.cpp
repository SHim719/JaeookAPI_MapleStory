#include "Token.h"

Token::Token()
{
	SetName(L"�÷��� ��ǥ");
	m_iMaxCount = 4;
	m_iSellPrice = 999999;
}

Token::~Token()
{
}

void Token::Initialize()
{
	m_pItemTex = ResourceMgr::Load<JoTexture>(L"Token", L"Resources/Item/�÷��� ��ǥ.png");
}
