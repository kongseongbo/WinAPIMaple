#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class MushMom : public GameObject
	{
	public:
		enum class State
		{
			IDLE,
			MOVE,
			ATTACK,
			HIT,
			DEATH,
		};

	public:
		MushMom();
		MushMom(Vector2 position);
		~MushMom();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void Idle();
		void Move();
		void Attack();
		void Hit();
		void Death();


	private:
		State mState = State::IDLE;
		Animator* mAnimator;
		Image* mImage;
		bool mMoveLeft;
		float mTime;
		float mDir;

		int mHp;
	};

}