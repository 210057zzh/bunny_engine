#pragma once
#include <memory>

class KeyboardManager;
class OS;
class Graphics;

class Engine
{
public:
	Engine();
	static Engine& GetInstance();

	void Init(int width, int height, std::unique_ptr<OS>&& system);
	int Loop();
	int Frame();
	void Terminate()
	{
		m_running_ = false;
	}

	std::unique_ptr<Graphics> graphics;
	std::unique_ptr<OS> os;

private:
	std::unique_ptr<KeyboardManager> keyboard_manager_;
	static Engine s_instance_;
	bool m_running_ = true;
};

