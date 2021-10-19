#include "stdafx.h"
#include "RenderManager.h"
#include "SingletonManager.h"
#include "Window.h"
#include "Time.h"
#include "PostProcess.h"

RenderManager::RenderManager()
{
	Init();
}

RenderManager::~RenderManager()
{
	Release();
}

void RenderManager::Init()
{
}

void RenderManager::Update()
{
}

ULONG RenderManager::Release()
{
	return 0;
}

void RenderManager::AddPostProcess(string name)
{
	if (_postProcesses[name] != nullptr)
		return;


}

void RenderManager::DeletePostProcess(string name)
{
	if (_postProcesses[name] != nullptr)
	{
		_postProcesses[name]->Release();
		_postProcesses.erase(name);
	}
}

void RenderManager::DeleteAllPostProcess()
{
	for (auto pp : _postProcesses)
	{
		pp.second->Release();
	}
	_postProcesses.clear();
}

void RenderManager::Resize(UINT width, UINT height)
{
}
