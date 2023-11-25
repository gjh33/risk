#include "Player.h"

namespace risk {
	Player::Player(std::string name) :
		m_Name(name)
	{
	}

	std::string Player::GetName() const
	{
		return m_Name;
	}
}
