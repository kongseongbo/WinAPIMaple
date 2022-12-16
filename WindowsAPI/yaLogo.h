#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Logo : public GameObject
	{
	public:
		Logo();
		~Logo();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		float mSpeed;
		float mAliveTime;
		Image* mImage;

	public:
		Vector2 mDir;
		Vector2 mDestPos;
	};
}

