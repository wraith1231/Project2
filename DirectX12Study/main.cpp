#include "stdafx.h"
#include "SingletonManager.h"
#include "Window.h"
#include "Input.h"

#pragma region XMVECTOR_XMMATRIX_OUTPUT
ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v)
{
	XMFLOAT4 dest2;
	XMStoreFloat4(&dest2, v);

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
	
	WindowDesc desc;
	desc.hInstance = hInstance;
	Singleton<Window>()->SetDesc(desc);

	if (Singleton<Window>()->Init(nShowCmd) == false)
		return 0;

	SingletonManager::Singleton()->Init();

	return Singleton<Window>()->Run();
}

LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return Singleton<Input>()->MsgProc(hWnd, msg, wParam, lParam);
}