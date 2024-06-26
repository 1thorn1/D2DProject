#include "pch.h"
#include "BitmapScene.h"
#include "D2DRender.h";


bool BitmapScene::SetBitmap(const std::wstring& strFileName)
{
	//HRESULT hr; // 결과를 저장하는 변수임니다

	//// 인터페이스는 다양한 이미지 포맷(JPEG, PNG, BMP 등)의 이미지를 디코딩하여 메모리에 로드할 수 있는 기능을 제공합니다.
	//// 이 객체를 사용하여 이미지 파일을 읽고, 메모리에 비트맵 형식으로 디코딩할 수 있습니다.
	//IWICBitmapDecoder* pDecoder = NULL;

	//// 인터페이스는 WIC에서 지원하는 다양한 이미지 포맷 간의 변환을 담당합니다.
	//// 주로 이미지의 색상 형식이나 비트 깊이 등을 변환할 때 사용됩니다.
	//IWICFormatConverter* pConverter = NULL;

	//hr = D2DRender::GetWICFactory()->CreateDecoderFromFilename(
	//	strFileName.c_str(),             // Image to be decoded
	//	NULL,                            // Do not prefer a particular vendor
	//	GENERIC_READ,                    // Desired read access to the file
	//	WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
	//	&pDecoder                        // Pointer to the decoder
	//);

	//// WIC에서 이미지의 각 프레임을 디코딩하기 위한 객체를 나타냅니다.
	//// 이미지 포맷에 따라 하나의 이미지가 여러 프레임을 가질 수 있습니다 (예: GIF 애니메이션).
	//IWICBitmapFrameDecode* pFrame = NULL;
	//if (SUCCEEDED(hr))
	//{
	//	hr = pDecoder->GetFrame(0, &pFrame); // 이 부분 이중 포인터 설명해주시옵소서
	//}
	//if (SUCCEEDED(hr))
	//{
	//	hr = D2DRender::GetWICFactory()->CreateFormatConverter(&pConverter); // 이 부분 
	//}
	//if (SUCCEEDED(hr))
	//{
	//	hr = pConverter->Initialize(  // 이건 무슨 의미인지 궁금합니다 ㅠㅠ 헉 왜 초기화
	//		pFrame,                          // Input bitmap to convert
	//		GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
	//		WICBitmapDitherTypeNone,         // Specified dither pattern
	//		NULL,                            // Specify a particular palette 
	//		0.f,                             // Alpha threshold
	//		WICBitmapPaletteTypeCustom       // Palette translation type
	//	);
	//}

	//if (SUCCEEDED(hr))
	//{
	//	hr = D2DRender::GetRanderTarget()->CreateBitmapFromWicBitmap(pConverter, NULL, &m_pBitmap);

	//}


	//// 파일을 사용할때마다 다시 만든다.
	//if (pConverter)
	//	pConverter->Release();

	//if (pDecoder)
	//	pDecoder->Release();

	//if (pFrame)
	//	pFrame->Release();

	return false;
}


void BitmapScene::Update()
{
	__super::Update();
}

void BitmapScene::Render()
{
	D2D_SIZE_F size = m_pBitmap->GetSize();
	D2D_MATRIX_3X2_F center = D2D1::Matrix3x2F::Translation(size.width / 2, size.height / 2);
	D2D1InvertMatrix(&center);
	D2DRender::GetRanderTarget()->SetTransform(center * this->m_WorldTransform);
	D2DRender::GetRanderTarget()->DrawBitmap(this->m_pBitmap);
	D2DRender::GetRanderTarget()->SetTransform(D2D1::Matrix3x2F::Identity()); // 변환 초기화
}