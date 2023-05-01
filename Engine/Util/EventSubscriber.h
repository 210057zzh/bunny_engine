#pragma once

template <typename Event>
class EventSubscriber {
public:
	virtual ~EventSubscriber() = default;
	virtual void OnNotify(Event event) = 0;
};
