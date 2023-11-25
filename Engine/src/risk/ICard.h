#pragma once

#include <string>

#include "CardPlayContext.h"

namespace risk {
	class ICard
	{
	public:
		virtual bool Play(const CardPlayContext& context) const = 0;
		virtual std::string GetName() const = 0;
		virtual std::string GetDescription() const = 0;

	protected:
		virtual bool Validate(const CardPlayContext& context) const = 0;
	};
}

