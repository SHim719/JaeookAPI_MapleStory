#include "JoBmp.h"
#include "MainGame.h"

extern MainGame g_MainGame;

JoBmp::JoBmp()
	: JoResource(eResourceType::Texture)
	, m_height(0)
	, m_width(0)
	, m_BmpDC(nullptr)
	, m_hBitmap(nullptr)
{
}

JoBmp::~JoBmp()
{
}

HRESULT JoBmp::Load(const wstring& path)
{
	HDC	hDC = g_MainGame.GetMainDC();

	// CreateCompatibleDC : ���� ȭ�� dc�� ȣȯ�Ǵ� dc�� ����

	m_BmpDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_MainGame.GetHwnd(), hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,			// ���α׷� �ν��Ͻ� �ڵ�(�츮�� ���Ϸκ��� �о���� ������ NULL���� ����)
		path.c_str(),		// ������ ���
		IMAGE_BITMAP,	// � Ÿ���� �о���� ����(��Ʈ�� , Ŀ��, ������ ���)
		0,				// ����, ���� ������
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : ���Ϸκ��� �̹����� �ҷ������� LR_CREATEDIBSECTION : �о�� ������ DIB ���·� ��ȯ

	// SelectObject : gdi ������Ʈ�� �����ϱ� ���� ������ ������ �ִ� ������Ʈ�� ��ȯ
	auto oldBitmap = (HBITMAP)SelectObject(m_BmpDC, m_hBitmap);

	DeleteObject(oldBitmap);
	return S_OK;
}
