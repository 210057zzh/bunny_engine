#include "KeyboardManager.h"

#include "Engine/Util/EventServer.h"

KeyboardManager::~KeyboardManager() {
	//EventServer<OS::OSKeyBoardEvent>::GetInstance().UnSubscribe(this);
}

KeyboardManager::KeyboardManager() {
	EventServer<OS::OsKeyBoardEvent>::GetInstance().Subscribe(this);
}

void KeyboardManager::OnNotify(const OS::OsKeyBoardEvent event) {
	switch (event.type) {
		case OS::OsKeyBoardEvent::Type::Keyup:
			keyStates[event.code] = false;
			break;
		case OS::OsKeyBoardEvent::Type::Keydown:
			keyStates[event.code] = true;
			break;
		case OS::OsKeyBoardEvent::Type::Invalid:
			break;
	}
}
