#include "stdafx.h"
#include "Window.h"
#include "SingletonManager.h"
#include "Time.h"

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
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
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
		_desc.x,
		_desc.y,
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

void Window::Init()
{
}

int Window::Run()
{
	MSG msg = { 0 };

	ch::time_point<ch::high_resolution_clock> now = ch::high_resolution_clock::now();

	ch::time_point<ch::high_resolution_clock> last;
	ch::nanoseconds diff;
	float delta;
	while (msg.message != WM_QUIT)
	{
		last = ch::high_resolution_clock::now();
		diff = last - now;
		delta = (float)ch::duration_cast<ch::milliseconds>(diff).count();


		if (delta < (1 / (float)_desc.MaxFPS) * 1000)
		{
			continue;
		}
		now = last;
		//Singleton<Time>("Time")->SetDeltaTime(delta);
		Singleton<Time>()->SetDeltaTime(delta);

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE) == TRUE)
		{
			//message 입력이 있는 경우
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//Message 입력이 없는 경우
			SingletonManager::Singleton()->Update();
		}
	}

	SingletonManager::Singleton()->Delete();
	return (int)msg.wParam;
}

void Window::Update()
{
}

void Window::Delete()
{
}

void Window::SetDesc(WindowDesc desc)
{
	_desc.hInstance = desc.hInstance;
	_desc.ghMainWnd = desc.ghMainWnd;
}