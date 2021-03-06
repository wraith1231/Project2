#pragma once
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <cstdint>
#include <thread>
#include <time.h>
#include <vector>
#include <map>
#include <functional>
#include <exception>

#include <d3d12.h>
#include <d3d12shader.h>
#include <d3d12sdklayers.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <d3dtypes.h>
#include <dxgi.h>
#include <dxgicommon.h>

#include "External/d3dUtil.h"
#include "External/d3dx12.h"
#include "d3dUtil.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

namespace ch = std::chrono;
namespace wrl = Microsoft::WRL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#pragma once 
ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v);
ostream& XM_CALLCONV operator<<(ostream& os, FXMMATRIX m);

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT4 Color;
	XMFLOAT2 UV;
};