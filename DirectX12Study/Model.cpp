#include "stdafx.h"
#include "Model.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "D3D.h"
#include "Time.h"
#include "Input.h"

Model::Model()
{
	_preWorldPosition = XMVectorZero();
	_worldPosition = XMVectorZero();
	_postWorldPosition = XMVectorZero();

	_scale = XMVectorZero();
	_rotate = XMVectorZero();
	_direction = XMVectorZero();
}

Model::~Model()
{
}
