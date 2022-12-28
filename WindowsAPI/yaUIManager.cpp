#include "yaUIManager.h"
#include "yaHUD.h"
#include "yaPotion.h"
#include "yaPanel.h"
#include "yaItemSlot.h"
#include "yaInput.h"
namespace ya
{
	std::unordered_map<eUIType, UiBase*> UIManager::mUIs;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UiBase*> UIManager::mUIBases;
	UiBase* UIManager::mCurrentData = nullptr;

	void UIManager::Initialize()
	{
		// 여기에서 ui 메모리에 할당하면 된다.
		HUD* hud = new HUD(eUIType::HPMPBAR);
		mUIs.insert(std::make_pair(eUIType::HPMPBAR, hud));
		hud->SetPos(Vector2(700.0f, 830.0f));
		hud->ImageLoad(L"HPBAR", L"..\\Resources\\Image\\HpMpBar\\hpmpbar2.bmp");

		HUD* Hp = new HUD(eUIType::HP);
		mUIs.insert(std::make_pair(eUIType::HP, Hp));
		Hp->SetPos(Vector2(725.0f, 858.0f));
		Hp->ImageLoad(L"Hp", L"..\\Resources\\Image\\HpMpBar\\Hp.bmp");

		HUD* Mp = new HUD(eUIType::MP);
		mUIs.insert(std::make_pair(eUIType::MP, Mp));
		Mp->SetPos(Vector2(725.0f, 874.8f));
		//hud->SetSize(Vector2(200.0f, 200.0f));
		Mp->ImageLoad(L"Mp", L"..\\Resources\\Image\\HpMpBar\\Mp.bmp");

		HUD* BossHp = new HUD(eUIType::MONSTERHP);
		mUIs.insert(std::make_pair(eUIType::MONSTERHP, BossHp));
		BossHp->SetPos(Vector2(0.0f, 50.0f));
		BossHp->ImageLoad(L"BossHp", L"..\\Resources\\Image\\HpMpBar\\BossHp.bmp");

		Panel* Inventory = new Panel(eUIType::INVENTORY);
		mUIs.insert(std::make_pair(eUIType::INVENTORY, Inventory));
		Inventory->SetPos(Vector2(200.0f, 100.0f));
		Inventory->ImageLoad(L"Inventory", L"..\\Resources\\Image\\inventory.bmp");

		ItemSlot* itemslot = new ItemSlot(eUIType::ITEMSLOT);
		mUIs.insert(std::make_pair(eUIType::ITEMSLOT, itemslot));
		itemslot->SetPos(Vector2(920.0f, 825.0f));
		itemslot->ImageLoad(L"Itemslot", L"..\\Resources\\Image\\Itemslot\\Itemslot.bmp");

		Potion* RedPortion = new Potion(eUIType::REDPORTION);
		mUIs.insert(std::make_pair(eUIType::REDPORTION, RedPortion));
		//RedPortion->SetPos(Vector2(15.0f, 96.0f));
		RedPortion->ImageLoad(L"RedPortion", L"..\\Resources\\Image\\Portion\\RedPortion.bmp");
		RedPortion->mInventory = Inventory;
		RedPortion->mItemSlot = itemslot;

		Potion* BluePortion = new Potion(eUIType::BLUEPORTION);
		mUIs.insert(std::make_pair(eUIType::BLUEPORTION, BluePortion));
		//BluePortion->SetPos(Vector2(57.0f, 96.0f));
		BluePortion->ImageLoad(L"BluePortion", L"..\\Resources\\Image\\Portion\\BluePortion.bmp");
		BluePortion->mInventory = Inventory;
		BluePortion->mItemSlot = itemslot;
		//Inventory->AddChild(RedPortion);
		//Inventory->AddChild(BluePortion);

		itemslot->AddChild(RedPortion);
		itemslot->AddChild(BluePortion);
	}

	void UIManager::OnLoad(eUIType type)
	{
		std::unordered_map<eUIType, UiBase*>::iterator iter = mUIs.find(type);
		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
	}

	void UIManager::Tick()
	{
		std::stack<UiBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UiBase* uiBase = uiBases.top();
			if (uiBase != nullptr)
			{
				uiBase->Tick();
			}
			uiBases.pop();
		}

		if (mRequestUIQueue.size() > 0)
		{
			//UI 로드 해줘
			eUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();

			OnLoad(requestUI);
		}
	}


	void UIManager::Render(HDC hdc)
	{
		std::stack<UiBase*> uiBases = mUIBases;
		std::stack<UiBase*> tempStack;

		// 뒤집어서 렌더링을 해준다.
		while (!uiBases.empty())
		{
			UiBase* uiBase = uiBases.top();
			tempStack.push(uiBase);
			uiBases.pop();
		}

		while (!tempStack.empty())
		{
			UiBase* uiBase = tempStack.top();
			if (uiBase != nullptr)
			{
				uiBase->Render(hdc);
			}
			tempStack.pop();
		}
	}

	void UIManager::OnComplete(UiBase* addUI)
	{
		if (addUI == nullptr)
			return;

		addUI->Initialize();
		addUI->Active();
		addUI->Tick();

		if (addUI->GetIsFullScreen())
		{
			std::stack<UiBase*> uiBases = mUIBases;
			while (!uiBases.empty())
			{
				UiBase* uiBase = uiBases.top();
				uiBases.pop();

				if (uiBase->GetIsFullScreen())
				{
					uiBase->InActive();
				}
			}
		}

		mUIBases.push(addUI);
	}

	void UIManager::OnFail()
	{
		mCurrentData = nullptr;
	}

	void UIManager::Release()
	{
		for (auto ui : mUIs)
		{
			delete ui.second;
			ui.second = nullptr;
		}
	}

	void UIManager::Push(eUIType type)
	{
		mRequestUIQueue.push(type);
	}

	void UIManager::Pop(eUIType type)
	{
		if (mUIBases.size() <= 0)
			return;

		std::stack<UiBase*> tempStack;

		UiBase* uiBase = nullptr;
		while (mUIBases.size() > 0)
		{
			uiBase = mUIBases.top();
			mUIBases.pop();

			// pop하는 ui가 전체화면 일경우에,
			// 남은 ui중에 전체화면인 가장 상단의 ui 를 활성화 해주어야한다.
			if (uiBase->GetType() == type)
			{
				if (uiBase->GetIsFullScreen())
				{
					std::stack<UiBase*> uiBases = mUIBases;
					while (!uiBases.empty())
					{
						UiBase* uiBase = uiBases.top();
						uiBases.pop();

						if (uiBase->GetIsFullScreen())
						{
							uiBase->Active();
							break;
						}
					}
				}
				uiBase->InActive();
				uiBase->UIClear();
			}
			else
			{
				tempStack.push(uiBase);
			}
		}

		while (tempStack.size())
		{
			uiBase = tempStack.top();
			tempStack.pop();
			mUIBases.push(uiBase);
		}

	}

}