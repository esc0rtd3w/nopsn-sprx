#pragma once


//Timer
class Timer
{
public:
	void Start();
	void Restart();
	system_time_t GetDifference();
private:
	system_time_t StartTime;
	bool Started;
	system_time_t Difference;
};

void Timer::Start()
{
	if (!Timer::Started)
	{
		Timer::StartTime = sys_time_get_system_time() / 1000;
		Started = true;
	}
}

void Timer::Restart()
{
	Timer::StartTime = sys_time_get_system_time() / 1000;
	Started = true;
}

system_time_t Timer::GetDifference()
{
	system_time_t CurrentTime = sys_time_get_system_time() / 1000;
	float LastTime = StartTime;
	Timer::Difference = CurrentTime - StartTime;
	return Timer::Difference;
}



// Timer Control For Menu
bool newTimerTick = true;
int maxTimerCount;
void AppTimer(int tickTime) 
{
	if (newTimerTick)
	{
		maxTimerCount = sys_time_get_system_time() / 1000 + tickTime;
		newTimerTick = false;
	}
}

bool isTimerReady() 
{
	return sys_time_get_system_time() / 1000 > maxTimerCount;
}

void ResetGameTimer()
{
	newTimerTick = true;
}


