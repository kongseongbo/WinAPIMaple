#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Sound;
	class Image;
	class SkillBeyonder : public GameObject
	{
	public:
		SkillBeyonder();
		~SkillBeyonder();

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

