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


namespace ya
{
	MushMom::MushMom()
		: mTime(0.0f)
		, mDir(1.0f)
		, mMoveLeft(false)
		, mHp(50)
	{
		SetName(L"MushMom1");
		SetPos({ 900.0f, 820.0f });
		SetScale({ 1.0f, 1.0f });

		/*if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"MushMom", L"..\\Resources\\Animations\\Mushmom\\MushIdle\\stand.bmp");
		}*/

		mAnimator = new Animator();


		//¿ÞÂÊ
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\MushIdle"
			, L"MushIdle", Vector2({0.0f, -40.0f}));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\MushMoveLeft"
			, L"MushMoveLeft", Vector2({ 0.0f, -40.0f }), 0.3f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\MushMoveRight"
			, L"MushMoveRight", Vector2({ 0.0f, -40.0f }),0.3f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\MushHit"
			, L"MushHit", Vector2({ 0.0f, -30.0f }));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\MushMom\\MushDie"
			, L"MushDie", Vector2({ 0.0f, -30.0f }), 0.2f);
		
		mAnimator->Play(L"MushIdle", true);
		//mAnimator->FindEvents(L"MushMoveLeft")->mStartEvent = std::bind(&MushMom::WarkAnimator, this);
		//mAnimator->GetStartEvent(L"MushMoveLeft") = std::bind(&MushMom::WarkAnimator, this);

		AddComponent(mAnimator);
		AddComponent(new Collider());

	}

	MushMom::MushMom(Vector2 position)
		: mTime(0.0f)
	{
		SetName(L"MushMom2");
		SetPos(position);
		SetScale({ 1.0f, 1.0f });


		AddComponent(new Animator());
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
	}
	void MushMom::Hit()
	{
		if (mHp == 0)
		{
			mAnimator->Play(L"MushDie", false);
			mState = State::DEATH;
		}
		else if(mHp >0 )
			mAnimator->Play(L"MushHit", false);
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
		if (mHp > 0)
		{
			mHp -= 10;
			mState = State::HIT;
		}
	}
	void MushMom::OnCollisionStay(Collider* other)
	{
		if (mHp > 0)
			mState = State::MOVE;
	}
	void MushMom::OnCollisionExit(Collider* other)
	{
		if (mHp > 0)
			mState = State::MOVE;
	}
}
