#include "stdafx.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "Time.h"
#include "PostProcess.h"
#include "Input.h"
#include "D3D.h"
#include "Window.h"

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
}

ULONG SceneManager::Release()
{

	return 0;
}

void SceneManager::Update()
{
}

void SceneManager::Render()
{
}
