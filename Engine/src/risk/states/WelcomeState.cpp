#include "WelcomeState.h"

namespace risk {
	const std::string WelcomeState::WelcomeMenuMessage = 
		"Welcome to Ri... I mean Conquest!\n"
		"What would you like to do?\n"
		"1. Play a game\n"
		"2. Exit\n";
	
	WelcomeState::WelcomeState(std::shared_ptr<IPlayerDialogue> dialogue) :
		m_Dialogue(dialogue)
	{
	}

	void WelcomeState::SetNextState(std::shared_ptr<BaseGameState> nextState)
	{
		m_NextState = nextState;
	}

	std::shared_ptr<BaseGameState> WelcomeState::OnRun(Game& game)
	{
		int menuChoice = m_Dialogue->AskInt(WelcomeMenuMessage);
		while (menuChoice <= 0 || menuChoice > 2) {
			menuChoice = m_Dialogue->AskInt("Please enter a valid choice...");
		}

		if (menuChoice == 1) {
			return m_NextState;
		}

		return nullptr;
	}
}
