#pragma once
#include "yaGameObject.h"


namespace ya
{
	class Player;
	class Image;
	class BgImageObject : public GameObject
	{
	public:
		BgImageObject();
		~BgImageObject();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key ,const std::wstring& fileName);
		void SetPixelImage(const std::wstring& key, const std::wstring& fileName);
		
		Player* mPlayer;

	private:
		bool mbDebug;
		bool mGroundOX;
		bool mBlueGroundOX;
		bool ox ;
		Image* mImage;
		Image* mPixelImage;
	};
}
