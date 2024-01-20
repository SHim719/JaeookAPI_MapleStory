#include "JoTexture.h"
#include "MainGame.h"
#include "RenderMgr.h"

JoTexture::JoTexture()
	: JoResource(eResourceType::Texture)
	, m_height(0)
	, m_width(0)
	, m_pBitmap(nullptr)
{
}

JoTexture::~JoTexture()
{
	m_pBitmap->Release();
}

HRESULT JoTexture::Load(const wstring& path)
{
	IWICBitmapDecoder* p_decoder;		// ����� �̹����� ������ ��ü
	IWICBitmapFrameDecode* p_frame;		// Ư�� �׸��� ������ ��ü
	IWICFormatConverter* p_converter;	// �̹��� ��ȯ ��ü

	// WIC�� Factory ��ü�� ����Ͽ� �̹��� ���� ������ ���� ��ü�� ����
	if (S_OK != RenderMgr::GetImageFactory()->CreateDecoderFromFilename(path.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder))
	{
		assert(nullptr);
	}
	// ������ �����ϴ� �̹��� �߿��� ù��° �̹����� �����Ѵ�.
	if (S_OK != p_decoder->GetFrame(0, &p_frame))
	{
		assert(nullptr);
	}
	// IWICBitmap������ ��Ʈ���� ID2D1Bitmap. �������� ��ȯ�ϱ� ���� ��ü ����
	if (S_OK != RenderMgr::GetImageFactory()->CreateFormatConverter(&p_converter))
	{
		assert(nullptr);
	}
	// ���õ� �׸��� � ������ ��Ʈ������ ��ȯ�� ������ ����
	if (S_OK != p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom))
	{
		assert(nullptr);
	}
	// IWICBitmap ������ ��Ʈ������ ID2D1Bitmap ��ü�� ����
	ID2D1Bitmap* bitmap = RenderMgr::GetBitmap();
	if (S_OK != RenderMgr::GetRenderTarget()->CreateBitmapFromWicBitmap(p_converter, NULL, &bitmap))
	{
		assert(nullptr);
	}

	// ���������� ������ ���
	m_pBitmap = bitmap;

	m_width = UINT(m_pBitmap->GetSize().width);
	m_height = UINT(m_pBitmap->GetSize().height);

	p_converter->Release();		// �̹��� ��ȯ ��ü ����
	p_frame->Release();			// �׸����Ͽ� �ִ� �̹����� �����ϱ� ���� ����� ��ü ����
	p_decoder->Release();		// ������ �����ϱ� ���� ������ ��ü ����

	return S_OK;
}

