#include "GameEngine.h"

namespace risk {
	GameEngine::GameEngine(std::shared_ptr<IUserInterface> ui) :
		m_RunningState(GameEngine::State::Uninitialized),
		m_UserInterface(ui)
	{
		BuildStateMachine();
		m_RunningState = GameEngine::State::Initialized;
	}

	GameEngine::State GameEngine::GetState() const
	{
		return m_RunningState;
	}

	void GameEngine::LoadGame(std::shared_ptr<Game> game)
	{
		m_Game = game;
		m_RunningState = GameEngine::State::GameLoaded;
	}

	void GameEngine::Run() {
		while (m_CurrentGameState != nullptr) {
			m_CurrentGameState = m_CurrentGameState->Run(*m_Game);
		}
	}
	
	void GameEngine::BuildStateMachine() {
		std::shared_ptr<WelcomeState> welcomeState = std::make_shared<WelcomeState>(m_UserInterface->GetDefaultDialogue());

		m_CurrentGameState = welcomeState;
	}
}
