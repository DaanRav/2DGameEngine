#include "MiniginPCH.h"
#include "Timer.h"

void dae::Timer::Start()
{
	m_LastTime = std::chrono::high_resolution_clock::now();
}

void dae::Timer::Update()
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - m_LastTime);
	m_LastTime = currentTime;
}

double dae::Timer::GetDeltaTime() const
{
	return m_DeltaTime.count();
}

double dae::Timer::GetFixedDeltaTime() const
{
	return m_FixedDeltaTime.count();
}

std::chrono::steady_clock::time_point dae::Timer::GetLastTime() const
{
	return m_LastTime;
}

