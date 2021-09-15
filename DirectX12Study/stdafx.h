#pragma once
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

#include <iostream>
#include <stdio.h>
#include <Windows.h>

#include <d3d12.h>
#include <d3d12shader.h>
#include <d3d12sdklayers.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <d3dtypes.h>
#include <dxgi.h>
#include <dxgicommon.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

/*
static HWND ghMainWnd;
bool InitWindowsApp(HINSTANCE instanceHandle, int show);
int Run();
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#pragma once 
ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v);
//{
//	//XMFLOAT3 dest;
//	//XMStoreFloat3(&dest, v);
//	XMFLOAT4 dest2;
//	XMStoreFloat4(&dest2, v);
//
//	//os << "(" << dest.x << ", " << dest.y << ", " << dest.z << "), ";
//	os << dest2.x << "/t" << dest2.y << "/t" << dest2.z << "/t" << dest2.w;
//	return os;
//}
ostream& XM_CALLCONV operator<<(ostream& os, FXMMATRIX m);
//{
//	for (int i = 0; i < 4; i++)
//	{
//		os << XMVectorGetX(m.r[i]) << "/t";
//		os << XMVectorGetY(m.r[i]) << "/t";
//		os << XMVectorGetZ(m.r[i]) << "/t";
//		os << XMVectorGetW(m.r[i]);
//		os << endl;
//	}
//
//	return os;
//}