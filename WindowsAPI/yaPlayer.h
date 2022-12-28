#pragma once
#include "yaGameObject.h"

namespace ya
{
	int _PlayerHp = 1000;
	int _PlayerMp = 1000;

	class Animator;
	class Image;
	class Player : public GameObject
	{
	public:
		enum class State
		{
			IDLE,
			MOVE,
			HIT,
			SMASH,
			BEYONDER,
			DEATH,
		};
		Player();
		~Player();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetMoveLeft(bool move) { mMoveLeft = move; }
		void SetMoveRight(bool move) { mMoveRight = move; }
		void SetEx(int ex) { mEx += ex; }
		void SetHitDamage(int damage) { mHitDamage = damage; }
		bool GetLook() { return mRightLook; }

		void Idle();
		void Move();
		void Hit();
		void Smash();
		void Beyonder();
		void Death();

		int GetAttackDamage() { return mPlayerSTR; }
		int GetPlayerHitDamage() { return mHitDamage; }

		void CreateDamage();

	private:
		float mCoff;
		float mSpeed;
		float mTime;
		Image* mImage;
		Animator* mAnimator;
		Vector2 mMisiileDir;
		Vector2 dest;
		State mState = State::IDLE;

		int mHitDamage;
		int mPlayerSTR;
		int mEx;
		int mLv;
		int mSkillStack;
		float mSkillTime;
		bool mMoveLeft;
		bool mMoveRight;
		bool mRightLook;
		int mJumpStack;
	};

}