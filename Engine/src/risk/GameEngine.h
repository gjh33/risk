#pragma once

#include <memory>

#include "IUserInterface.h"
#include "Game.h"
#include "BaseGameState.h"
#include "states/WelcomeState.h"

namespace risk {
	class GameEngine
	{
	public:
		enum State
		{
			Uninitialized,
			Initialized,
			GameLoaded,
			GameRunning,
			GameFinished
		};

	public:
		GameEngine(std::shared_ptr<IUserInterface> ui);
		State GetState() const;
		void LoadGame(std::shared_ptr<Game> game);
		void Run();

	private:
		State m_RunningState;
		std::shared_ptr<Game> m_Game;
		std::shared_ptr<IUserInterface> m_UserInterface;
		std::shared_ptr<BaseGameState> m_CurrentGameState;

		void BuildStateMachine();
	};
}

