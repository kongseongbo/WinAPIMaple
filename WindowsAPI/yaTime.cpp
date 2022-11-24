#include "yaTime.h"
#include "yaApplication.h"

namespace ya
{
	LARGE_INTEGER Time::mCpuFrequency;
	LARGE_INTEGER Time::mPrevFrequency;
	LARGE_INTEGER Time::mCurFrequency;
	float Time::mDeltaTime = 0.0f;
	float Time::mTime = 0.0f;
	float Time::mTimeScale = 1.0f;

	void Time::Initialize()
	{
		// Sleep();
		// CPU �ʴ� �ݺ��Ǵ� �������� ������ �Լ�
		QueryPerformanceFrequency(&mCpuFrequency);

		// ���α׷� ���� ������ cpu�� Ŭ�� ��
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Tick()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float differenceFrequency
			= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
		mDeltaTime = differenceFrequency / static_cast<float>(mCpuFrequency.QuadPart);

		// �ٽ� ������ ���� ���ο� ���� ������ ����
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		mTime += Time::DeltaTime();
		if (mTime > 1.0f)
		{
			wchar_t szFloat[50] = {};
			float fps = 1.0f / mDeltaTime;
			swprintf_s(szFloat, 50, L"fps : %f", fps);

			HWND hWnd 
				= Application::GetInstance().GetWindowData().hWnd;

			SetWindowText(hWnd, szFloat);
			mTime = 0.0f;
		}
	}
}