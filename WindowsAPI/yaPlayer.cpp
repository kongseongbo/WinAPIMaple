#include "yaPlayer.h"
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
#include "yaBackPack.h"
#include "yaRigidbody.h"
#include "yaUIManager.h"

#include "yaSkillSmash.h"
#include "yaSkillSmash2.h"
#include "yaSkillSmash3.h"

#include "yaBeyonder.h"
#include "yaBeyonder2.h"
#include "yaBeyonder3.h"

#include "yaDamageSkin.h"

#include "yaHUD.h"
namespace ya
{
	Player::Player()
		: mSpeed(1.0f)
		, mTime(0.0f)
		, mPlayerSTR(0)
		, mEx(0)
		, mHitDamage(0)
		, mSkillStack(0)
		, mSkillTime(0.0f)
		, mMoveLeft(false)
		, mMoveRight(false)
		, mRightLook(false)
	{
		SetName(L"Player");
		SetPos({ 1500.0f, 750.0f });
		SetScale({ 1.0f, 1.0f });

		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Up"
			, L"MoveUp");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\LevelUp"
			, L"LevelUp");

		//왼쪽
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Idle"
			, L"Idle");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\MoveLeft"
			, L"MoveLeft");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Smash1"
			, L"Smash1");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Smash2"
			, L"Smash2");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Smash3"
			, L"Smash3");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Beyonder\\Beyonder1"
			, L"Beyonder1");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Beyonder\\Beyonder2"
			, L"Beyonder2");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Beyonder\\Beyonder3"
			, L"Beyonder3");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Beyonder\\BeyonderEffect1"
			, L"BeyonderEffect1", Vector2(-150.0f, -50.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Beyonder\\BeyonderEffect2"
			, L"BeyonderEffect2", Vector2(-200.0f, -50.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Beyonder\\BeyonderEffect3"
			, L"BeyonderEffect3", Vector2(-200.0f, -50.0f));

		//오른쪽
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\RIdle"
			, L"RIdle");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\MoveRight"
			, L"MoveRight", Vector2(-15.0f, 0.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\RSmash1"
			, L"RSmash1");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\RSmash2"
			, L"RSmash2");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\RSmash3"
			, L"RSmash3");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Beyonder\\RBeyonder1"
			, L"RBeyonder1");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Beyonder\\RBeyonder2"
			, L"RBeyonder2");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Beyonder\\RBeyonder3"
			, L"RBeyonder3");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Beyonder\\RBeyonderEffect1"
			, L"RBeyonderEffect1", Vector2(150.0f, -50.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Beyonder\\RBeyonderEffect2"
			, L"RBeyonderEffect2", Vector2(200.0f, -50.0f));
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Beyonder\\RBeyonderEffect3"
			, L"RBeyonderEffect3", Vector2(200.0f, -50.0f));

		//포탈
		/*mAnimator->CreateAnimations(L"..\\Resources\\Animations\\p"
			, L"p");*/

			// 한 이미지에 전부 들어있을때
			/*mAnimator->CreateAnimation(L"Idle", mImage
				, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f)
				, Vector2(5.0f, -20.0f), 3, 0.1f);

			mAnimator->CreateAnimation(L"MoveDown", mImage
				, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f)
				, Vector2(5.0f, -20.0f), 10, 0.1f);
			mAnimator->CreateAnimation(L"MoveLeft", mImage
				, Vector2(0.0f, 650.0f), Vector2(120.0f, 130.0f)
				, Vector2(5.0f, -20.0f), 10, 0.1f);
			mAnimator->CreateAnimation(L"MoveUp", mImage
				, Vector2(0.0f, 780.0f), Vector2(120.0f, 130.0f)
				, Vector2(5.0f, -20.0f), 10, 0.1f);
			mAnimator->CreateAnimation(L"MoveRight", mImage
				, Vector2(0.0f, 910.0f), Vector2(120.0f, 130.0f)
				, Vector2(5.0f, -20.0f), 10, 0.1f);*/

		mAnimator->Play(L"Idle", true);
		//mAnimator->FindEvents(L"MoveRight")->mCompleteEvent = std::bind(&Player::WalkComplete, this);
		//mAnimator->GetCompleteEvent(L"MoveRight") = std::bind(&Player::WalkComplete, this);

		//mAnimator->Play(L"MoveRight", true);
		//mAnimator->mCompleteEvent = std::bind(&Player::WalkComplete, this);
		AddComponent(mAnimator);

		//아래
		Collider* coliider = new Collider();
		AddComponent(coliider);
		coliider->SetOffset(Vector2(0.0f, 103.0f));
		coliider->SetScale(Vector2(10.0f, 10.0f));

		//위
		Collider* coliider2 = new Collider();
		AddComponent(coliider2);
		coliider2->SetOffset(Vector2(0.0f, 30.0f));
		coliider2->SetScale(Vector2(10.0f, 10.0f));

		//오른쪽
		Collider* coliider3 = new Collider();
		AddComponent(coliider3);
		coliider3->SetOffset(Vector2(20.0f, 50.0f));
		coliider3->SetScale(Vector2(10.0f, 10.0f));

		//왼쪽
		Collider* coliider4 = new Collider();
		AddComponent(coliider4);
		coliider4->SetOffset(Vector2(-30.0f, 50.0f));
		coliider4->SetScale(Vector2(10.0f, 10.0f));

		AddComponent<Rigidbody>();

		mCoff = 0.1f;
		//mMisiileDir = Vector2::One;
		//Camera::SetTarget(this);
		//float x = math::lerp(1.0f, 3.0f, 0.5f);
	}

	Player::~Player()
	{

	}

	void Player::Tick()
	{
		GameObject::Tick();
		
		switch (mState)
		{
		case ya::Player::State::IDLE:
			mSkillStack = 0;
			Idle();
			break;
		case ya::Player::State::MOVE:
			Move();
			break;
		case ya::Player::State::HIT:
			Hit();
			break;
		case ya::Player::State::SMASH:
			Smash();
			break;
		case ya::Player::State::BEYONDER:
			Beyonder();
			break;
		/*case ya::Player::State::MOVESMASH:
		MoveSmash();
		break;*/
		case ya::Player::State::DEATH:
		Death();
		break;
		default:
			break;
		}
	}

	void Player::Idle()
	{
		mAnimator->SetAniAlpha(255);
		mAnimator->Play(L"Idle", true);
		if (mRightLook)
		{
			mAnimator->Play(L"RIdle", true);
		}
		if (KEY_DOWN(eKeyCode::UP))
		{
			mAnimator->Play(L"MoveUp", true);
			mState = State::MOVE;
		}
		if (KEY_DOWN(eKeyCode::LEFT))
		{
			mAnimator->Play(L"MoveLeft", true);
			mState = State::MOVE;
		}
		if (KEY_DOWN(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"MoveRight", true);
			mState = State::MOVE;
		}
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Rigidbody* rigidbody = GetComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();
			if (KEY_PREESE(eKeyCode::DOWN))
			{
				rigidbody->SetVelocity(velocity);
			}
			else
			{
				velocity.y = -500.0f;
				rigidbody->SetGround(false);
				rigidbody->SetVelocity(velocity);
			}
			UIManager::Pop(eUIType::OPTION);
		}

		if (KEY_DOWN(eKeyCode::LCTRL))
			mState = State::SMASH;
		
		if (KEY_DOWN(eKeyCode::LSHIFT))
			mState = State::BEYONDER;
		
	}
	void Player::Move()
	{
		Vector2 pos = GetPos();
		if (KEY_PREESE(eKeyCode::UP))
		{
			pos.y -= 120.0f * Time::DeltaTime();
		}
		if (KEY_PREESE(eKeyCode::LEFT))
		{
			if (mMoveLeft == false)
				return;

			pos.x -= 120.0f * Time::DeltaTime();
			mRightLook = false;
		}
		if (KEY_PREESE(eKeyCode::RIGHT))
		{
			if (mMoveRight == false)
				return;

			pos.x += 120.0f * Time::DeltaTime();
			mRightLook = true;
		}
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Rigidbody* rigidbody = GetComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();
			if (KEY_PREESE(eKeyCode::DOWN))
			{
				rigidbody->SetVelocity(velocity);
			}
			else
			{
				velocity.y = -500.0f;
				rigidbody->SetGround(false);
				rigidbody->SetVelocity(velocity);
			}
			UIManager::Pop(eUIType::OPTION);
		}
		if (KEY_UP(eKeyCode::UP) || KEY_UP(eKeyCode::LEFT) || KEY_UP(eKeyCode::RIGHT))
		{
			mState = State::IDLE;
		}
		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			mState = State::SMASH;
		}
		if (KEY_DOWN(eKeyCode::LSHIFT))
		{
			mState = State::BEYONDER;
		}
		//if ((KEY_PREESE(eKeyCode::RIGHT) || KEY_PREESE(eKeyCode::LEFT)) &&  KEY_DOWN(eKeyCode::LCTRL))
		//{
		//	mState = State::MOVESMASH;
		//}

		SetPos(pos);
	}
	void Player::Hit()
	{
		mTime += Time::DeltaTime();
		mAnimator->SetAniAlpha(150);
		Vector2 pos = GetPos();
		DamageSkin* damage = new DamageSkin();
		Scene* playScene = SceneManager::GetPlayScene();
		damage->mPlayer = this;
		damage->SetTargetName(L"Player");
		damage->SetPos({ pos.x , pos.y - 50.0f });
		damage->SetAttackNumber(1);
		playScene->AddGameObject(damage, eColliderLayer::Damage);

		if (mTime > 1.0f)
			mState = State::IDLE;
	}
	void Player::Smash()
	{
		mSkillTime += Time::DeltaTime();
		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			if (mSkillTime > 5.0f)
			{
				mSkillTime = 0.0f;
				mSkillStack = 0;
			}

			if (mSkillStack == 0)
			{
				mSkillStack++;
				mPlayerSTR = 100;
				if (mRightLook)
				{
					mAnimator->Play(L"RSmash1", false);
					SkillSmash* smash = new SkillSmash();
					Scene* playScene = SceneManager::GetPlayScene();
					playScene->AddGameObject(smash, eColliderLayer::Player_Smash);
					Vector2 playerPos = GetPos();
					smash->SetPos(Vector2(playerPos.x + 100.0f, playerPos.y + 50.0f));
					
				}
				else
				{
					mAnimator->Play(L"Smash1", false);
					SkillSmash* smash = new SkillSmash();
					Scene* playScene = SceneManager::GetPlayScene();
					playScene->AddGameObject(smash, eColliderLayer::Player_Smash);
					Vector2 playerPos = GetPos();
					smash->SetPos(Vector2(playerPos.x - 100.0f, playerPos.y + 50.0f));
				}
			}
			else if (mSkillStack == 1)
			{
				mSkillTime = 0.0f;
				mSkillStack++;
				mPlayerSTR = 220;
				if (mRightLook)
				{
					mAnimator->Play(L"RSmash2", false);
					SkillSmash2* smash = new SkillSmash2();
					Scene* playScene = SceneManager::GetPlayScene();
					playScene->AddGameObject(smash, eColliderLayer::Player_Smash);
					Vector2 playerPos = GetPos();
					smash->SetPos(Vector2(playerPos.x, playerPos.y + 50.0f));
				}
				else
				{
					mAnimator->Play(L"Smash2", false);
					SkillSmash2* smash = new SkillSmash2();
					Scene* playScene = SceneManager::GetPlayScene();
					playScene->AddGameObject(smash, eColliderLayer::Player_Smash);
					Vector2 playerPos = GetPos();
					smash->SetPos(Vector2(playerPos.x, playerPos.y + 50.0f));
				}
			}
			else if (mSkillStack == 2)
			{
				mSkillStack = 0;
				mPlayerSTR = 311;
				if (mRightLook)
				{
					mAnimator->Play(L"RSmash3", false);
					SkillSmash3* smash = new SkillSmash3();
					Scene* playScene = SceneManager::GetPlayScene();
					playScene->AddGameObject(smash, eColliderLayer::Player_Smash);
					Vector2 playerPos = GetPos();
					smash->SetPos(Vector2(playerPos.x + 100.0f, playerPos.y));
				}
				else
				{
					mAnimator->Play(L"Smash3", false);
					SkillSmash3* smash = new SkillSmash3();
					Scene* playScene = SceneManager::GetPlayScene();
					playScene->AddGameObject(smash, eColliderLayer::Player_Smash);
					Vector2 playerPos = GetPos();
					smash->SetPos(Vector2(playerPos.x - 100.0f, playerPos.y));
				}
			}
		}

		if (KEY_DOWN(eKeyCode::UP))
		{
			mAnimator->Play(L"MoveUp", true);
			mState = State::MOVE;
		}
		if (KEY_DOWN(eKeyCode::LEFT))
		{
			mAnimator->Play(L"MoveLeft", true);
			mState = State::MOVE;
		}
		if (KEY_DOWN(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"MoveRight", true);
			mState = State::MOVE;
		}
	}

	void Player::Beyonder()
	{
		mSkillTime += Time::DeltaTime();
		if (KEY_DOWN(eKeyCode::LSHIFT))
		{
			if (mSkillTime > 5.0f)
			{
				mSkillTime = 0.0f;
				mSkillStack = 0;
			}

			if (mSkillStack == 0)
			{
				mSkillStack++;
				mPlayerSTR = 163;
				if (mRightLook)
				{
					mAnimator->Plays(L"RBeyonder1", L"RBeyonderEffect1", false, false);
					SkillBeyonder* beyonder = new SkillBeyonder();
					Scene* playScene = SceneManager::GetPlayScene();
					playScene->AddGameObject(beyonder, eColliderLayer::Player_Beyonder);
					Vector2 playerPos = GetPos();
					beyonder->SetPos(Vector2(playerPos.x + 200.0f, playerPos.y + 50.0f));
				}
				else
				{
					mAnimator->Plays(L"Beyonder1", L"BeyonderEffect1", false, false);
					SkillBeyonder* beyonder = new SkillBeyonder();
					Scene* playScene = SceneManager::GetPlayScene();
					playScene->AddGameObject(beyonder, eColliderLayer::Player_Beyonder);
					Vector2 playerPos = GetPos();
					beyonder->SetPos(Vector2(playerPos.x - 200.0f, playerPos.y + 50.0f));
				}	
			}
			else if (mSkillStack == 1)
			{
				mSkillStack++;
				mSkillTime = 0.0f;
				mPlayerSTR = 243;
				if (mRightLook)
				{
					mAnimator->Plays(L"RBeyonder2", L"RBeyonderEffect2", false, false);
					SkillBeyonder2* beyonder = new SkillBeyonder2();
					Scene* playScene = SceneManager::GetPlayScene();
					playScene->AddGameObject(beyonder, eColliderLayer::Player_Beyonder);
					Vector2 playerPos = GetPos();
					beyonder->SetPos(Vector2(playerPos.x + 200.0f, playerPos.y + 50.0f));
				}
				else
				{
					mAnimator->Plays(L"Beyonder2", L"BeyonderEffect2", false, false);
					SkillBeyonder2* beyonder = new SkillBeyonder2();
					Scene* playScene = SceneManager::GetPlayScene();
					playScene->AddGameObject(beyonder, eColliderLayer::Player_Beyonder);
					Vector2 playerPos = GetPos();
					beyonder->SetPos(Vector2(playerPos.x - 200.0f, playerPos.y + 50.0f));
				}
			}
			else if (mSkillStack == 2)
			{
				mSkillStack = 0;
				mPlayerSTR = 302;
				if (mRightLook)
				{
					mAnimator->Plays(L"RBeyonder3", L"RBeyonderEffect3", false, false);
					SkillBeyonder3* beyonder = new SkillBeyonder3();
					Scene* playScene = SceneManager::GetPlayScene();
					playScene->AddGameObject(beyonder, eColliderLayer::Player_Beyonder);
					Vector2 playerPos = GetPos();
					beyonder->SetPos(Vector2(playerPos.x + 200.0f, playerPos.y + 50.0f));
				}
				else
				{
					mAnimator->Plays(L"Beyonder3", L"BeyonderEffect3", false, false);
					SkillBeyonder3* beyonder = new SkillBeyonder3();
					Scene* playScene = SceneManager::GetPlayScene();
					playScene->AddGameObject(beyonder, eColliderLayer::Player_Beyonder);
					Vector2 playerPos = GetPos();
					beyonder->SetPos(Vector2(playerPos.x - 200.0f, playerPos.y + 50.0f));
				}
			}
		}

		if (KEY_DOWN(eKeyCode::UP))
		{
			mAnimator->Play(L"MoveUp", true);
			mState = State::MOVE;
		}
		if (KEY_DOWN(eKeyCode::LEFT))
		{
			mAnimator->Play(L"MoveLeft", true);
			mState = State::MOVE;
		}
		if (KEY_DOWN(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"MoveRight", true);
			mState = State::MOVE;
		}
	}
	/*void Player::MoveSmash()
{
	Vector2 pos = GetPos();

	if (KEY_DOWN(eKeyCode::LCTRL))
	{
		if (mSkillTime > 5.0f)
		{
			mSkillTime = 0.0f;
			mSkillStack = 0;
		}

		if (mSkillStack == 0)
		{
			mSkillStack++;
			if (mRightLook)
			{
				pos.x += 1000.0f * Time::DeltaTime();
				mAnimator->Play(L"RSmash1", false);
			}
			else
			{
				pos.x -= 1000.0f * Time::DeltaTime();
				mAnimator->Play(L"Smash1", false);
			}
		}
		else if (mSkillStack == 1)
		{
			mSkillStack++;
			mSkillTime = 0.0f;
			if (mRightLook)
			{
				pos.x += 1000.0f * Time::DeltaTime();
				mAnimator->Play(L"RSmash2", false);
			}
			else
			{
				pos.x -= 1000.0f * Time::DeltaTime();
				mAnimator->Play(L"Smash2", false);
			}
		}
		else if (mSkillStack == 2)
		{
			mSkillStack = 0;
			if (mRightLook)
			{
				pos.x += 1000.0f * Time::DeltaTime();
				mAnimator->Play(L"RSmash3", false);
			}
			else
			{
				pos.x -= 1000.0f * Time::DeltaTime();
				mAnimator->Play(L"Smash3", false);
			}
		}
	}

	if (KEY_DOWN(eKeyCode::UP))
	{
		mAnimator->Play(L"MoveUp", true);
		mState = State::MOVE;
	}
	if (KEY_DOWN(eKeyCode::LEFT))
	{
		mAnimator->Play(L"MoveLeft", true);
		mState = State::MOVE;
	}
	if (KEY_DOWN(eKeyCode::RIGHT))
	{
		mAnimator->Play(L"MoveRight", true);
		mState = State::MOVE;
	}
	SetPos(pos);
}*/
	void Player::Death()
	{

	}
	void Player::Render(HDC hdc)
	{
		//HBRUSH blueBrush = CreateSolidBrush(RGB(153, 204, 255));
		//Brush brush(hdc, blueBrush);

		//HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		//Pen pen(hdc, redPen);

		

		GameObject::Render(hdc);
	}

	void Player::OnCollisionEnter(Collider* other)
	{
		
		mAnimator->SetAniAlpha(150);
	}

	void Player::OnCollisionStay(Collider* other)
	{
		mAnimator->SetAniAlpha(150);
	}

	void Player::OnCollisionExit(Collider* other)
	{
		mAnimator->SetAniAlpha(255);
	}

	//void Player::WalkComplete()
	//{
	//	Missile* missile = new Missile();
	//	Scene* playScene = SceneManager::GetPlayScene();
	//	playScene->AddGameObject(missile, eColliderLayer::Player_Projecttile);
	//	Vector2 playerPos = GetPos();
	//	Vector2 playerScale = GetScale() / 2.0f;
	//	Vector2 missileScale = missile->GetScale();
	//	missile->SetPos((playerPos + playerScale) - (missileScale / 2.0f));
	//}
}
