#include "stdafx.h"
#include "Time.h"

Time::Time()
{
	clock_t start = clock();
	_startTime = ch::high_resolution_clock::now();
	_deltaTime = 0;
	_lastTime = ch::high_resolution_clock::now();
}

Time::~Time()
{
}

void Time::Init()
{
}

void Time::Update()
{
	_lastTime = ch::high_resolution_clock::now();
	_runningTime = (float)ch::duration_cast<ch::milliseconds>(_lastTime - _startTime).count();
}

void Time::Delete()
{
}