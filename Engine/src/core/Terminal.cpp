#include "Terminal.h"

namespace core {
	Terminal::Terminal() :
		m_OutputStream(std::cout),
		m_InputStream(std::cin)
	{
	}

	Terminal::Terminal(std::ostream& output, std::istream& input) :
		m_OutputStream(output),
		m_InputStream(input)
	{
	}

	void Terminal::Send(const std::string& message)
	{
		m_OutputStream << message << std::endl;
	}

	std::string Terminal::Receive()
	{
		std::string message;
		std::getline(m_InputStream, message);
		return message;
	}

	std::string Terminal::Ask(const std::string& prompt)
	{
		m_OutputStream << prompt;
		return Receive();
	}

	void Terminal::WaitForInput()
	{
		m_InputStream.get();
	}
}
