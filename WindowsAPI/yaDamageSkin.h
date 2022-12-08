#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MushMom;
	class Image;
	class DamageSkin : public GameObject
	{
	public:
		DamageSkin();
		~DamageSkin();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key, const std::wstring& fileName);

		MushMom* mushmom;
	private:
		Image* mImage;
		float mSpeed;
		float mAliveTime;
		int alpha;

		Vector2 pos;
	};
}