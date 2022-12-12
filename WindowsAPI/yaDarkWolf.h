#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Player;
	class Image;
	class DarkWolf : public GameObject
	{
	public:
		enum class State
		{
			REGEN,
			IDLE,
			MOVE,
			ATTACK,
			HIT,
			DEATH,
		};

	public:
		DarkWolf();
		~DarkWolf();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void Regen();
		void Idle();
		void Move();
		void Attack();
		void Hit();
		void Death();

		int AttackDamage();

		Player* mPlayer;

	private:
		State mState = State::REGEN;
		Animator* mAnimator;
		Image* mImage;
		bool mMoveLeft;
		float mTime;
		float mDir;
		float distance;
		int mHp;
		int mAttackDamage;
		int defense;
	};

}