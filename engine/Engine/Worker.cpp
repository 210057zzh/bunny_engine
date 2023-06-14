#include "stdafx.h"
#include "Worker.h"

#include "Job.h"
#include "JobManager.h"

void Worker::Begin()
{
	mThread = std::thread{ Loop };
}

void Worker::End()
{
	if (mThread.joinable())
		mThread.join();
}

void Worker::Loop()
{
	auto& manager = JobManager::Get();
	while (manager.running)
	{
		std::unique_lock<std::mutex> lock(manager.queue_mutex);
		manager.task_available.wait(lock, [&manager]()
			{
				return !manager.jobs.empty() || !manager.running;
			});
		if (manager.running)
		{
			auto job = std::move(manager.jobs.front());
			manager.jobs.pop_front();
			lock.unlock();
			job->DoIt();
			lock.lock();
			--manager.tasks_total;
			lock.unlock();
			if (manager.waiting)
			{
				manager.task_done.notify_one();
			}
		}
	}
}
