#include "Subject.h"
#include "Observer.h"

void Subject::AddObserver(std::weak_ptr<Observer> observer)
{
	m_Observers.push_back(observer);
}

void Subject::RemoveObserver(std::weak_ptr<Observer> observer)
{
	m_Observers.erase(std::remove_if(m_Observers.begin(), m_Observers.end(), [observer](const std::weak_ptr<Observer>& obs) 
		{
			if (obs.lock() == observer.lock())
				return true;
			return false;
		}), m_Observers.end());
}

void Subject::Notify(std::shared_ptr<Component> pComp, Event event)
{
	for (std::weak_ptr<Observer> observer : m_Observers)
	{
		observer.lock()->Notify(pComp, event);
	}
}
