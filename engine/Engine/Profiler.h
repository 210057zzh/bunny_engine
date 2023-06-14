#pragma once

#include "jsonUtil.h"

class Profiler
{
public:
	class Timer
	{
	public:
		friend class Profiler;
		void Start();
		void Stop();
		void Reset();
		const std::string& GetName() const;
		double GetTime_ms() const;
		double GetMax_ms() const;
		double GetAvg_ms() const;

	private:
		Timer(std::string name);
		~Timer();

		std::string mName;
		double mThisFrameTime{};
		double mLongestFrameTime{};
		double mTotalTime{};
		int mNumFrames{};
		std::chrono::high_resolution_clock::time_point mStart;
	};

	class ScopedTimer
	{
	public:
		ScopedTimer(Timer* timer);
		~ScopedTimer();
	private:
		Timer* mTimer;
	};

	static Profiler* Get();

	void BeginTimer(const std::string& name,
		uint64_t startTime);

	void EndTimer(uint64_t endTime);

	Timer* GetTimer(const std::string& name);

	void ResetAll();

	friend class Timer;

private:
	rapidjson::Document mJson{ rapidjson::Type::kArrayType };
	static Profiler s_profiler_;
	std::unordered_map<std::string, Timer*> mTimerMap;
	Profiler();
	~Profiler();
};

#define PROFILE_SCOPE(name) \
Profiler::ScopedTimer name##_scope(Profiler::Get()->GetTimer(std::string(#name)))
