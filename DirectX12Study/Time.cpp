#include "stdafx.h"
#include "Time.h"

Time::Time()
{
	clock_t start = clock();
	_startTime = start;
	_deltaTime = 0;
	_lastTime = start;
}

Time::~Time()
{
}
