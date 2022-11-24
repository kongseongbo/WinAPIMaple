#include "yaScene.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaCollisionManager.h"
#include "yaApplication.h"
#include "yaCamera.h"

namespace ya
{

	Scene::Scene()
	{
		SceneManager::SetPlayScene(this);
		mObjects.resize(_COLLIDER_LAYER);
		mWindowInfo = Application::GetInstance().GetWindowData();
	}

	Scene::~Scene()
	{
		for (size_t y = 0; y < _COLLIDER_LAYER; y++)
		{
			for (size_t x = 0; x < mObjects[y].size(); x++)
			{
				delete mObjects[y][x];
				mObjects[y][x] = nullptr;
			}
		}
	}

	void Scene::Initialize()
	{
		

		for (size_t y = 0; y < _COLLIDER_LAYER; y++)
		{
			for (size_t x = 0; x < mObjects[y].size(); x++)
			{
				if (mObjects[y][x] == nullptr)
					continue;
				if (mObjects[y][x]->IsDeath())
					continue;

				mObjects[y][x]->Initialize();
			}
		}

	}

	void Scene::Tick()
	{
		for (size_t y = 0; y < _COLLIDER_LAYER; y++)
		{
			for (size_t x = 0; x < mObjects[y].size(); x++)
			{
				if (mObjects[y][x] == nullptr)
					continue;
				if (mObjects[y][x]->IsDeath())
					continue;
					mObjects[y][x]->Tick();
			}
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (size_t y = 0; y < _COLLIDER_LAYER; y++)
		{
			for (size_t x = 0; x < mObjects[y].size(); x++)
			{
				if (mObjects[y][x] == nullptr)
					continue;
				if (mObjects[y][x]->IsDeath())
					continue;

				Vector2 pos = mObjects[y][x]->GetPos();
				pos = Camera::CalculatePos(pos);
				if (pos.x < -100 
					|| pos.y < -100)
					continue;
				if (pos.x > mWindowInfo.width + 100 
					|| pos.y > mWindowInfo.height + 100)
					continue;

				mObjects[y][x]->Render(hdc);
			}
		}

		// �̴��������� ������Ѵ�.
	}

	void Scene::Enter()
	{
	}

	void Scene::Exit()
	{
		//CollisionManager::Clear();
	}

	void Scene::AddGameObject(GameObject* object, eColliderLayer type)
	{
		if (object == nullptr)
			return;

		mObjects[(UINT)type].push_back(object);
	}
}