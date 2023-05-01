#pragma once
#include "Engine/Platform/OS.h"
#include "Engine/Util/EventSubscriber.h"
#include <bitset>
#include <limits>

constexpr uint32_t NUMKEYS = 300;

class KeyboardManager : EventSubscriber<OS::OsKeyBoardEvent> {
public:
	~KeyboardManager() override;
	KeyboardManager();
	KeyboardManager(const KeyboardManager &) = delete;
	KeyboardManager &operator=(const KeyboardManager &) = delete;
	KeyboardManager(KeyboardManager &&) = delete;
	KeyboardManager &operator=(KeyboardManager &&) = delete;
	void OnNotify(OS::OsKeyBoardEvent event) override;
	std::bitset<NUMKEYS> keyStates;
};
