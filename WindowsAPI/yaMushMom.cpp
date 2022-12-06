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

namespace ya
{
	MushMom::MushMom()
		: mTime(0.0f)
		, mDir(1.0f)
		, mMoveLeft(false)
		, mHp(50)
		, distance(0.0f)
	{
		SetName(L"MushMom1");
		SetPos({ 900.0f, 820.0f });
		SetScale({ 1.0f, 1.0f });

		/*if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"MushMom", L"..\\Resources\\Animations\\Mushmom\\MushIdle\\stand.bmp");
		}*/

		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\MushDie"
			, L"MushDie", Vector2({ 0.0f, -30.0f }), 0.2f);

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

		if (mPlayer == nullptr)
			return;

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
		if (mTime > 2.0f)
		{
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

		if (mHp == 0)
		{
			mAnimator->Play(L"MushDie", false);
			mState = State::DEATH;
		}
		else if (mHp > 0)
		{
			if (mTime > 1.5f)
			{
				if (!mMoveLeft)
				{
					mAnimator->Play(L"MushAttack", false);
				}
				else
				{
					mAnimator->Play(L"RMushAttack", false);
				}
				mAnimator->Play(L"MushAttack", false);
				mState = State::ATTACK;
				mTime = 0.0f;
			}
		}
		
	}
	void MushMom::Death()
	{
		mTime += Time::DeltaTime();
		if (mTime > 4.0f)
		{
			GameObject* gameObj = this;
			gameObj->Death();
			mTime = 0.0f;
		}
	}

	void MushMom::Render(HDC hdc)
	{
		
		GameObject::Render(hdc);
	}
	void MushMom::OnCollisionEnter(Collider* other)
	{
		Vector2 pos = GetPos();
		if (mHp > 0)
		{
			mHp -= 10;
			if (!mMoveLeft)
			{
				/*pos.x += 20.0f;
				SetPos(pos);*/
				mAnimator->Play(L"MushHit", false);
				mState = State::HIT;
			}
			else
			{
				/*pos.x -= 20.0f;
				SetPos(pos);*/
				mAnimator->Play(L"RMushHit", false);
				mState = State::HIT;
			}
		}
		else if (mHp <= 0)
		{
			mAnimator->Play(L"MushDie", false);
			mState = State::DEATH;
		}
	}
	void MushMom::OnCollisionStay(Collider* other)
	{
	}
	void MushMom::OnCollisionExit(Collider* other)
	{
	}
}
