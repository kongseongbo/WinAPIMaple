#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Player;
	class Image;
	class IceDrake : public GameObject
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
		IceDrake();
		~IceDrake();

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

		void AddBall();
		int AttackDamage();
		int GetState() { return (int)mState; }
		void SetTime(float time) { t = time; }

		Player* mPlayer;

	private:
		State mState = State::IDLE;
		Animator* mAnimator;
		Image* mImage;
		bool mMoveLeft;
		float mTime;
		float mDir;
		float distance;
		int mHp;
		int mAttackDamage;
		float t;
	};

}