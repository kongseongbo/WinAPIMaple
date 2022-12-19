#include "yaLogoScene.h"
#include "yaPlayer.h"
#include "yaMushMom.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaCollisionManager.h"
#include "yaObject.h"
#include "yaApplication.h"
#include "yaToolScene.h"
#include "yaGround.h"
#include "yaUIManager.h"
#include "yaHUD.h"
#include "yaButton.h"
#include "yaDarkWolf.h"
#include "yaTime.h"
#include "yaGolem.h"
#include "yaCamera.h"

namespace ya
{
	int LogoScene::mNextSceneStack = 0;

	LogoScene::LogoScene()
		: mTime(0.0f)
	{
	}

	LogoScene::~LogoScene()
	{
	}

	void LogoScene::Initialize()
	{	
		BgImageObject* bg = ya::object::Instantiate<BgImageObject>(eColliderLayer::PixelBackGround);
		bg->SetPixelImage(L"PIXEL", L"Map\\Pixel.bmp");
		bg->SetImage(L"Map", L"Map\\HenesysGolemSawon3.bmp");

		BgImageObject* bg2 = ya::object::Instantiate<BgImageObject>(eColliderLayer::BackGround);
		bg2->SetImage(L"BGMap",L"Map\\HenesysGolemSawonBG3.bmp");
		bg2->SetPos(Vector2{ -700.0f,-600.0f });
		
		player = ya::object::Instantiate<Player>(eColliderLayer::Player);
		bg->mPlayer = player;

		//Golem
		for (size_t i = 0; i < 3; i++)
		{
			mGolem[i] = ya::object::Instantiate<Golem>(eColliderLayer::Monster);
			mGolem[i]->mPlayer = player;
			golemPos[i] = { mGolem[i]->GetPos() };
		}
	
		golemPos[0].x += 2500.0f;
		mGolem[0]->SetPos(golemPos[0]);

		golemPos[1].x += 2600.0f;
		golemPos[1].y -= 290.0f;
		mGolem[1]->SetPos(golemPos[1]);

		golemPos[2].x += 2650.0f;
		mGolem[2]->SetPos(golemPos[2]);

		//MushMom
		for (size_t i = 0; i < 5; i++)
		{
			mMushmom[i] = ya::object::Instantiate<MushMom>(eColliderLayer::Monster);
			mMushmom[i]->mPlayer = player;
			mushPos[i] = { mMushmom[i]->GetPos()};
		}

		mushPos[1].x += 120.0f;
		mMushmom[1]->SetPos(mushPos[1]);

		mushPos[2].x += 800.0f;
		mushPos[2].y -= 290.0f;
		mMushmom[2]->SetPos(mushPos[2]);
		
		mushPos[3].x += 100.0f;
		mushPos[3].y -= 290.0f;
		mMushmom[3]->SetPos(mushPos[3]);
		
		mushPos[4].x += 1300.0f;
		mMushmom[4]->SetPos(mushPos[4]);
		
		//Ground* ground = ya::object::Instantiate<Ground>(eColliderLayer::Ground);
		//ground->SetPos(Vector2(700.0f, 700.0f));

		UIManager::Push(eUIType::HP);
		UIManager::Push(eUIType::MP);
		UIManager::Push(eUIType::HPMPBAR);
		//UIManager::Push(eUIType::INVENTORY);

		HUD* Hp = UIManager::GetUiInstant<HUD>(eUIType::HP);
		HUD* Mp = UIManager::GetUiInstant<HUD>(eUIType::MP);
		HUD* hud = UIManager::GetUiInstant<HUD>(eUIType::HPMPBAR);
		Hp->SetTarget(player);
		Mp->SetTarget(player);

		//ya::Scene* scene = ya::SceneManager::GetScene(eSceneType::Tool);
		//ya::ToolScene* toolScene = dynamic_cast<ya::ToolScene*>(scene);
		//toolScene->LoadTilePalette(L"..\\Resources\\TileSaveFiles\\Test");

	}

	void LogoScene::Tick()
	{
		// 오브젝트 tick 을 호출한다.
		Scene::Tick();
		for (size_t i = 0; i < 5; i++)
		{
			if (mMushmom[i]->GetState() == 4)
			{
				mTime += Time::DeltaTime();
				if (mTime > 4.0f)
				{
					mMushmom[i] = ya::object::Instantiate<MushMom>(eColliderLayer::Monster);
					mMushmom[i]->mPlayer = player;
					mMushmom[i]->SetPos(mushPos[i]);
					mNextSceneStack++;
					mTime = 0.0f;
				}
			}

		}
		for (size_t i = 0; i < 3; i++)
		{
			if (mGolem[i]->GetState() == 4)
			{
				mTime += Time::DeltaTime();
				if (mTime > 4.0f)
				{
					mGolem[i] = ya::object::Instantiate<Golem>(eColliderLayer::Monster);
					mGolem[i]->mPlayer = player;
					mGolem[i]->SetPos(golemPos[i]);
					mNextSceneStack++;
					mTime = 0.0f;
				}
			}
		}

		if (mNextSceneStack >= 5)
		{
			SceneManager::ChangeScene(eSceneType::Play);
			
			mNextSceneStack = 0;
		}
		//ya::object::Destroy(mons[0], 3.0f);
	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Logo Scene.bmp");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}

	void LogoScene::Enter()
	{
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Smash, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Beyonder, true);
		CollisionManager::SetLayer(eColliderLayer::Ground, eColliderLayer::Player, true);
		Camera::SetTarget(player);
	}

	void LogoScene::Exit()
	{
		Camera::SetAlphaTime(0.0f);
		Camera::SetCameraEffect(eCameraEffect::FadeOut);
	}
}