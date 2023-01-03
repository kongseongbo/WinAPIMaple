#include "yaIceDrake.h"
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
#include "yaIceDrakeBall.h"
namespace ya
{
	IceDrake::IceDrake()
		: mTime(0.0f)
		, mDir(1.0f)
		, mMoveLeft(false)
		, mHp(30000)
		, distance(0.0f)
		, t(0.0f)
	{
		SetName(L"IceDrake");
		SetPos({ 1100.0f, 820.0f });
		SetScale({ 1.0f, 1.0f });
		
		mImage = Resources::Load<Image>(L"MushHp", L"..\\Resources\\Image\\HpMpBar\\MonsterHp.bmp");

		mAnimator = new Animator();
		//����
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\IceDrake\\Idle"
			, L"DrakeIdle", Vector2({ -10.0f, 0.0f }), 0.3f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\IceDrake\\Move"
			, L"DrakeMoveLeft", Vector2({ -10.0f, 0.0f }), 0.4f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\IceDrake\\Attack"
			, L"DrakeAttack", Vector2({ -10.0f, 0.0f }), 0.2f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\IceDrake\\Hit"
			, L"DrakeHit", Vector2({ -10.0f, 0.0f }));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\IceDrake\\Die"
			, L"DrakeDie", Vector2({ -10.0f, 0.0f }));

		//������
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\IceDrake\\RMove"
			, L"DrakeMoveRight", Vector2({ 30.0f, 0.0f }), 0.4f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\IceDrake\\RAttack"
			, L"RDrakeAttack", Vector2({ 30.0f, 0.0f }), 0.2f);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\IceDrake\\RHit"
			, L"RDrakeHit", Vector2({ 30.0f, 0.0f }));

		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\SmashHit"
			, L"SmashHit");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\BeyonderHit1"
			, L"BeyonderHit1");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\BeyonderHit2"
			, L"BeyonderHit2");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\BeyonderHit3"
			, L"BeyonderHit3");

		mAnimator->Play(L"DrakeIdle", true);
		//mAnimator->FindEvents(L"MushMoveLeft")->mStartEvent = std::bind(&MushMom::WarkAnimator, this);
		//mAnimator->GetStartEvent(L"MushMoveLeft") = std::bind(&MushMom::WarkAnimator, this);
		//mAnimator->FindEvents(L"DrakeAttack")->mCompleteEvent = std::bind(&IceDrake::AddBall, this);
		mAnimator->GetCompleteEvent(L"DrakeAttack") = std::bind(&IceDrake::AddBall, this);
		mAnimator->GetCompleteEvent(L"RDrakeAttack") = std::bind(&IceDrake::AddBall, this);
		AddComponent(mAnimator);
		AddComponent(new Collider());

	}

	IceDrake::~IceDrake()
	{

	}

	void IceDrake::Tick()
	{
		GameObject::Tick();

		switch (mState)
		{
		case ya::IceDrake::State::IDLE:
			Idle();
			break;
		case ya::IceDrake::State::MOVE:
			Move();
			break;
		case ya::IceDrake::State::ATTACK:
			Attack();
			break;
		case ya::IceDrake::State::HIT:
			Hit();
			break;
		case ya::IceDrake::State::DEATH:
			Death();
			break;
		default:
			break;
		}

	}
	void IceDrake::Idle()
	{
		mTime += t * Time::DeltaTime();
		if (mTime > 5.0f)
		{
			mState = State::MOVE;
			mAnimator->Play(L"DrakeMoveLeft", true);
			mTime = 0.0f;
		}
	}
	void IceDrake::Move()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.0f && mMoveLeft)
		{
			mDir *= -1.0f;
			mTime = 0.0f;
			mAnimator->Play(L"DrakeMoveLeft", true);
			mMoveLeft = false;
		}

		if (mTime > 3.0f)
		{
			mDir *= -1.0f;
			mTime = 0.0f;
			mAnimator->Play(L"DrakeMoveRight", true);
			mMoveLeft = true;
		}

		Vector2 pos = GetPos();
		pos.x -= (mDir * 50.0f) * Time::DeltaTime();
		SetPos(pos);
	}
	void IceDrake::Attack()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.3f)
		{
			if (!mMoveLeft)
			{
				mAnimator->Play(L"DrakeMoveLeft", true);
				mState = State::MOVE;
			}
			else
			{
				mAnimator->Play(L"DrakeMoveRight", true);
				mState = State::MOVE;
			}
			mTime = 0.0f;
		}

	}
	void IceDrake::Hit()
	{
		mTime += Time::DeltaTime();
		if (mHp <= 0)
		{
			mAnimator->Play(L"DrakeDie", false);
			mState = State::DEATH;
		}
		else if (mHp > 0)
		{
			if (mTime > 1.5f)
			{
				if (mPlayer->GetLook() == true)
				{
					mAnimator->Play(L"DrakeAttack", true);
				}
				else
				{
					mAnimator->Play(L"RDrakeAttack", true);
				}
				mState = State::ATTACK;
				mTime = 0.0f;
			}
		}

	}
	void IceDrake::Death()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.0f)
		{
			GameObject* gameObj = this;
			gameObj->Death();
			mTime = 0.0f;
			mPlayer->SetEx(50);
		}
	}
	void IceDrake::AddBall()
	{

		IceDrakeBall* AttackBall = new IceDrakeBall();
		AttackBall->SetPos(GetPos());
		AttackBall->mPlayer = this->mPlayer;
		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(AttackBall, eColliderLayer::Monster);
		if(mPlayer->GetLook() == false)
			AttackBall->SetDir(-1.0f);
	}
	void IceDrake::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth() * (scale.x / 2.0f));
		finalPos.y = pos.y + 55.0f;

		Vector2 rect;
		rect.x = mImage->GetWidth();
		rect.y = mImage->GetHeight();

		float xRatioHp = (mHp / 30000.0f);

		finalPos = Camera::CalculatePos(finalPos);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, finalPos.x, finalPos.y
			, rect.x * xRatioHp, rect.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);

		GameObject::Render(hdc);
	}
	void IceDrake::OnCollisionEnter(Collider* other)
	{
		GameObject* gameObj = other->GetOwner();
		Vector2 pos = GetPos();
		if (gameObj->GetName() == L"Smash")
		{
			if (mHp > 0)
			{
				if (mPlayer->GetLook() == true)
				{
					mAnimator->Plays(L"DrakeHit", L"SmashHit", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					mAnimator->Plays(L"RDrakeHit", L"SmashHit", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"DrakeDie", false);
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
					mAnimator->Plays(L"DrakeHit", L"BeyonderHit1", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					mAnimator->Plays(L"RDrakeHit", L"BeyonderHit1", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"DrakeDie", false);
				mState = State::DEATH;
			}
		}
		if (gameObj->GetName() == L"Beyonder2")
		{
			if (mHp > 0)
			{

				if (mPlayer->GetLook() == true)
				{
					mAnimator->Plays(L"DrakeHit", L"BeyonderHit2", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					mAnimator->Plays(L"RDrakeHit", L"BeyonderHit2", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"DrakeDie", false);
				mState = State::DEATH;
			}
		}
		if (gameObj->GetName() == L"Beyonder3")
		{
			if (mHp > 0)
			{

				if (mPlayer->GetLook() == true)
				{
					mAnimator->Plays(L"DrakeHit", L"BeyonderHit3", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
				else
				{
					mAnimator->Plays(L"RDrakeHit", L"BeyonderHit3", false, false);
					mState = State::HIT;
					mTime = 0.0f;
				}
			}
			else
			{
				mAnimator->Play(L"DrakeDie", false);
				mState = State::DEATH;
			}
		}
	}
	void IceDrake::OnCollisionStay(Collider* other)
	{
	}
	void IceDrake::OnCollisionExit(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"Smash")
		{
			Vector2 pos = GetPos();
			DamageSkin* damage = new DamageSkin();
			Scene* playScene = SceneManager::GetPlayScene();
			damage->mIceDrake = this;
			damage->SetTargetName(L"IceDrake");
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
			damage->mIceDrake = this;
			damage->SetTargetName(L"IceDrake");
			damage->SetPos({ pos.x , pos.y - 150.0f });
			damage->SetAttackNumber(5);
			playScene->AddGameObject(damage, eColliderLayer::Damage);
		}

	}
	int IceDrake::AttackDamage()
	{
		int finalDamage = mPlayer->GetAttackDamage();
		mHp -= finalDamage;
		return finalDamage;
	}
}
