#pragma once

#include <memory>
#include <unordered_set>
#include "EventSubscriber.h"

template<typename Event>
class EventServer
{
public:
	static EventServer& GetInstance()
	{
		if (s_instance_ == nullptr)
		{
			s_instance_ = std::make_unique<EventServer>();
		}
		return *s_instance_;
	}

	void Subscribe(EventSubscriber<Event>* subscriber)
	{
		s_subscribers.insert(subscriber);
	}

	void UnSubscribe(EventSubscriber<Event>* subscriber)
	{
		auto itr = s_subscribers.find(subscriber);
		if (itr != s_subscribers.end())
		{
			s_subscribers.erase(itr);
		}
	}

	void Notify(Event&& event);

private:
	static std::unique_ptr<EventServer> s_instance_;
	std::unordered_set<EventSubscriber<Event>*> s_subscribers;
};

template <typename Event>
std::unique_ptr<EventServer<Event>> EventServer<Event>::s_instance_;

template <typename Event>
void EventServer<Event>::Notify(Event&& event)
{
	for (auto s : s_subscribers)
	{
		s->OnNotify(event);
	}
}
