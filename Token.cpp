#include "Token.h"

Token::Token()
{
	SetName(L"�÷��� ��ǥ");
}

Token::~Token()
{
}

void Token::Initialize()
{
	m_pItemTex = ResourceMgr::Load<JoTexture>(L"Token", L"Resources/Item/�÷��� ��ǥ.png");
}
