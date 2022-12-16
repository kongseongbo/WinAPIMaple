#include "yaTitleScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaAnimator.h"
#include "yaLogo.h"
#include "yaObject.h"
#include "yaTime.h"

namespace ya
{
	TitleScene::TitleScene()
		: mTime(0.0f)
	{
		
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		Logo* logo = ya::object::Instantiate<Logo>(eColliderLayer::BackGround);
	}       
	void TitleScene::Tick()
	{
		Scene::Tick();
		mTime += Time::DeltaTime();
		if (mTime >13.0f)
		{
			SceneManager::ChangeScene(eSceneType::Logo);
		}
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Title Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
	void TitleScene::Enter()
	{
	}
	void TitleScene::Exit()
	{
	}
}
