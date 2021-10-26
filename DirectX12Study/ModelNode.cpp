#include "stdafx.h"
#include "ModelNode.h"
#include "Material.h"

ModelNode::ModelNode()
{
	Init();
}

ModelNode::~ModelNode()
{
	Release();
}

void ModelNode::Init()
{
	_material = new Material();
}

void ModelNode::Release()
{
	_material->Release();
	_material = nullptr;

	int size = _childs.size();
	for (int i = 0; i < size; i++)
	{
		_childs[i]->Release();
		_childs[i] = nullptr;
	}

	_childs.clear();
}

void ModelNode::PreMove()
{
}

void ModelNode::Update()
{
}

void ModelNode::Render()
{
}
