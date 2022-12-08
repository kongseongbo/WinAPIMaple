#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class SkillBeyonder3 : public GameObject
	{
	public:
		SkillBeyonder3();
		~SkillBeyonder3();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

	private:
		float mAliveTime;
		Image* mImage;
	public:
		Vector2 mDir;
		Vector2 mDestPos;
	};
}

