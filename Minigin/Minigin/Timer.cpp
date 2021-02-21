#include "MiniginPCH.h"
#include "Timer.h"

Timer* pTimer = nullptr;

Timer::Timer(double fixedDeltaTime)
	:m_FixedDeltaTime{fixedDeltaTime}
{
}

void Timer::Start()
{
	m_LastTime = std::chrono::high_resolution_clock::now();
}

void Timer::Update()
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - m_LastTime);
	m_LastTime = currentTime;
}

double Timer::GetDeltaTime() const
{
	return m_DeltaTime.count();
}

double Timer::GetFixedDeltaTime() const
{
	return m_FixedDeltaTime.count();
}

std::chrono::steady_clock::time_point Timer::GetLastTime() const
{
	return m_LastTime;
}
