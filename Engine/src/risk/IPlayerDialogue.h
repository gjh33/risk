#pragma once

#include <string>

namespace risk {
	class IPlayerDialogue
	{
	public:
		virtual std::string AskString(const std::string& question) = 0;
		virtual bool AskBool(const std::string& question) = 0;
		virtual int AskInt(const std::string& question) = 0;
		virtual float AskFloat(const std::string& question) = 0;
	};
}
