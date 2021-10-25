#include "stdafx.h"
#include "SceneManager.h"
#include "SingletonManager.h"
#include "RenderManager.h"
#include "Time.h"
#include "PostProcess.h"
#include "Input.h"
#include "D3D.h"
#include "Window.h"
#include "Camera.h"
#include "TestModel.h"

SceneManager::SceneManager()
{
	Init();
}

SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::Init()
{
	_renderManager = new RenderManager();
	_camera = new Camera();
	_gameSpeed = Singleton<Time>()->GameSpeed();
}

ULONG SceneManager::Release()
{
	_renderManager->Release();
	_camera->Release();

	return 0;
}

void SceneManager::Update()
{
}

void SceneManager::Render()
{
}

void SceneManager::Resize(UINT width, UINT height)
{
	_renderManager->Resize(width, height);
}

SceneManager* SceneManager::Scene()
{
	if (h_sInstance == nullptr)
	{
		h_sInstance = new SceneManager();
	}

	return h_sInstance;
}
