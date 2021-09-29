#include "stdafx.h"
#include "D3D.h"

D3D::D3D()
{
	Init();
}

D3D::~D3D()
{
	Delete();
}

void D3D::Init()
{
#if defined(DEBUG) || defined(_DEBUG)
	{
		DX::ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&_debugController)));
		_debugController->EnableDebugLayer();
	}
#endif

	CreateD3DDevice();
	LogAdapters();
	
}

void D3D::Update()
{

}

void D3D::Delete()
{
	_debugController->Release();
	_mdxgiFactory->Release();
	_pWarpAdapter->Release();
	_md3dDevice->Release();
}

void D3D::LogAdapters()
{
	UINT i = 0;
	IDXGIAdapter* adapter = nullptr;
	vector<IDXGIAdapter*> adapterList;
	while (_mdxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);

		wstring text = L"***Adapter : ";
		text += desc.Description;
		text += L"\n";

		OutputDebugString(text.c_str());

		adapterList.push_back(adapter);
		++i;
	}

	for (size_t i = 0; i < adapterList.size(); i++)
	{
		LogAdapterOutputs(adapterList[i]);
	}
}

void D3D::LogAdapterOutputs(IDXGIAdapter* adapter)
{
	UINT i = 0;
	IDXGIOutput* output = nullptr;
	while (adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_OUTPUT_DESC desc;
		output->GetDesc(&desc);

		wstring text = L"***Output : ";
		text += desc.DeviceName;
		text += L"\n";
		OutputDebugString(text.c_str());

		++i;
	}
}

void D3D::LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format)
{
	UINT count = 0;
	UINT flags = 0;

	output->GetDisplayModeList(format, flags, &count, nullptr);

	vector<DXGI_MODE_DESC> modeList(count);
	output->GetDisplayModeList(format, flags, &count, &modeList[0]);

	for (auto& x : modeList)
	{
		UINT n = x.RefreshRate.Numerator;
		UINT d = x.RefreshRate.Denominator;
		wstring text =
			L"Width = " + to_wstring(x.Width) + L" " +
			L"Height = " + to_wstring(x.Height) + L" " +
			L"Refresh = " + to_wstring(n) + L"/" + to_wstring(d) + L"\n";

		OutputDebugString(text.c_str());
	}
}

void D3D::CreateD3DDevice()
{
	DX::ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&_mdxgiFactory)));

	HRESULT hardwareResult = D3D12CreateDevice(
		nullptr,
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&_md3dDevice)
	);

	if (FAILED(hardwareResult))
	{
		DX::ThrowIfFailed(_mdxgiFactory->EnumAdapters(0, &_pWarpAdapter));

		DX::ThrowIfFailed(D3D12CreateDevice(
			_pWarpAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&_md3dDevice)
		));
	}

	CreateFence();
}

void D3D::CreateFence()
{
	DX::ThrowIfFailed(_md3dDevice->CreateFence(
		0,
		D3D12_FENCE_FLAG_NONE,
		IID_PPV_ARGS(&_mFence)
	));


}

void D3D::CreateCommandList()
{
	D3D12_COMMAND_QUEUE_DESC desc = {};
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	DX::ThrowIfFailed(_md3dDevice->CreateCommandQueue(
		&desc, IID_PPV_ARGS(&_mCommandQueue)
	));

	DX::ThrowIfFailed(_md3dDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		,
		IID_PPV_ARGS(&_mCommandAllocator)
	));

	DX::ThrowIfFailed(_md3dDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		_mCommandAllocator,

	))
}

void D3D::FlushCommandQueue()
{
	UINT currentFence = 0;

	currentFence++;

	DX::ThrowIfFailed();
}
