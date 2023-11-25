#pragma once

#include <memory>

#include "Game.h"

namespace risk {
	class BaseGameState
	{
	public:
		BaseGameState();
		std::shared_ptr<BaseGameState> Run(Game& game);
		bool IsActive();

	protected:
		virtual std::shared_ptr<BaseGameState> OnRun(Game& game) = 0;

	private:
		bool m_IsActive;
	};
}

