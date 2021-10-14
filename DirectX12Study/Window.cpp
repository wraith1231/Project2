#include "stdafx.h"
#include "Window.h"
#include "SingletonManager.h"
#include "Time.h"
#include "D3D.h"

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

	Singleton<D3D>()->Init();
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

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE) == TRUE)
		{
			//message 입력이 있는 경우
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			last = ch::high_resolution_clock::now();
			diff = last - now;
			delta = (float)ch::duration_cast<ch::milliseconds>(diff).count() * 0.001f;


			if (delta < (1 / (float)_desc.MaxFPS))
			{
				continue;
			}
			now = last;
			//Singleton<Time>("Time")->SetDeltaTime(delta);
			Singleton<Time>()->SetDeltaTime(delta);

			wstring deltaStr = to_wstring(delta);
			wstring running = to_wstring(Singleton<Time>()->GetRunningTime());

			wstring windowText = L"D3D12 delta : " + deltaStr
				+ L" Running : " + running;
			SetWindowText(_desc.ghMainWnd, windowText.c_str());
			//Message 입력이 없는 경우
			
			if (_desc.Paused == false)
			{
				SingletonManager::Singleton()->Update();

				Singleton<D3D>()->Draw();
			}
			else
			{
				Sleep(100);
			}
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

void Window::SetWidth(int width)
{
	_desc.Width = width;
}

void Window::SetHeight(int height)
{
	_desc.Height = height;
}

void Window::SetPaused(bool paused)
{
	_desc.Paused = paused;
}
