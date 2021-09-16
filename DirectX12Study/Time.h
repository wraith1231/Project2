#pragma once
class Time
{
public:
	Time();
	~Time();

	float GetDeltaTime() { return _deltaTime; }
	void SetDeltaTime(float time) { _deltaTime = time; }
	void AddDeltaTime(float time) { _deltaTime = time; }

	float GetStartTime() { return _startTime; }
	float SetStartTime(float time) { _startTime = time; }

	float GetLastTime() { return _lastTime; }
	void SetLastTime(float time) { _lastTime = time; }

private:
	float _deltaTime;
	float _startTime;
	float _lastTime;
};

