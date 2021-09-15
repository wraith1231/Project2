#include "stdafx.h"
#include "Window.h"

Window::Window()
{

}

Window::~Window()
{
}

bool Window::Init(int show)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _desc.hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursorW(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"DirectX12";

	if (RegisterClass(&wc) == false)
	{
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		return false;
	}

	_desc.ghMainWnd = CreateWindow(
		L"DirectX12",
		L"DirectX12",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		_desc.Width,
		_desc.Height,
		0, 0,
		_desc.hInstance,
		0);

	if (_desc.ghMainWnd == 0)
	{
		MessageBox(0, L"Window Create FAILED", 0, 0);
		return false;
	}

	ShowWindow(_desc.ghMainWnd, show);
	UpdateWindow(_desc.ghMainWnd);

	return true;
}

int Window::Update()
{
	MSG msg = { 0 };

	BOOL bRet = 1;
	while (bRet = GetMessage(&msg, 0, 0, 0) != 0)
	{
		if (bRet == -1)
		{
			MessageBox(0, L"Get Message FAILED", L"ERROR", MB_OK);
			break;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

void Window::Delete()
{
}

void Window::SetDesc(WindowDesc desc)
{
	_desc.hInstance = desc.hInstance;
	_desc.ghMainWnd = desc.ghMainWnd;
}