#include "stdafx.h"
#include "SingletonManager.h"
#include "Input.h"

Input::Input()
{
	Init();
}

Input::~Input()
{
}

void Input::Init()
{

}

void Input::Update()
{
}

void Input::Delete()
{
}

void Input::Foo()
{
	::OutputDebugString(L"WTF");
}
