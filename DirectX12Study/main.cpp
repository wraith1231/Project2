#include "stdafx.h"
#include "SingletonManager.h"
#include "Window.h"

#pragma region XMVECTOR_XMMATRIX_OUTPUT
ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v)
{
	//XMFLOAT3 dest;
	//XMStoreFloat3(&dest, v);
	XMFLOAT4 dest2;
	XMStoreFloat4(&dest2, v);

	//os << "(" << dest.x << ", " << dest.y << ", " << dest.z << "), ";
	os << dest2.x << "	" << dest2.y << "	" << dest2.z << "	" << dest2.w;
	return os;
}
ostream& XM_CALLCONV operator<<(ostream& os, FXMMATRIX m)
{
	for (int i = 0; i < 4; i++)
	{
		os << XMVectorGetX(m.r[i]) << "	";
		os << XMVectorGetY(m.r[i]) << "	";
		os << XMVectorGetZ(m.r[i]) << "	";
		os << XMVectorGetW(m.r[i]);
		os << endl;
	}

	return os;
}
#pragma endregion


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, INT nShowCmd)
{
	SingletonManager::Singleton()->Init();

	WindowDesc desc;
	desc.hInstance = hInstance;
	SingletonManager::Singleton()->GetWindow()->SetDesc(desc);

	if(SingletonManager::Singleton()->GetWindow()->Init(nShowCmd)==false)
		return 0;
	//ghMainWnd = 0;
	//if (InitWindowsApp(hInstance, nShowCmd) == false)
	//	return 0;

	return SingletonManager::Singleton()->GetWindow()->Update();
	//return Run();
}

LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(SingletonManager::Singleton()->GetWindow()->GetDesc().ghMainWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//int main()
//{
//	//이거 쓸려면 windows.h 필요함 근데 이거 SSE2 지원 여부 확인인데 펜티엄4나 K8 이후론 다 지원해서 요샌 쓸모없음
//	if (!XMVerifyCPUSupport())
//	{
//		cout << "DirectXMath not supported" << endl;
//		return 0;
//	}
//
//	XMVectorTest* test = new XMVectorTest();
//	test->test();
//
//	XMMatrixTest* mtest = new XMMatrixTest();
//	mtest->Test();
//
//	return 0;
//}

/*
bool InitWindowsApp(HINSTANCE instanceHandle, int show)
{
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursorW(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"Window Class";

	if (RegisterClass(&wc) == false)
	{
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		return false;
	}

	ghMainWnd = CreateWindow(
		L"Window Class",
		L"Win64 Basic",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0, 0,
		instanceHandle,
		0);

	if (ghMainWnd == 0)
	{
		MessageBox(0, L"Window Create FAILED", 0, 0);
		return false;
	}

	ShowWindow(ghMainWnd, show);
	UpdateWindow(ghMainWnd);

	return true;
}

int Run()
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
*/