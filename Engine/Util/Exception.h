#pragma once
#include <exception>
#include <string>

class Exception : public std::exception {
public:
	Exception(int throwingLine, const char *throwingFile);
	~Exception() noexcept override;
	const char *what() const override;
	virtual const char *GetType() const noexcept;
	int GetThrowingLine() const noexcept;
	const std::string &GetThrowingFile() const noexcept;
	std::string GetThrowLocationString() const noexcept;

private:
	int m_throwing_line_ = -1;
	std::string m_throwing_file_;

protected:
	mutable std::string whatBuffer;
};
