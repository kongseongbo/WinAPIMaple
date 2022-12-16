#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Player;
	class Image;
	class Golem : public GameObject
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
		Golem();
		~Golem();

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

		int AttackDamage();

		int GetState() { return (int)mState; }

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
	};

}