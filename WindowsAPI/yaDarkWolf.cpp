#include "yaDarkWolf.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaMissile.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaPlayer.h"
#include "yaDamageSkin.h"
#include "yaDarkWolfAttack.h"
#include "yaDarkWolfTeleport.h"

namespace ya
{
	DarkWolf::DarkWolf()
		: mTime(0.0f)
		, mDir(1.0f)
		, mMoveLeft(false)
		, mHp(8000)
		, distance(0.0f)
	{
		SetName(L"DarkWolf");
		SetPos({ 1900.0f, 820.0f });
		SetScale({ 1.0f, 1.0f });

		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\WolfDie"
			, L"WolfDie", Vector2({ -300.0f, -120.0f }), 0.2f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\WolfRegen"
			, L"WolfRegen", Vector2({ -300.0f, -120.0f }), 0.2f);


		//¿ÞÂÊ
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\WolfStand"
			, L"WolfIdle", Vector2({ -300.0f, -120.0f }));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\WolfMove"
			, L"WolfMoveLeft", Vector2({ -300.0f, -120.0f }), 0.3f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\WolfAttack"
			, L"WolfAttack", Vector2({ -300.0f, -120.0f }), 0.2f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\WolfHit"
			, L"WolfHit", Vector2({ -300.0f, -120.0f }));


		//¿À¸¥ÂÊ
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\RWolfStand"
			, L"RWolfIdle", Vector2({ 0.0f, -120.0f }));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\RWolfMove"
			, L"WolfMoveRight", Vector2({ 0.0f, -120.0f }), 0.3f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\RWolfHit"
			, L"RWolfHit", Vector2({ 0.0f, -120.0f }));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\RWolfAttack"
			, L"RWolfAttack", Vector2({ 0.0f, -120.0f }), 0.2f);

		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\WolfSkill1"
			, L"WolfSkill1", Vector2({ -150.0f, -50.0f }), 0.2f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\WolfSkill2"
			, L"WolfSkill2", Vector2({ -150.0f, -50.0f }), 0.2f);


		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\SmashHit"
			, L"SmashHit", Vector2({ -50.0f, 0.0f }));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\BeyonderHit1"
			, L"BeyonderHit1", Vector2({ -50.0f, 0.0f }));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\BeyonderHit2"
			, L"BeyonderHit2", Vector2({ -50.0f, 0.0f }));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\BeyonderHit3"
			, L"BeyonderHit3", Vector2({ -50.0f, 0.0f }));

		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\zero"
			, L"a", Vector2({ 0.0f, 0.0f }));

		mAnimator->Play(L"WolfRegen", false);
		//mAnimator->FindEvents(L"MushMoveLeft")->mStartEvent = std::bind(&MushMom::WarkAnimator, this);
		//mAnimator->GetCompleteEvent(L"WolfSkill1") = std::bind(&DarkWolf::abc, this);

		AddComponent(mAnimator);

		Collider* coliider = new Collider();
		AddComponent(coliider);
		coliider->SetOffset(Vector2(-150.0f, 0.0f));
		coliider->SetScale(Vector2(250.0f, 150.0f));

		wolfTeleport = new DarkWolfTeleport();
		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(wolfTeleport, eColliderLayer::Teleport);
		wolfTeleport->mDarkWolf = this;
		
	}

	DarkWolf::~DarkWolf()
	{

	}

	void DarkWolf::Tick()
	{
		GameObject::Tick();
		
		switch (mState)
		{
		case ya::DarkWolf::State::REGEN:
			Regen();
			break;
		case ya::DarkWolf::State::IDLE:
			Idle();
			break;
		case ya::DarkWolf::State::MOVE:
			Move();
			break;
		case ya::DarkWolf::State::ATTACK:
			Attack();
			break;
		case ya::DarkWolf::State::TELEPORT:
			TeleportAttack();
			break;
		case ya::DarkWolf::State::HIT:
			Hit();
			break;
		case ya::DarkWolf::State::DEATH:
			Death();
			break;
		default:
			break;
		}

		wolfTeleport->SetPos(this->GetPos());
	}
	void DarkWolf::Regen()
	{
		

		mTime += Time::DeltaTime();
		if (mTime > 3.5f)
		{
			mState = State::IDLE;
			mAnimator->Play(L"WolfIdle", true);
			mTime = 0.0f;
		}

	}
	void DarkWolf::Idle()
	{
		mTime += Time::DeltaTime();
		if (mTime > 5.0f)
		{
			mState = State::MOVE;
			mAnimator->Play(L"WolfMoveLeft", true);
			mTime = 0.0f;
		}
	}
	void DarkWolf::Move()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.0f && mMoveLeft)
		{
			mDir *= -1.0f;
			mTime = 0.0f;
			mAnimator->Play(L"WolfMoveLeft", true);
			mMoveLeft = false;
		}

		if (mTime > 3.0f)
		{
			mDir *= -1.0f;
			mTime = 0.0f;
			mAnimator->Play(L"WolfMoveRight", true);
			mMoveLeft = true;
		}

		Vector2 pos = GetPos();
		pos.x -= (mDir * 50.0f) * Time::DeltaTime();
		SetPos(pos);
	}
	void DarkWolf::Attack()
	{
		mTime += Time::DeltaTime();
		mPlayer->SetHitDamage(257);
		if (mTime > 2.0f)
		{
			mPlayer->Hit();
			if (!mMoveLeft)
			{
				mAnimator->Play(L"WolfMoveLeft", true);
				mState = State::MOVE;
			}
			else
			{
				mAnimator->Play(L"WolfMoveRight", true);
				mState = State::MOVE;
			}
			mTime = 0.0f;
		}

	}
	void DarkWolf::TeleportAttack()
	{
		mTime += Time::DeltaTime();
		if (mHp <= 0)
		{
			mAnimator->Play(L"WolfDie", false);
			mState = State::DEATH;
		}
		else if (mHp > 0)
		{	
			if (mTime > 1.5f)
			{	
				mAnimator->Play(L"RWolfAttack", false);
				//DarkWolfAttack* wolfAttack = new DarkWolfAttack();
				//Scene* playScene = SceneManager::GetPlayScene();
				//playScene->AddGameObject(wolfAttack, eColliderLayer::Monster_Projecttile);
				//Vector2 wolfPos = GetPos();
				//wolfAttack->SetPos(Vector2(wolfPos.x + 100.0f, wolfPos.y - 50.0f));
				
				mState = State::ATTACK;
				mTime = 0.0f;
			}
		}

	}
	void DarkWolf::Hit()
	{
		mTime += Time::DeltaTime();
		if (mHp <= 0)
		{
			mAnimator->Play(L"WolfDie", false);
			mState = State::DEATH;
		}
		else if (mHp > 0)
		{
			if (mTime > 1.5f)
			{
				if (mPlayer->GetLook() == true)
				{
					mAnimator->Play(L"WolfAttack", false);
					//DarkWolfAttack* wolfAttack = new DarkWolfAttack();
					//Scene* playScene = SceneManager::GetPlayScene();
					//playScene->AddGameObject(wolfAttack, eColliderLayer::Monster_Projecttile);
					//Vector2 wolfPos = GetPos();
					//wolfAttack->SetPos(Vector2(wolfPos.x - 400.0f , wolfPos.y - 50.0f));
				}
				else
				{
					mAnimator->Play(L"RWolfAttack", false);
					//DarkWolfAttack* wolfAttack = new DarkWolfAttack();
					//Scene* playScene = SceneManager::GetPlayScene();
					//playScene->AddGameObject(wolfAttack, eColliderLayer::Monster_Projecttile);
					//Vector2 wolfPos = GetPos();
					//wolfAttack->SetPos(Vector2(wolfPos.x + 100.0f , wolfPos.y - 50.0f));
				}
				
				mState = State::ATTACK;
				mTime = 0.0f;
			}
		}

	}
	void DarkWolf::Death()
	{
		mTime += Time::DeltaTime();
		wolfTeleport->Death();
		if (mTime > 3.0f)
		{
			GameObject* gameObj = this;
			gameObj->Death();
			mTime = 0.0f;
			SceneManager::ChangeScene(eSceneType::End);
		}
		
	}
	void DarkWolf::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}
	void DarkWolf::OnCollisionEnter(Collider* other)
	{
		GameObject* gameObj = other->GetOwner();
		Vector2 pos = GetPos();
		if (gameObj->GetName() == L"Smash")
		{
			if (mHp > 0)
			{
				if (mPlayer->GetLook() == true)
				{
					mAnimator->Plays(L"WolfHit", L"SmashHit", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else 
				{
					mAnimator->Plays(L"RWolfHit", L"SmashHit", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"WolfDie", false);
				mState = State::DEATH;
				mTime = 0.0f;
			}
				
		}
		if (gameObj->GetName() == L"Beyonder")
		{
			if (mHp > 0)
			{
				//mHp -= 10;
				if (mPlayer->GetLook() == true)
				{
					mAnimator->Plays(L"WolfHit", L"BeyonderHit1", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					mAnimator->Plays(L"RWolfHit", L"BeyonderHit1", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"WolfDie", false);
				mState = State::DEATH;
				mTime = 0.0f;
			}
		}
		if (gameObj->GetName() == L"Beyonder2")
		{
			if (mHp > 0)
			{

				if (mPlayer->GetLook() == true)
				{
					mAnimator->Plays(L"WolfHit", L"BeyonderHit2", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					mAnimator->Plays(L"RWolfHit", L"BeyonderHit2", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"WolfDie", false);
				mState = State::DEATH;
				mTime = 0.0f;
			}
		}
		if (gameObj->GetName() == L"Beyonder3")
		{
			if (mHp > 0)
			{

				if (mPlayer->GetLook() == true)
				{
					mAnimator->Plays(L"WolfHit", L"BeyonderHit3", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					mAnimator->Plays(L"RWolfHit", L"BeyonderHit3", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"WolfDie", false);
				mState = State::DEATH;
				mTime = 0.0f;
			}
		}

	}
	void DarkWolf::OnCollisionStay(Collider* other)
	{
	}
	void DarkWolf::OnCollisionExit(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"Smash")
		{
			Vector2 pos = GetPos();
			DamageSkin* damage = new DamageSkin();
			Scene* playScene = SceneManager::GetPlayScene();
			damage->mDarkWolf = this;
			damage->SetTargetName(L"DarkWolf");
			damage->SetPos({ pos.x , pos.y - 150.0f });
			damage->SetAttackNumber(3);
			playScene->AddGameObject(damage, eColliderLayer::Damage);
		}
		if (other->GetOwner()->GetName() == L"Beyonder"
			|| other->GetOwner()->GetName() == L"Beyonder2"
			|| other->GetOwner()->GetName() == L"Beyonder3")
		{
			Vector2 pos = GetPos();
			DamageSkin* damage = new DamageSkin();
			Scene* playScene = SceneManager::GetPlayScene();
			damage->mDarkWolf = this;
			damage->SetTargetName(L"DarkWolf");
			damage->SetPos({ pos.x , pos.y - 150.0f });
			damage->SetAttackNumber(5);
			playScene->AddGameObject(damage, eColliderLayer::Damage);
		}

	}
	int DarkWolf::AttackDamage()
	{
		int finalDamage = mPlayer->GetAttackDamage();
		mHp -= finalDamage;
		return finalDamage;
	}
}
