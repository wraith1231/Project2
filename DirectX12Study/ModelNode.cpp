#include "stdafx.h"
#include "ModelNode.h"
#include "Material.h"
#include "SingletonManager.h"
#include "D3D.h"

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

	_vertexBuffer->Release();
	_vertexUploadBuffer->Release();

	_indexBuffer->Release();
	_indexUploadBuffer->Release();

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

void ModelNode::AddVertex(Vertex vertex)
{
	_vertices.push_back(vertex);
}

void ModelNode::AddVertex(int num, ...)
{
	va_list value;

	va_start(value, sizeof(Vertex));

	for (int i = 0; i < num; i++)
		_vertices.push_back(va_arg(value, Vertex));

	va_end(value);
}

void ModelNode::AddIndex(int num, ...)
{
	va_list value;

	va_start(value, sizeof(UINT));

	for (int i = 0; i < num; i++)
	{
		_indices.push_back(va_arg(value, UINT));
	}
	va_end(value);
}

void ModelNode::SetViews()
{
	Singleton<D3D>()->SetVertexBufferView(_vertexBuffereViews);
	Singleton<D3D>()->SetIndexBufferView(_indexBufferView);
}

void ModelNode::CreateBuffer()
{
	_vertexBuffer = Singleton<D3D>()->CreateDefaultBuffer(&_vertices, _vertices.size() * sizeof(Vertex), _vertexUploadBuffer);
	_indexBuffer = Singleton<D3D>()->CreateDefaultBuffer(&_indices, _indices.size() * sizeof(UINT), _indexUploadBuffer);

	D3D12_VERTEX_BUFFER_VIEW vertexView;
	vertexView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	vertexView.StrideInBytes = sizeof(Vertex);
	vertexView.SizeInBytes = _vertices.size() * sizeof(Vertex);

	_vertexBuffereViews.push_back(vertexView);

	_indexBufferView.BufferLocation = _indexBuffer->GetGPUVirtualAddress();
	_indexBufferView.Format = DXGI_FORMAT_R16_UINT;
	_indexBufferView.SizeInBytes = _indices.size() * sizeof(UINT);

}

ModelNode* ModelNode::GetChild(string name)
{
	ModelNode* ret = nullptr;
	if (name == _boneName)
		ret = this;
	else
	{
		int size = _childs.size();
		for (int i = 0; i < size; i++)
		{
			ret = _childs[i]->GetChild(name);
			if (ret != nullptr)
				break;
		}
	}

	return ret;
}
