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


namespace ya
{
	Player::Player()
		: mSpeed(1.0f)
		, mHp(100)
		, skillstack(0)
		, skillTime(0.0f)
		, mMoveLeft(true)
		, RL('L')
	{
		SetName(L"Player");
		SetPos({ 500.0f, -650.0f });
		SetScale({ 1.0f, 1.0f });

		

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Player", L"..\\Resources\\Animations\\Player\\Idle\\stand.bmp");
		}


		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Up"
			, L"MoveUp");

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
			, L"BeyonderEffect1",Vector2(-200.0f,-50.0f));
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
			, L"RBeyonderEffect1", Vector2(200.0f, -50.0f));
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
		mMisiileDir = Vector2::One;
		Camera::SetTarget(this);
		//float x = math::lerp(1.0f, 3.0f, 0.5f);
	}

	Player::~Player()
	{

	}

	void Player::Tick()
	{
		GameObject::Tick();
		Vector2 pos = GetPos();

		if (KEY_DOWN(eKeyCode::W))
		{
			mAnimator->Play(L"MoveUp", true);
		}
		if (KEY_DOWN(eKeyCode::S))
		{
			//mAnimator->Play(L"MoveDown", true);
		}
		if (KEY_DOWN(eKeyCode::A))
		{
			mAnimator->Play(L"MoveLeft", true);
			RL = 'L';
		}
		if (KEY_DOWN(eKeyCode::D))
		{
			mAnimator->Play(L"MoveRight", true);
			RL = 'R';
		}

		if (KEY_UP(eKeyCode::W))
		{
			mAnimator->Play(L"Idle", true);
		}
		if (KEY_UP(eKeyCode::S))
		{
			mAnimator->Play(L"Idle", true);
		}
		if (KEY_UP(eKeyCode::A))
		{
			if(KEY_PREESE(eKeyCode::D))
				mAnimator->Play(L"MoveRight", true);
			else
				mAnimator->Play(L"Idle", true);
		}
		if (KEY_UP(eKeyCode::D))
		{
			if (KEY_PREESE(eKeyCode::A))
				mAnimator->Play(L"MoveLeft", true);
			else
				mAnimator->Play(L"RIdle", true);
		}

		if (KEY_PREESE(eKeyCode::W))
		{
			pos.y -= 120.0f * Time::DeltaTime();

			//GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, -200.0f));
		}
		if (KEY_PREESE(eKeyCode::A))
		{
			if (mMoveLeft == false)
				return;
			
			pos.x -= 120.0f * Time::DeltaTime();
			//missile->mDir.x = 1.0f;
			//GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));

			//Vector2 pos = GetPos();
			//
			//pos = math::lerp(pos, dest, 0.003f);
			//SetPos(pos);
			//pos = math::lerp(pos, )

		}
		if (KEY_PREESE(eKeyCode::D))
		{
			if (mMoveRight == false)
				return;

			pos.x += 120.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(200.0f, 0.0f));
			
		}
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Rigidbody* rigidbody = GetComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();
			if (KEY_PREESE(eKeyCode::S))
			{
				//velocity.y = -300.0f;
				rigidbody->SetVelocity(velocity);
			}
			else
			{
				velocity.y = -500.0f;
				rigidbody->SetGround(false);
				rigidbody->SetVelocity(velocity);
				UIManager::Pop(eUIType::OPTION);
			}
		}

		//Inventory
		if (KEY_DOWN(eKeyCode::I))
		{
			//포탈
			//mAnimator->Play(L"p", true);

			BackPack* backPack = new BackPack();
			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(backPack, eColliderLayer::Player_Projecttile);
		}
		//Skill Smash 
		if (KEY_DOWN(eKeyCode::LCTRL))
		{
			if (skillstack == 0)
			{
				skillstack++;
				if(RL == 'L')
					mAnimator->Play(L"Smash1", false);
				else if(RL == 'R')
					mAnimator->Play(L"RSmash1", false);
			}
			else if (skillstack == 1)
			{
				skillstack++;
				skillTime = 0.0f;
				if (RL == 'L')
					mAnimator->Play(L"Smash2", false);
				else if (RL == 'R')
					mAnimator->Play(L"RSmash2", false);
			}
			else if (skillstack == 2)
			{
				skillstack = 0;
				if (RL == 'L')
					mAnimator->Play(L"Smash3", false);
				else if (RL == 'R')
					mAnimator->Play(L"RSmash3", false);
			}
		}
		
		//Skill Beyonder
		if (KEY_DOWN(eKeyCode::LSHIFT))
		{


			if (skillstack == 0)
			{
				skillstack++;

				if (RL == 'L')
					mAnimator->Plays(L"Beyonder1", L"BeyonderEffect1", false, false);
				else if (RL == 'R')
					mAnimator->Plays(L"RBeyonder1", L"RBeyonderEffect1", false, false);
				
			}
			else if (skillstack == 1)
			{
				skillstack++;
				skillTime = 0.0f;

				if (RL == 'L')
					mAnimator->Plays(L"Beyonder2", L"BeyonderEffect2", false, false);
				else if (RL == 'R')
					mAnimator->Plays(L"RBeyonder2", L"RBeyonderEffect2", false, false);
			}
			else if (skillstack == 2)
			{
				skillstack = 0;

				if (RL == 'L')
					mAnimator->Plays(L"Beyonder3", L"BeyonderEffect3", false, false);
				else if (RL == 'R')
					mAnimator->Plays(L"RBeyonder3", L"RBeyonderEffect3", false, false);
			}
		}
		if (skillstack > 0)
		{
			skillTime += Time::DeltaTime();

			if (skillTime > 5.0f)
			{
				skillTime = 0.0f;
				skillstack = 0;
			}
		}
		SetPos(pos);
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
		int a = 0;
	}

	void Player::OnCollisionStay(Collider* other)
	{

	}

	void Player::OnCollisionExit(Collider* other)
	{

	}

	void Player::WalkComplete()
	{
		Missile* missile = new Missile();

		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(missile, eColliderLayer::Player_Projecttile);

		Vector2 playerPos = GetPos();
		Vector2 playerScale = GetScale() / 2.0f;
		Vector2 missileScale = missile->GetScale();

		missile->SetPos((playerPos + playerScale) - (missileScale / 2.0f));
	}
}
