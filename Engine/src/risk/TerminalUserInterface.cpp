#include "TerminalUserInterface.h"

namespace risk {
	TerminalUserInterface::TerminalUserInterface(std::shared_ptr<TerminalPlayerDialogue> terminalDialogue) :
		m_TerminalDialogue(terminalDialogue)
	{
	}

	const std::shared_ptr<IPlayerDialogue> TerminalUserInterface::GetDefaultDialogue()
	{
		return m_TerminalDialogue;
	}

	const std::shared_ptr<IPlayerDialogue> TerminalUserInterface::GetCardPlayDialogue()
	{
		return m_TerminalDialogue;
	}
}