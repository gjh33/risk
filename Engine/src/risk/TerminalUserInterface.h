#pragma once

#include "IUserInterface.h"
#include "IPlayerDialogue.h"
#include "TerminalPlayerDialogue.h"

namespace risk {
	class TerminalUserInterface : public IUserInterface
	{
	public:
		TerminalUserInterface(std::shared_ptr<TerminalPlayerDialogue> terminalDialogue);
		virtual const std::shared_ptr<IPlayerDialogue> GetDefaultDialogue() override;
		virtual const std::shared_ptr<IPlayerDialogue> GetCardPlayDialogue() override;

	private:
		std::shared_ptr<TerminalPlayerDialogue> m_TerminalDialogue;
	};
}

