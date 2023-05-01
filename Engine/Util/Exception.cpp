#include "Exception.h"
#include <sstream>

Exception::Exception(const int throwingLine, const char *throwingFile) :
		m_throwing_line_(throwingLine),
		m_throwing_file_(throwingFile) {
}

Exception::~Exception() noexcept = default;

const char *Exception::what() const {
	std::ostringstream oss;
	oss << GetType() << '\n'
		<< GetThrowLocationString() << '\n';
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char *Exception::GetType() const noexcept {
	return "Exception";
}

int Exception::GetThrowingLine() const noexcept {
	return m_throwing_line_;
}

const std::string &Exception::GetThrowingFile() const noexcept {
	return m_throwing_file_;
}

std::string Exception::GetThrowLocationString() const noexcept {
	std::ostringstream oss;
	oss << GetThrowingFile() << ':' << GetThrowingLine();
	return oss.str();
}
