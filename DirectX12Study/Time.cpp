#include "stdafx.h"
#include "Time.h"

Time::Time()
{
	Init();
}

Time::~Time()
{
	Release();
}

void Time::Init()
{
	clock_t start = clock();
	_startTime = ch::high_resolution_clock::now();
	_deltaTime = 0;
	_lastTime = ch::high_resolution_clock::now();
}

void Time::Update()
{
	_lastTime = ch::high_resolution_clock::now();
	_runningTime = (float)ch::duration_cast<ch::milliseconds>(_lastTime - _startTime).count() * 0.001f;


}

ULONG Time::Release()
{
	return 0;
}
