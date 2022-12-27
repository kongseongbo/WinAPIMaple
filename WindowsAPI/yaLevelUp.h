#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class LevelUp : public GameObject
	{
	public:
		LevelUp();
		~LevelUp();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void PlayAni();


	private:
		float mAliveTime;
		Animator* mAnimator;

	public:
		Vector2 mDir;
		Vector2 mDestPos;
	};
}

