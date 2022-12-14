#include "yaLevelUp.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaAnimator.h"
#include "yaSound.h"

namespace ya
{
	LevelUp::LevelUp()
		: mAliveTime(2.0f)
	{
		SetName(L"LevelUp");
		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\LevelUp"
			, L"LevelUp", Vector2(0.0f, -250.0f), 0.2f);
		AddComponent(mAnimator);
	}

	LevelUp::~LevelUp()
	{
	}

	void LevelUp::Tick()
	{
		GameObject::Tick();
		
		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}
	}

	void LevelUp::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void LevelUp::PlayAni()
	{
		Sound* mSound = new Sound();
		mSound->LoadWavFile(L"..\\Sound\\LevelUp.wav");
		mAnimator->Play(L"LevelUp", false);
		mSound->Play(false);
		delete mSound;
	}
}