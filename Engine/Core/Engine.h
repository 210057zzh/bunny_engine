#pragma once
#include <memory>

class OS;
class Window;

class Engine
{
public:
	Engine(int width, int height);
	const static Engine& GetInstance();
	std::unique_ptr<Window> window;
	std::unique_ptr<OS> os;

private:
	static Engine s_instance_;
};

