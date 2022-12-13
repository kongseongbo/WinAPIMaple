#include "yaGolem.h"
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

namespace ya
{
	Golem::Golem()
		: mTime(0.0f)
		, mDir(1.0f)
		, mMoveLeft(false)
		, mHp(20000)
		, distance(0.0f)
		, defense(900)
	{
		SetName(L"Golem");
		SetPos({ 900.0f, 820.0f });
		SetScale({ 1.0f, 1.0f });

		mAnimator = new Animator();
		

		//¿ÞÂÊ
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Golem\\GolemIdle"
			, L"GolemIdle", Vector2({ 0.0f, -40.0f }), 0.4f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Golem\\GolemMoveLeft"
			, L"GolemMoveLeft", Vector2({ 0.0f, -40.0f }), 0.4f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Golem\\GolemSkill"
			, L"GolemAttack", Vector2({ 0.0f, -40.0f }), 0.2f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Golem\\GolemHit"
			, L"GolemHit", Vector2({ 0.0f, -40.0f }));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Golem\\GolemDie"
			, L"GolemDie", Vector2({ 0.0f, -40.0f }), 0.1f);

		//¿À¸¥ÂÊ
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Golem\\GolemMoveRight"
			, L"GolemMoveRight", Vector2({ 0.0f, -40.0f }), 0.4f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Golem\\RGolemHit"
			, L"RGolemHit", Vector2({ 0.0f, -40.0f }));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Golem\\RGolemSkill"
			, L"RGolemAttack", Vector2({ 0.0f, -40.0f }), 0.2f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Golem\\RGolemDie"
			, L"RGolemDie", Vector2({ 0.0f, -40.0f }), 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\SmashHit"
			, L"SmashHit");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\BeyonderHit1"
			, L"BeyonderHit1");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\BeyonderHit2"
			, L"BeyonderHit2");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\BeyonderHit3"
			, L"BeyonderHit3");

		mAnimator->Play(L"GolemIdle", true);
		//mAnimator->FindEvents(L"MushMoveLeft")->mStartEvent = std::bind(&MushMom::WarkAnimator, this);
		//mAnimator->GetStartEvent(L"MushMoveLeft") = std::bind(&MushMom::WarkAnimator, this);

		AddComponent(mAnimator);
		AddComponent(new Collider());

	}

	Golem::~Golem()
	{

	}

	void Golem::Tick()
	{
		GameObject::Tick();

		switch (mState)
		{
		case ya::Golem::State::IDLE:
			Idle();
			break;
		case ya::Golem::State::MOVE:
			Move();
			break;
		case ya::Golem::State::ATTACK:
			Attack();
			break;
		case ya::Golem::State::HIT:
			Hit();
			break;
		case ya::Golem::State::DEATH:
			Death();
			break;
		default:
			break;
		}

	}
	void Golem::Idle()
	{
		mTime += Time::DeltaTime();
		if (mTime > 5.0f)
		{
			mState = State::MOVE;
			mAnimator->Play(L"GolemMoveLeft", true);
			mTime = 0.0f;
		}
	}
	void Golem::Move()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.0f && mMoveLeft)
		{
			mDir *= -1.0f;
			mTime = 0.0f;
			mAnimator->Play(L"GolemMoveLeft", true);
			mMoveLeft = false;
		}

		if (mTime > 3.0f)
		{
			mDir *= -1.0f;
			mTime = 0.0f;
			mAnimator->Play(L"GolemMoveRight", true);
			mMoveLeft = true;
		}

		Vector2 pos = GetPos();
		pos.x -= (mDir * 50.0f) * Time::DeltaTime();
		SetPos(pos);
	}
	void Golem::Attack()
	{

		mTime += Time::DeltaTime();
		if (mTime > 2.0f)
		{
			if (!mMoveLeft)
			{
				mAnimator->Play(L"GolemMoveLeft", true);
				mState = State::MOVE;
			}
			else
			{
				mAnimator->Play(L"GolemMoveRight", true);
				mState = State::MOVE;
			}
			mTime = 0.0f;
		}

	}
	void Golem::Hit()
	{
		mTime += Time::DeltaTime();
		if (mHp <= 0)
		{
			mAnimator->Play(L"GolemDie", false);
			mState = State::DEATH;
		}
		else if (mHp > 0)
		{
			if (mTime > 1.5f)
			{
				if (mPlayer->GetLook() == true)
				{
					mAnimator->Play(L"GolemAttack", false);
				}
				else
				{
					mAnimator->Play(L"RGolemAttack", false);
				}
				mState = State::ATTACK;
				mTime = 0.0f;
			}
		}

	}
	void Golem::Death()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.0f)
		{
			GameObject* gameObj = this;
			gameObj->Death();
			mTime = 0.0f;
		}
		mPlayer->SetEx(50);
	}
	void Golem::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}
	void Golem::OnCollisionEnter(Collider* other)
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
					mAnimator->Plays(L"GolemHit", L"SmashHit", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					pos.x -= 20.0f;
					SetPos(pos);
					mAnimator->Plays(L"RGolemHit", L"SmashHit", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"GolemDie", false);
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
					mAnimator->Plays(L"GolemHit", L"BeyonderHit1", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					pos.x -= 20.0f;
					SetPos(pos);
					mAnimator->Plays(L"RGolemHit", L"BeyonderHit1", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"GolemDie", false);
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
					mAnimator->Plays(L"GolemHit", L"BeyonderHit2", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					pos.x -= 20.0f;
					SetPos(pos);
					mAnimator->Plays(L"RGolemHit", L"BeyonderHit2", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"GolemDie", false);
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
					mAnimator->Plays(L"GolemHit", L"BeyonderHit3", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					pos.x -= 20.0f;
					SetPos(pos);
					mAnimator->Plays(L"RGolemHit", L"BeyonderHit3", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"GolemDie", false);
				mState = State::DEATH;
			}
		}
	}
	void Golem::OnCollisionStay(Collider* other)
	{
	}
	void Golem::OnCollisionExit(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"Smash")
		{
			Vector2 pos = GetPos();
			DamageSkin* damage = new DamageSkin();
			Scene* playScene = SceneManager::GetPlayScene();
			damage->mGolem = this;
			damage->SetTargetName(L"Golem");
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
			damage->mGolem = this;
			damage->SetTargetName(L"Golem");
			damage->SetPos({ pos.x , pos.y - 150.0f });
			damage->SetAttackNumber(5);
			playScene->AddGameObject(damage, eColliderLayer::Damage);
		}

	}
	int Golem::AttackDamage()
	{
		int finalDamage = mPlayer->GetAttackDamage();
		mHp -= finalDamage;
		return finalDamage;
	}
}
