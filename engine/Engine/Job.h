#pragma once

class Job
{
public:
	virtual ~Job() = default;
	virtual void DoIt()
	{
		for (int i = 0; i < 100; i++)
		{
			int j = i * i + 200;
		}
	}
};
