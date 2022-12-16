#pragma once
#include "yaGameObject.h"

namespace ya
{
	class DarkWolf;
	class Image;
	class DarkWolfTeleport : public GameObject
	{
	public:
		DarkWolfTeleport();
		~DarkWolfTeleport();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void abc();

		DarkWolf* mDarkWolf;

	private:
		float mAliveTime;
		Image* mImage;
		Animator* mAnimator;
		float mTime;
	public:
		Vector2 mDir;
		Vector2 mDestPos;
	};
}

