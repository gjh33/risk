#include "TerminalPlayerDialogue.h"

namespace risk {
	const std::vector<std::string> TerminalPlayerDialogue::s_TrueStrings = {
		"y",
		"yes",
		"true",
		"1",
	};

	const std::vector<std::string> TerminalPlayerDialogue::s_FalseStrings = {
		"n",
		"no",
		"false",
		"0",
	};
	
	TerminalPlayerDialogue::TerminalPlayerDialogue(const core::Terminal& terminal) :
		m_Terminal(terminal)
	{
	}

	std::string TerminalPlayerDialogue::AskString(const std::string& question)
	{
		return m_Terminal.Ask(question);
	}

	bool TerminalPlayerDialogue::AskBool(const std::string& question)
	{
		m_Terminal.Send(question);
		
		std::string answer;
		while (!IsTrue(answer) && !IsFalse(answer))
		{
			answer = m_Terminal.Ask("Please answer with yes or no: ");
		}
		return IsTrue(answer);
	}

	int TerminalPlayerDialogue::AskInt(const std::string& question) {
		m_Terminal.Send(question);

		std::string answer;
		bool isValid = false;
		int result = 0;
		while (!isValid) {
			answer = m_Terminal.Ask("Please answer with a whole number: ");
			try {
				result = std::stoi(answer);
				isValid = true;
			}
			catch (...) {
				isValid = false;
			}
		}
		return result;
	}

	float TerminalPlayerDialogue::AskFloat(const std::string& question) {
		m_Terminal.Send(question);

		std::string answer;
		bool isValid = false;
		float result = 0;
		while (!isValid) {
			answer = m_Terminal.Ask("Please answer with a number: ");
			try {
				result = std::stof(answer);
				isValid = true;
			}
			catch (...) {
				isValid = false;
			}
		}
		return result;
	}

	bool TerminalPlayerDialogue::IsTrue(const std::string& answer)
	{
		for (const std::string& trueString : s_TrueStrings)
		{
			if (answer == trueString)
			{
				return true;
			}
		}
		return false;
	}

	bool TerminalPlayerDialogue::IsFalse(const std::string& answer)
	{
		for (const std::string& falseString : s_FalseStrings)
		{
			if (answer == falseString)
			{
				return true;
			}
		}
		return false;
	}
}
