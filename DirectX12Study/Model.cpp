#include "stdafx.h"
#include "Model.h"
#include "SceneManager.h"
#include "SingletonManager.h"
#include "RenderManager.h"
#include "D3D.h"
#include "Time.h"
#include "Input.h"
#include "Material.h"
#include "ModelNode.h"

Model::Model()
{
	Init();
}

Model::~Model()
{
	Release();
}

void Model::Init()
{
	_preWorldPosition = XMVectorZero();
	_worldPosition = XMVectorZero();
	_postWorldPosition = XMVectorZero();

	_scale = XMVectorZero();
	_rotate = XMVectorZero();
	_direction = XMVectorZero();

	_speed = 1.0f;
	_gameSpeed = Singleton<Time>()->GameSpeed();

	_coreNode = new ModelNode();
}

void Model::PreMove()
{
	_preWorldPosition = _worldPosition;
	_worldPosition = _postWorldPosition;

}

void Model::Update()
{
}

void Model::Render()
{
}

void Model::Release()
{
}
