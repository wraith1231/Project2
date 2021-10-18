#include "stdafx.h"
#include "SingletonManager.h"
#include "Input.h"
#include "Window.h"
#include "D3D.h"

Input::Input()
{
	Init();
}

Input::~Input()
{
	Delete();
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

LRESULT Input::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATE:
	{

		break;
	}
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		Singleton<Window>()->SetWidth(width);
		Singleton<Window>()->SetHeight(height);

		if (Singleton<D3D>()->DeviceInit() == true)
		{
			if (wParam == SIZE_MINIMIZED)
			{

			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				Singleton<D3D>()->Resize(width, height);
			}
			else if (wParam == SIZE_RESTORED)
			{
				Singleton<D3D>()->Resize(width, height);
			}
		}
		return 0;
	}
	case WM_ENTERSIZEMOVE:
	{
		Singleton<Window>()->SetPaused(true);
		break;
	}
	case WM_EXITSIZEMOVE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		Singleton<Window>()->SetPaused(false);
		//Singleton<D3D>()->Resize(width, height);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_MENUCHAR:
	{
		break;
	}
	case WM_LBUTTONDOWN:
	{
		break;
	}
	case WM_RBUTTONDOWN:
	{
		break;
	}
	case WM_MBUTTONDOWN:
	{
		break;
	}
	case WM_LBUTTONUP:
	{
		break;
	}
	case WM_RBUTTONUP:
	{
		break;
	}
	case WM_MBUTTONUP:
	{
		break;
	}
	case WM_MOUSEMOVE:
	{
		break;
	}
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
