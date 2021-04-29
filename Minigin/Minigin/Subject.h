#pragma once
#include <vector>
#include <memory>
#include "Observer.h"

class Component;

class Subject
{
public:
	void AddObserver(std::weak_ptr<Observer> observer);
	void RemoveObserver(std::weak_ptr<Observer> observer);
	void Notify(std::shared_ptr<Component> pComp, Event event);

private:
	std::vector<std::weak_ptr<Observer>> m_Observers{};	
};

