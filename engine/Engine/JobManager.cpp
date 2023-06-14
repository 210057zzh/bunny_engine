#include "stdafx.h"
#include "JobManager.h"
#include "Job.h"
#include "Worker.h"

JobManager JobManager::s_manager_;

JobManager::JobManager()
{
	Begin();
}

JobManager::~JobManager()
{
	End();
}

void JobManager::Begin()
{
	running = true;
	const unsigned int processor_count = std::thread::hardware_concurrency();
	workers.resize(processor_count);
	for (auto& worker : workers)
	{
		worker = std::make_unique<Worker>();
	}
	for (const auto& worker : workers)
	{
		worker->Begin();
	}
}

void JobManager::End()
{
	WaitForJobs();
	{
		std::lock_guard<std::mutex> l(queue_mutex);
		running = false;
	}
	task_available.notify_all();
	for (const auto& worker : workers)
	{
		worker->End();
	}
}

void JobManager::AddJob(std::unique_ptr<Job>&& pJob)
{
	{
		std::lock_guard<std::mutex> l(queue_mutex);
		jobs.push_back(std::move(pJob));
		++tasks_total;
	}
	task_available.notify_one();
}

void JobManager::WaitForJobs()
{
	waiting = true;
	std::unique_lock<std::mutex> lock(queue_mutex);
	task_done.wait(lock, [this]() {return tasks_total == 0; });
	waiting = false;
}
