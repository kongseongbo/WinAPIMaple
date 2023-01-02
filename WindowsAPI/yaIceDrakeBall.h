#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Player;
	class IceDrakeBall : public GameObject
	{
	public:
		IceDrakeBall();
		~IceDrakeBall();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetDir(float dir) { mDir *= dir; }

		Player* mPlayer;
	private:
		float mAliveTime;
		Image* mImage;
		Animator* mAnimator;
	public:
		float mDir;
		Vector2 mDestPos;
	};
}

