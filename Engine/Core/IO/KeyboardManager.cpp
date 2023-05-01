#include "KeyboardManager.h"

#include "Engine/Util/EventServer.h"

KeyboardManager::~KeyboardManager()
{
	//EventServer<OS::OSKeyBoardEvent>::GetInstance().UnSubscribe(this);
}

KeyboardManager::KeyboardManager()
{
	EventServer<OS::OSKeyBoardEvent>::GetInstance().Subscribe(this);
}

void KeyboardManager::OnNotify(OS::OSKeyBoardEvent event)
{
	switch (event.type)
	{
	case OS::OSKeyBoardEvent::Type::KEYUP:
		key_states[event.code] = false;
	case OS::OSKeyBoardEvent::Type::KEYDOWN:
		key_states[event.code] = true;
	default: break;
	}
}
