#include "stdafx.h"
#include "TestModel.h"
#include "ModelNode.h"
#include "SingletonManager.h"
#include "D3D.h"

TestModel::TestModel()
{
	Init();
}

TestModel::~TestModel()
{
	Release();
}

void TestModel::Init()
{
	__super::Init();

	_coreNode->AddVertex(Vertex{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(Colors::White),XMFLOAT2(0.0f, 0.0f) });
	_coreNode->AddVertex(Vertex{ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(Colors::Black),XMFLOAT2(0.0f, 0.0f) });
	_coreNode->AddVertex(Vertex{ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(Colors::Green),XMFLOAT2(0.0f, 0.0f) });
	_coreNode->AddVertex(Vertex{ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(Colors::Red),XMFLOAT2(0.0f, 0.0f) });
	_coreNode->AddVertex(Vertex{ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(Colors::Orange),XMFLOAT2(0.0f, 0.0f) });
	_coreNode->AddVertex(Vertex{ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(Colors::DarkCyan),XMFLOAT2(0.0f, 0.0f) });
	_coreNode->AddVertex(Vertex{ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(Colors::Magenta),XMFLOAT2(0.0f, 0.0f) });
	_coreNode->AddVertex(Vertex{ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(Colors::Maroon),XMFLOAT2(0.0f, 0.0f) });

	_coreNode->AddIndex(36, 0, 1, 2, 0, 2, 3, 4, 6, 5,
	4, 7, 6, 4, 5, 1, 4, 1, 0, 3, 2, 6, 3, 6, 7,
	1, 5, 6, 1, 6, 2, 4, 0, 3, 4, 3, 7);

	_coreNode->CreateBuffer();
}

void TestModel::PreMove()
{
	__super::PreMove();
}

void TestModel::Update()
{
	__super::Update();
}

void TestModel::Render()
{
	__super::Render();
}

void TestModel::Release()
{
	__super::Release();
}
