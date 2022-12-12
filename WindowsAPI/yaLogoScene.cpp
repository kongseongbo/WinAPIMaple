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

namespace ya
{
	LogoScene::LogoScene()
	{
	}

	LogoScene::~LogoScene()
	{
	}

	void LogoScene::Initialize()
	{
		/*BgImageObject* bgImage = ya::object::Instantiate<BgImageObject>(eColliderLayer::BackGround);
		bgImage->SetImage(L"Map", L"Map\\HenesysGolemSawonBG.bmp");*/
		
		BgImageObject* bg = ya::object::Instantiate<BgImageObject>(eColliderLayer::PixelBackGround);
		bg->SetPixelImage(L"PIXEL", L"Map\\Pixel.bmp");
		bg->SetImage(L"Map", L"Map\\HenesysGolemSawon3.bmp");
		BgImageObject* bg2 = ya::object::Instantiate<BgImageObject>(eColliderLayer::BackGround);
		bg2->SetImage(L"BGMap",L"Map\\HenesysGolemSawonBG2.bmp");
		
		Player* player = ya::object::Instantiate<Player>(eColliderLayer::Player);
		bg->mPlayer = player;
		MushMom* mMushmom = ya::object::Instantiate<MushMom>(eColliderLayer::Monster);
		MushMom* mMushmom1 = ya::object::Instantiate<MushMom>(eColliderLayer::Monster);
		MushMom* mMushmom2 = ya::object::Instantiate<MushMom>(eColliderLayer::Monster);
		MushMom* mMushmom3 = ya::object::Instantiate<MushMom>(eColliderLayer::Monster);
		MushMom* mMushmom4 = ya::object::Instantiate<MushMom>(eColliderLayer::Monster);
		DarkWolf* mDarkWolf = ya::object::Instantiate<DarkWolf>(eColliderLayer::Monster);
		mMushmom->mPlayer = player;
		mMushmom1->mPlayer = player;
		mMushmom2->mPlayer = player;
		mMushmom3->mPlayer = player;
		mMushmom4->mPlayer = player;
		mDarkWolf->mPlayer = player;
		
		Vector2 pos = mMushmom1->GetPos();
		pos.x += 120.0f;
		mMushmom1->SetPos(pos);
		Vector2 pos2 = mMushmom1->GetPos();
		pos2.x += 800.0f;
		pos2.y -= 290.0f;
		mMushmom2->SetPos(pos2);
		Vector2 pos3 = mMushmom1->GetPos();
		pos3.x += 100.0f;
		pos3.y -= 290.0f;
		mMushmom3->SetPos(pos3);
		Vector2 pos4 = mMushmom1->GetPos();
		pos4.x += 1500.0f;
		mMushmom4->SetPos(pos4);

		
		
		//Ground* ground = ya::object::Instantiate<Ground>(eColliderLayer::Ground);
		//ground->SetPos(Vector2(700.0f, 700.0f));

		//UIManager::Push(eUIType::HP);
		//UIManager::Push(eUIType::MP);
		//UIManager::Push(eUIType::INVENTORY);

		//HUD* hud = UIManager::GetUiInstant<HUD>(eUIType::HP);
		//HUD* hud = UIManager::GetUiInstant<HUD>(eUIType::MP);
		//hud->SetTarget(player);

		//ya::Scene* scene = ya::SceneManager::GetScene(eSceneType::Tool);
		//ya::ToolScene* toolScene = dynamic_cast<ya::ToolScene*>(scene);
		//toolScene->LoadTilePalette(L"..\\Resources\\TileSaveFiles\\Test");

	}

	void LogoScene::Tick()
	{
		// 오브젝트 tick 을 호출한다.
		Scene::Tick();
		
		//ya::object::Destroy(mons[0], 3.0f);
	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//
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
	}

	void LogoScene::Exit()
	{
	}
}