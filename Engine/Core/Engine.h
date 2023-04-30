#pragma once
#include <memory>

class OS;
class Graphics;

class Engine
{
public:
	Engine();
	static Engine& GetInstance();

	void Init(int width, int height, std::unique_ptr<OS>&& system);
	int Loop();

	std::unique_ptr<Graphics> graphics;
	std::unique_ptr<OS> os;

private:
	static Engine s_instance_;
};

