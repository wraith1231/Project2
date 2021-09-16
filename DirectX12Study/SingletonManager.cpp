#include "stdafx.h"
#include "SingletonManager.h"
#include "Window.h"
#include "Time.h"

SingletonManager::SingletonManager()
{
	_time = nullptr;
	_window = nullptr;
}

SingletonManager::~SingletonManager()
{
}

SingletonManager* SingletonManager::Singleton()
{
	if (h_instance == nullptr)
	{
		h_instance = new SingletonManager();

		h_instance->_window = new Window();
		h_instance->_time = new Time();
	}

	return h_instance;
}

Window* SingletonManager::GetWindow()
{
	return _window;
}

Time* SingletonManager::GetTime()
{
	return _time;
}
