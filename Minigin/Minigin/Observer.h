#pragma once
#include <memory>

class Component;

enum class Event
{
	TestEvent
};

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Notify(std::shared_ptr<Component>, Event event) = 0;
};


