#pragma once

#include <iostream>
#include <string>

namespace core {
	class Terminal
	{
	public:
		Terminal();
		Terminal(std::ostream& output, std::istream& input);

		void Send(const std::string& message);
		std::string Receive();
		std::string Ask(const std::string& question);
		void WaitForInput();
	private:
		std::ostream& m_OutputStream;
		std::istream& m_InputStream;
		
	};
}

