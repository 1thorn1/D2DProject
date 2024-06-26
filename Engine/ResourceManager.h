#pragma once

class AnimationAsset;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* pInstance; // 

	// std::wstring을 키로, ID2D1Bitmap*값을 저장
	static std::map<std::wstring, ID2D1Bitmap*> m_BitmapMap;
	static std::map<std::wstring, AnimationAsset*> m_AnimationAssetMap;

	// bitmap 파일들의 배열을 만들고 해제합니다. -> 리소스!!
	static bool CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap);
	static void ReleaseD2DBitmap(std::wstring strFilePath);

	// animation asset(정보를 담은 애니메이션들)의 배열을 만들고 해제합니다.
	static bool CreateAnimationAsset(std::wstring strFilePath, AnimationAsset** asset);
	static void ReleaseAnimationAsset(std::wstring strFilePath);
};

