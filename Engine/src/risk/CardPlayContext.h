#pragma once

#include <memory>

#include "Player.h"
#include "CommandExecutionContext.h"
#include "IPlayerDialogue.h"

namespace risk {
	struct CardPlayContext 
	{
		Player& ExecutingPlayer;
		IPlayerDialogue& Dialogue;
	};
}
