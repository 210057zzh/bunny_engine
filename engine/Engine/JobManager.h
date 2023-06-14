#pragma once

#include <deque>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <mutex>

class Job;
class Worker;

struct Condition
{
	std::condition_variable cond;
	std::mutex lock;
};

class JobManager
{
public:
	JobManager();
	~JobManager();

	static JobManager& Get() { return s_manager_; }

	void Begin();
	void End();
	void AddJob(std::unique_ptr<Job>&& pJob);
	void WaitForJobs();

	std::condition_variable task_available;
	std::condition_variable task_done;
	std::mutex queue_mutex;

	std::vector<std::unique_ptr<Worker>> workers{};
	std::atomic<bool> running{ true };
	std::atomic<bool> waiting{ false };
	std::atomic<int> tasks_total{ 0 };
	std::deque<std::unique_ptr<Job>> jobs;

private:
	static JobManager s_manager_;
};
