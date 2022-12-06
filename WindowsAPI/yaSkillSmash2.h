#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Image;
	class SkillSmash2 : public GameObject
	{
	public:
		SkillSmash2();
		~SkillSmash2();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

	private:
		float mAliveTime;
		Image* mImage;
		Animator* mAnimator;

	public:
		Vector2 mDir;
		Vector2 mDestPos;
	};
}
