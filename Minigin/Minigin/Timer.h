#pragma once
#include <chrono>
#include "Singleton.h"

class Timer final : dae::Singleton<Timer>
{
public:
	Timer(double fixedDeltaTime);
	~Timer() = default;
	Timer(const Timer& other) = delete;
	Timer(Timer&& other) = delete;
	Timer& operator=(const Timer& other) = delete;
	Timer& operator=(Timer&& other) = delete;

	void Start();
	void Update();
	double GetDeltaTime() const;
	double GetFixedDeltaTime() const;
	std::chrono::steady_clock::time_point GetLastTime() const;
private:
	friend class Singleton<Timer>;
	Timer() = default;

	std::chrono::duration<double> m_DeltaTime{0};
	std::chrono::duration<double> m_FixedDeltaTime{ 0.02 };

	//internal vars
	std::chrono::steady_clock::time_point m_LastTime{};
	std::chrono::duration<double> m_SecondsPerFrame{};
};

//a global timer so that we dont need to pass it through all the update functions
extern Timer* pTimer;