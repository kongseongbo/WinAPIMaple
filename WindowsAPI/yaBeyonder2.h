#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Sound;
	class Image;
	class SkillBeyonder2 : public GameObject
	{
	public:
		SkillBeyonder2();
		~SkillBeyonder2();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

	private:
		float mAliveTime;
		Image* mImage;
		Sound* mSound;
	public:
		Vector2 mDir;
		Vector2 mDestPos;
	};
}

