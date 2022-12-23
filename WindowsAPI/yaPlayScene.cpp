#include "yaPlayScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaCamera.h"
#include "yaDarkWolf.h"
#include "yaDarkWolfAttack.h"
#include "yaObject.h"
#include "yaBgImageObject.h"
#include "yaCollisionManager.h"
#include "yaMissile.h"
#include "yaTime.h"
#include "yaUIManager.h"
#include "yaHUD.h"

namespace ya
{
	PlayScene::PlayScene()
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		bg = ya::object::Instantiate<BgImageObject>(eColliderLayer::PixelBackGround);
		bg->SetPixelImage(L"BossPIXEL", L"Map\\BossMapPixel2.bmp");
		bg->SetImage(L"BossMap", L"Map\\BossMap2.bmp");

		BgImageObject* bg2 = ya::object::Instantiate<BgImageObject>(eColliderLayer::BackGround);
		bg2->SetImage(L"BossMapBG", L"Map\\BossMapBG2.bmp");

		player = ya::object::Instantiate<Player>(eColliderLayer::Player);
		player->SetPos(Vector2{ 140.0f,660.0f });
		bg->mPlayer = player;
		
		DarkWolf* mDarkWolf = ya::object::Instantiate<DarkWolf>(eColliderLayer::Monster);
		mDarkWolf->SetPos(Vector2{ 1500.0f,700.0f });
		mDarkWolf->mPlayer = player;

		UIManager::Push(eUIType::MONSTERHP);
		UIManager::Push(eUIType::HPMPBAR);

		HUD* hud = UIManager::GetUiInstant<HUD>(eUIType::HPMPBAR);
		HUD* BossHp = UIManager::GetUiInstant<HUD>(eUIType::MONSTERHP);
		BossHp->SetTarget(mDarkWolf);

		//Missile* mMissile = ya::object::Instantiate<Missile>(eColliderLayer::Monster_Projecttile);
		//mMissile->SetPos(Vector2{ 500.0f,700.0f });
	}

	void PlayScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::End);
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Play Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}

	void PlayScene::Enter()
	{
		Camera::SetTarget(bg);

		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Teleport, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Smash, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Beyonder, true);
		CollisionManager::SetLayer(eColliderLayer::Ground, eColliderLayer::Player, true);

		Camera::SetAlphaTime(0.0f);
		Camera::SetCameraEffect(eCameraEffect::FadeIn);
		
	}

	void PlayScene::Exit()
	{

	}
}
