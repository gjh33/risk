#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "IPlayerDialogue.h"
#include "core/Terminal.h"

namespace risk {
	class TerminalPlayerDialogue : public IPlayerDialogue
	{
	public:
		TerminalPlayerDialogue(const core::Terminal& terminal);
		std::string AskString(const std::string& question) override;
		bool AskBool(const std::string& question) override;
		int AskInt(const std::string& question) override;
		float AskFloat(const std::string& question) override;
	private:
		static const std::vector<std::string> s_TrueStrings;
		static const std::vector<std::string> s_FalseStrings;
		core::Terminal m_Terminal;

		bool IsTrue(const std::string& input);
		bool IsFalse(const std::string& input);
	};
}

