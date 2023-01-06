#include "yaExBar.h"
#include "yaImage.h"
#include "yaPlayer.h"
#include "yaSceneManager.h"

namespace ya
{
	ExBar::ExBar(eUIType type)
		: UiBase(type)
	{
	}
	ExBar::~ExBar()
	{
	}
	void ExBar::OnInit()
	{
	}
	void ExBar::OnActive()
	{
	}
	void ExBar::OnInActive()
	{

	}
	void ExBar::OnTick()
	{
	}

	void ExBar::OnRender(HDC hdc)
	{
		if (mImage == nullptr)
			return;

		SceneManager* scene;

		Player* playerObj = dynamic_cast<Player*>(mTarget);

		int ex = _Ex;

		float xRatioEx = (ex / 100.0f);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		if (mTarget != nullptr)
		{
			if (scene->GetPlaySceneType() == eSceneType::Logo
				|| scene->GetPlaySceneType() == eSceneType::Play)
			{
				if (mImage->GetKey() == L"exbar1")
				{
					AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
						, mImage->GetWidth(), mImage->GetHeight()
						, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
				}
				if (mImage->GetKey() == L"ex1")
				{
					AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
						, mImage->GetWidth() * xRatioEx, mImage->GetHeight()
						, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
				}
			}
		}
	}

	void ExBar::OnClear()
	{

	}
}
