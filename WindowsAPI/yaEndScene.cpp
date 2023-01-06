#include "yaEndScene.h"
#include "yaBgImageObject.h"
#include "yaObject.h"
#include "yaSound.h"

namespace ya
{
	EndScene::EndScene()
	{
	}
	EndScene::~EndScene()
	{
	}
	void EndScene::Initialize()
	{
		BgImageObject* bg = ya::object::Instantiate<BgImageObject>(eColliderLayer::BackGround);
		bg->SetImage(L"EndScene", L"Map\\End.bmp");
		//bg->SetPos(Vector2(-700.0f, -500.0f));

		
	}
	void EndScene::Tick()
	{
		Scene::Tick();
	}
	void EndScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"End Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
	void EndScene::Enter()
	{
		mSound = new Sound();
		mSound->LoadWavFile(L"..\\Sound\\RestNPeace.wav");
		mSound->Play(true);
	}
	void EndScene::Exit()
	{
		delete mSound;
	}
}
