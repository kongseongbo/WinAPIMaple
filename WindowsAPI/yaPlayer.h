#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Image;
	class Player : public GameObject
	{
	public:
		enum class State
		{
			IDLE,
			MOVE,
			SMASH,
			BEYONDER,
			MOVESMASH,
			DEATH,
		};
		Player();
		~Player();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void WalkComplete();

		void SetHp(int hp) { mHp = hp; }
		int GetHp() { return mHp; }

		void SetMoveLeft(bool move) { mMoveLeft = move; }
		void SetMoveRight(bool move) { mMoveRight = move; }

		void Idle();
		void Move();
		void Smash();
		void MoveSmash();
		void Beyonder();
		void Death();



	private:
		float mCoff;
		float mSpeed;
		Image* mImage;
		Animator* mAnimator;
		Vector2 mMisiileDir;

		int mHp;
		Vector2 dest;

		State mState = State::IDLE;

		int mSkillStack;
		float mSkillTime;
		bool mMoveLeft;
		bool mMoveRight;
		bool mRightLook;
		
	};

}