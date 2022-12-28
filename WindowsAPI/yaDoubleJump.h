#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class DoubleJump : public GameObject
	{
	public:
		DoubleJump();
		~DoubleJump();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void PlayAni(bool look);


	private:
		float mAliveTime;
		Animator* mAnimator;

	public:
		Vector2 mDir;
		Vector2 mDestPos;
	};
}

