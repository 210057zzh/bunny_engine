#include "stdafx.h"
#include "Profiler.h"

#include <thread>

#include "jsonUtil.h"

/*static*/
Profiler Profiler::s_profiler_;

void Profiler::Timer::Start()
{
	mStart = std::chrono::high_resolution_clock::now();
	auto time = mStart.time_since_epoch().count() / 1000;
	Get()->BeginTimer(mName, time);
}

void Profiler::Timer::Stop()
{
	const auto end = std::chrono::high_resolution_clock::now();
	const auto duration = std::chrono::duration<double, std::milli>(end - mStart).count();
	mThisFrameTime += duration;

	auto time = end.time_since_epoch().count() / 1000;
	Get()->EndTimer(time);
}

void Profiler::Timer::Reset()
{
	mTotalTime += mThisFrameTime;
	mNumFrames++;
	mLongestFrameTime = std::max(mLongestFrameTime, mThisFrameTime);
	mThisFrameTime = 0.0;
}

const std::string& Profiler::Timer::GetName() const
{
	return mName;
}

double Profiler::Timer::GetTime_ms() const
{
	return mThisFrameTime;
}

double Profiler::Timer::GetMax_ms() const
{
	return mLongestFrameTime;
}

double Profiler::Timer::GetAvg_ms() const
{
	return mTotalTime / static_cast<double>(mNumFrames);
}

Profiler::Timer::Timer(std::string name) : mName(std::move(name))
{
}

Profiler::Timer::~Timer()
{
}

Profiler::ScopedTimer::ScopedTimer(Timer* timer) : mTimer(timer)
{
	mTimer->Start();
}

Profiler::ScopedTimer::~ScopedTimer()
{
	mTimer->Stop();
}

Profiler* Profiler::Get()
{
	return &s_profiler_;
}

void Profiler::BeginTimer(const std::string& name, uint64_t startTime)
{
	using rapidjson::Value;
	rapidjson::Document::AllocatorType& allocator = mJson.GetAllocator();
	Value beginEvent;
	beginEvent.SetObject();
	beginEvent.AddMember("name", Value().SetString(name, allocator), allocator);
	beginEvent.AddMember("ph", Value().SetString("B", allocator), allocator);
	beginEvent.AddMember("ts", Value().SetUint64(startTime), allocator);
	beginEvent.AddMember("tid", Value().SetUint64(
		std::hash<std::thread::id>{}(std::this_thread::get_id())), allocator);
	beginEvent.AddMember("pid", Value().SetUint64(1), allocator);
	mJson.PushBack(beginEvent, allocator);
}

void Profiler::EndTimer(uint64_t endTime)
{
	using rapidjson::Value;
	rapidjson::Document::AllocatorType& allocator = mJson.GetAllocator();
	Value endEvent;
	endEvent.SetObject();
	endEvent.AddMember("ph", Value().SetString("E", allocator), allocator);
	endEvent.AddMember("ts", Value().SetUint64(endTime), allocator);
	endEvent.AddMember("tid", Value().SetUint64(
		std::hash<std::thread::id>{}(std::this_thread::get_id())), allocator);
	endEvent.AddMember("pid", Value().SetUint64(1), allocator);
	mJson.PushBack(endEvent, allocator);
}

Profiler::Timer* Profiler::GetTimer(const std::string& name)
{
	auto itr = mTimerMap.find(name);
	if (itr == mTimerMap.end())
	{
		itr = mTimerMap.insert({ name, new Timer(name) }).first;
	}
	return itr->second;
}

void Profiler::ResetAll()
{
	for (const auto& v : mTimerMap)
	{
		v.second->Reset();
	}
}

Profiler::Profiler()
{
}

Profiler::~Profiler()
{
	{
		FILE* file;
		fopen_s(&file, "profile.txt", "w");
		fprintf_s(file, "name:, avg(ms), max(ms)\n");

		for (const auto& v : mTimerMap)
		{
			const auto& timer = v.second;
			fprintf_s(file, "%s:, %f, %f\n", timer->GetName().c_str(), timer->GetAvg_ms(), timer->GetMax_ms());
		}

		fclose(file);
	}

	{
		FILE* file;
		fopen_s(&file, "profile.json", "w");
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		mJson.Accept(writer);
		fputs(buffer.GetString(), file);
		fclose(file);
	}
}
