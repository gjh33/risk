#include "BaseGameState.h"

namespace risk {
	BaseGameState::BaseGameState() :
		m_IsActive(false)
	{
	}

	std::shared_ptr<BaseGameState> BaseGameState::Run(Game& game)
	{
		m_IsActive = true;
		std::shared_ptr<BaseGameState> result = OnRun(game);
		m_IsActive = false;
		return result;
	}

	bool BaseGameState::IsActive()
	{
		return false;
	}
}
