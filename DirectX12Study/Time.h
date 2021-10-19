#pragma once
#include "Singletons.h"

class Time : public Singletons
{
public:
	Time();
	~Time();

	virtual void Init() override;
	virtual void Update() override;
	virtual ULONG Release() override;

	float GetDeltaTime() { return _deltaTime; }
	void SetDeltaTime(float time) { _deltaTime = time; }
	void AddDeltaTime(float time) { _deltaTime = time; }

	ch::time_point<ch::high_resolution_clock> GetStartTime() { return _startTime; }
	void SetStartTime(ch::time_point<ch::high_resolution_clock> time) { _startTime = time; }

	ch::time_point<ch::high_resolution_clock> GetLastTime() { return _lastTime; }
	void SetLastTime(ch::time_point<ch::high_resolution_clock> time) { _lastTime = time; }

	float GetRunningTime() { return _runningTime; }

private:
	float _deltaTime;
	ch::time_point<ch::high_resolution_clock> _startTime;
	ch::time_point<ch::high_resolution_clock> _lastTime;
	float _runningTime;
};

