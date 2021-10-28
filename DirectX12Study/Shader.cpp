#include "stdafx.h"
#include "Shader.h"
#include "SingletonManager.h"
#include "D3D.h"

Shader::Shader()
{
	Init();
}

Shader::~Shader()
{
	Release();
}

void Shader::Init()
{
}

void Shader::Render(void* vertices, UINT64 vertexByte)
{
	_vertexBuffer = Singleton<D3D>()->CreateDefaultBuffer(vertices, vertexByte, _uploadBuffer);
}

void Shader::Release()
{
	_vertexBuffer->Release();
	_uploadBuffer->Release();
}

