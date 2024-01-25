#include "Collider.h"
#include "GameObject.h"
#include "RenderMgr.h"
#include "Camera.h"


UINT32 Collider::s_CollisionID = 0;

Collider::Collider()
	: m_iID(s_CollisionID++)
	, m_vSize{}
	, m_renderColor(RGB(0, 255, 0))
	, m_bActiveColl(true)
	, m_pOwner(nullptr)
{
	SetName(L"Collider");
}

Collider::~Collider()
{
}

void Collider::Initialize()
{
}

void Collider::Update()
{
}

void Collider::LateUpdate()
{
}
void Collider::Render()
{
	if (!m_bActiveColl)
		return;
	Vec2 pos = GetOwner()->GetPos();
	pos += GetOffset();
	pos = Camera::CalcRenderPos(pos);

	Vec2 vLeftTop = {};
	vLeftTop.x = pos.x - GetSize().x * 0.5f;
	vLeftTop.y = pos.y - GetSize().y * 0.5f;

	Vec2 vRightBottom = {};
	vRightBottom.x = pos.x + GetSize().x * 0.5f;
	vRightBottom.y = pos.y + GetSize().y * 0.5f;

	RenderMgr::RenderRectangle(
		  vLeftTop.x
		, vLeftTop.y
		, vRightBottom.x
		, vRightBottom.y
		, m_renderColor, 1.0f);
}

void Collider::OnCollisionEnter(Collider* other)
{
	if (!m_bActiveColl)
		return;
	m_renderColor = RGB(255, 0, 0);
	GetOwner()->OnCollisionEnter(other);
}

void Collider::OnCollisionStay(Collider* other)
{
	if (!m_bActiveColl)
		return;
	GetOwner()->OnCollisionStay(other);
}

void Collider::OnCollisionExit(Collider* other)
{
	if (!m_bActiveColl)
		return;
	m_renderColor = RGB(0, 255, 0);
	GetOwner()->OnCollisionExit(other);
}
