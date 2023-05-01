#pragma once
#include <memory>

class KeyboardManager;
class OS;
class Graphics;

class Engine {
public:
	Engine();
	static Engine &GetInstance();

	void Init(int width, int height, std::unique_ptr<OS> &&system);
	int Loop();
	int Frame();

	void Terminate() {
		m_running = false;
	}

	std::unique_ptr<Graphics> graphics;
	std::unique_ptr<OS> os;

private:
	std::unique_ptr<KeyboardManager> m_keyboardManager;
	static Engine m_instance;
	bool m_running = true;
};
