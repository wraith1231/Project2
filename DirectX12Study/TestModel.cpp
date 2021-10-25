#include "stdafx.h"
#include "TestModel.h"

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
