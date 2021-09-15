#include "stdafx.h"
#include "SingletonManager.h"
#include "Window.h"

SingletonManager::SingletonManager()
{
}

SingletonManager::~SingletonManager()
{
}

void SingletonManager::Init()
{
}

SingletonManager* SingletonManager::Singleton()
{
	if (h_instance == nullptr)
	{
		h_instance = new SingletonManager();

		h_instance->_window = new Window();
	}

	return h_instance;
}

Window* SingletonManager::GetWindow()
{
	return _window;
}
