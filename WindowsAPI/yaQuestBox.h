#pragma once
#include "yaGameObject.h"

namespace ya
{
	class QuestBox : public GameObject
	{
		QuestBox();
		virtual ~QuestBox();	
	
		virtual void Enter();
		virtual void Exit();
		virtual void Tick();
		virtual void Render();
	};
}