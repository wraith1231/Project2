#include "stdafx.h"
#include "SingletonManager.h"
#include "Singletons.h"
#include "Window.h"
#include "Time.h"
#include "Input.h"

SingletonManager::SingletonManager()
{
}

SingletonManager::~SingletonManager()
{
}

void SingletonManager::Init()
{

}

void SingletonManager::Update()
{
	map<string, Singletons*>::iterator iter = _Singletons.begin();
	for (; iter != _Singletons.end(); ++iter)
	{
		iter->second->Update();
	}
}

void SingletonManager::Delete()
{
	map<string, Singletons*>::iterator iter = _Singletons.begin();
	for (; iter != _Singletons.end(); ++iter)
	{
		iter->second->Delete();
	}
}

void SingletonManager::AddSingleton(string name, Singletons* sin)
{
	if (sin == nullptr)
		return;

	_Singletons[name] = sin;
}

Singletons* SingletonManager::GetSingleton(string name)
{
	return _Singletons[name];
}

SingletonManager* SingletonManager::Singleton()
{
	if (h_instance == nullptr)
	{
		h_instance = new SingletonManager();

		h_instance->AddSingleton("Window", new Window());
		h_instance->AddSingleton("Time", new Time());
		h_instance->AddSingleton("Input", new Input());
	}

	return h_instance;
}