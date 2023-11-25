#pragma once

#include <memory>

#include "IPlayerDialogue.h"

namespace risk {
	class IUserInterface
	{
	public:
		virtual const std::shared_ptr<IPlayerDialogue> GetDefaultDialogue() = 0;
		virtual const std::shared_ptr<IPlayerDialogue> GetCardPlayDialogue() = 0;
	};
}
