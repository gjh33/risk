#pragma once

#include <memory>

#include "risk/BaseGameState.h"
#include "risk/Game.h"

namespace risk
{
	class WelcomeState : public BaseGameState
	{
	public:
		WelcomeState(std::shared_ptr<IPlayerDialogue> dialogue);
		void SetNextState(std::shared_ptr<BaseGameState> nextState);
		std::shared_ptr<BaseGameState> OnRun(Game& game) override;
	private:
		static const std::string WelcomeMenuMessage;
		
		std::shared_ptr<IPlayerDialogue> m_Dialogue;
		std::shared_ptr<BaseGameState> m_NextState;
	};
}

