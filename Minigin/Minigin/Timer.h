#pragma once
#include <chrono>
#include "Singleton.h"

namespace dae
{
	class Timer final : public Singleton<Timer>
	{
	public:
		~Timer() = default;

		void Start();
		void Update();
		double GetDeltaTime() const;
		double GetFixedDeltaTime() const;
		std::chrono::steady_clock::time_point GetLastTime() const;


	protected:
		friend class Singleton<Timer>;
		Timer() = default;

		std::chrono::duration<double> m_DeltaTime{ 0 };
		std::chrono::duration<double> m_FixedDeltaTime{ 0.02 };

		//internal vars
		std::chrono::steady_clock::time_point m_LastTime{};
		std::chrono::duration<double> m_SecondsPerFrame{};
	};
}