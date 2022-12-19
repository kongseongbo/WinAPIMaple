#include "yaMushMom.h"
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
#include "yaLogoScene.h"

namespace ya
{
	MushMom::MushMom()
		: mTime(0.0f)
		, mDir(1.0f)
		, mMoveLeft(false)
		, mHp(10000)
		, distance(0.0f)
	{
		SetName(L"MushMom");
		SetPos({ 900.0f, 820.0f });
		SetScale({ 1.0f, 1.0f });

		/*if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"MushMom", L"..\\Resources\\Animations\\Mushmom\\MushIdle\\stand.bmp");
		}*/

		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\MushDie"
			, L"MushDie", Vector2({ 0.0f, -30.0f }), 0.1f);

		//¿ÞÂÊ
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\MushIdle"
			, L"MushIdle", Vector2({0.0f, -40.0f}));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\MushMoveLeft"
			, L"MushMoveLeft", Vector2({ 0.0f, -40.0f }), 0.3f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\MushSkill"
			, L"MushAttack", Vector2({ 0.0f, -50.0f }), 0.2f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\MushHit"
			, L"MushHit", Vector2({ 0.0f, -30.0f }));
		
		
		//¿À¸¥ÂÊ
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\MushMoveRight"
			, L"MushMoveRight", Vector2({ 0.0f, -40.0f }), 0.3f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\RMushHit"
			, L"RMushHit", Vector2({ 0.0f, -30.0f }));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\RMushSkill"
			, L"RMushAttack", Vector2({ 0.0f, -50.0f }), 0.2f);


		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\SmashHit"
			, L"SmashHit");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\BeyonderHit1"
			, L"BeyonderHit1");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\BeyonderHit2"
			, L"BeyonderHit2");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\BeyonderHit3"
			, L"BeyonderHit3");

		mAnimator->Play(L"MushIdle", true);
		//mAnimator->FindEvents(L"MushMoveLeft")->mStartEvent = std::bind(&MushMom::WarkAnimator, this);
		//mAnimator->GetStartEvent(L"MushMoveLeft") = std::bind(&MushMom::WarkAnimator, this);

		AddComponent(mAnimator);
		AddComponent(new Collider());

	}

	MushMom::~MushMom()
	{

	}

	void MushMom::Tick()
	{
		GameObject::Tick();

		switch (mState)
		{
		case ya::MushMom::State::IDLE:
			Idle();
			break;
		case ya::MushMom::State::MOVE:
			Move();
			break;
		case ya::MushMom::State::ATTACK:
			Attack();
			break;
		case ya::MushMom::State::HIT:
			Hit();
			break;
		case ya::MushMom::State::DEATH:
			Death();
			break;
		default:
			break;
		}
		
	}
	void MushMom::Idle()
	{
		mTime += Time::DeltaTime();
		if (mTime > 5.0f)
		{
			mState = State::MOVE;
			mAnimator->Play(L"MushMoveLeft", true);
			mTime = 0.0f;
		}
	}
	void MushMom::Move()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.0f && mMoveLeft)
		{
			mDir *= -1.0f;
			mTime = 0.0f;
			mAnimator->Play(L"MushMoveLeft", true);
			mMoveLeft = false;
		}
	
		if (mTime > 3.0f)
		{
			mDir *= -1.0f;
			mTime = 0.0f;
			mAnimator->Play(L"MushMoveRight", true);
			mMoveLeft = true;
		}
		
		Vector2 pos = GetPos();
		pos.x -= (mDir * 50.0f) * Time::DeltaTime();
		SetPos(pos);
	}
	void MushMom::Attack()
	{
		mTime += Time::DeltaTime();
		mPlayer->SetHitDamage(100);
		
		if (mTime > 2.0f)
		{
			mPlayer->Hit();
			if (!mMoveLeft)
			{
				mAnimator->Play(L"MushMoveLeft", true);
				mState = State::MOVE;
			}
			else
			{
				mAnimator->Play(L"MushMoveRight", true);
				mState = State::MOVE;
			}
			mTime = 0.0f;
		}
		
	}
	void MushMom::Hit()
	{
		mTime += Time::DeltaTime();
		if (mHp <= 0)
		{
			mAnimator->Play(L"MushDie", false);
			mState = State::DEATH;
		}
		else if (mHp > 0)
		{
			if (mTime > 1.5f)
			{
				if (mPlayer->GetLook() == true)
				{
					mAnimator->Play(L"MushAttack", false);
				}
				else
				{
					mAnimator->Play(L"RMushAttack", false);
				}
				mState = State::ATTACK;
				mTime = 0.0f;
			}
		}
		
	}
	void MushMom::Death()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.0f)
		{
			GameObject* gameObj = this;
			gameObj->Death();
		}
		mPlayer->SetEx(50);
	}
	void MushMom::Render(HDC hdc)
	{
		
		GameObject::Render(hdc);
	}
	void MushMom::OnCollisionEnter(Collider* other)
	{
		GameObject* gameObj = other->GetOwner();
		Vector2 pos = GetPos();
		if (gameObj->GetName() == L"Smash")
		{
			if (mHp > 0)
			{
				if (mPlayer->GetLook() == true)
				{
					pos.x += 20.0f;
					SetPos(pos);
					//mAnimator->Play(L"MushHit", false);
					mAnimator->Plays(L"MushHit",L"SmashHit",false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					pos.x -= 20.0f;
					SetPos(pos);
					//mAnimator->Play(L"RMushHit", false);
					mAnimator->Plays(L"RMushHit", L"SmashHit", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"MushDie", false);
				mState = State::DEATH;
			}
		}
		if (gameObj->GetName() == L"Beyonder")
		{
			if (mHp > 0)
			{
				//mHp -= 10;
				if (mPlayer->GetLook() == true)
				{
					pos.x += 20.0f;
					SetPos(pos);
					//mAnimator->Play(L"MushHit", false);
					mAnimator->Plays(L"MushHit", L"BeyonderHit1", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					pos.x -= 20.0f;
					SetPos(pos);
					//mAnimator->Play(L"RMushHit", false);
					mAnimator->Plays(L"RMushHit", L"BeyonderHit1", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"MushDie", false);
				mState = State::DEATH;
			}
		}
		if (gameObj->GetName() == L"Beyonder2")
		{
			if (mHp > 0)
			{
				
				if (mPlayer->GetLook() == true)
				{
					pos.x += 20.0f;
					SetPos(pos);
					//mAnimator->Play(L"MushHit", false);
					mAnimator->Plays(L"MushHit", L"BeyonderHit2", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					pos.x -= 20.0f;
					SetPos(pos);
					//mAnimator->Play(L"RMushHit", false);
					mAnimator->Plays(L"RMushHit", L"BeyonderHit2", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"MushDie", false);
				mState = State::DEATH;
			}
		}
		if (gameObj->GetName() == L"Beyonder3")
		{
			if (mHp > 0)
			{
				
				if (mPlayer->GetLook() == true)
				{
					pos.x += 20.0f;
					SetPos(pos);
					//mAnimator->Play(L"MushHit", false);
					mAnimator->Plays(L"MushHit", L"BeyonderHit3", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					pos.x -= 20.0f;
					SetPos(pos);
					//mAnimator->Play(L"RMushHit", false);
					mAnimator->Plays(L"RMushHit", L"BeyonderHit3", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"MushDie", false);
				mState = State::DEATH;
			}
		}
	}
	void MushMom::OnCollisionStay(Collider* other)
	{
	}
	void MushMom::OnCollisionExit(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"Smash")
		{
			Vector2 pos = GetPos();
			DamageSkin* damage = new DamageSkin();
			Scene* playScene = SceneManager::GetPlayScene();
			damage->mMushmom = this;
			damage->SetTargetName(L"Mushmom");
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
			damage->mMushmom = this;
			damage->SetTargetName(L"Mushmom");
			damage->SetPos({ pos.x , pos.y - 150.0f });
			damage->SetAttackNumber(5);
			playScene->AddGameObject(damage, eColliderLayer::Damage);
		}
		
	}
	int MushMom::AttackDamage()
	{
		int finalDamage = mPlayer->GetAttackDamage();
		mHp -= finalDamage;

		return finalDamage;
	}
}
