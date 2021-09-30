#include "stdafx.h"
#include "D3D.h"
#include "SingletonManager.h"
#include "Window.h"

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
	_backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	_depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	_currentBackBuffer = 0;

	CreateD3DDevice();
	CreateFence();
	CreateCommand();

	LogAdapters();
	
}

void D3D::Update()
{

}

void D3D::Delete()
{
	_commandAllocator->Release();
	_commandQueue->Release();
	_commandList->Release();

	_fence->Release();
	_debugController->Release();
	_dxgiFactory->Release();
	_warpAdapter->Release();
	_d3dDevice->Release();
}

#pragma region LOG

void D3D::LogAdapters()
{
	UINT i = 0;
	IDXGIAdapter* adapter = nullptr;
	vector<IDXGIAdapter*> adapterList;
	while (_dxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
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

#pragma endregion

void D3D::CreateD3DDevice()
{
	DX::ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&_dxgiFactory)));

	HRESULT hardwareResult = D3D12CreateDevice(
		nullptr,
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&_d3dDevice)
	);

	if (FAILED(hardwareResult))
	{
		DX::ThrowIfFailed(_dxgiFactory->EnumAdapters(0, &_warpAdapter));

		DX::ThrowIfFailed(D3D12CreateDevice(
			_warpAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&_d3dDevice)
		));
	}
}

void D3D::CreateFence()
{
	DX::ThrowIfFailed(_d3dDevice->CreateFence(
		0,
		D3D12_FENCE_FLAG_NONE,
		IID_PPV_ARGS(&_fence)
	));

	_rtvDescriptorSize = _d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	_dsvDescriptorSize = _d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	_cbvDescriptorSize = _d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void D3D::MSAAQualityCheck()
{
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
	msQualityLevels.Format = _backBufferFormat;
	msQualityLevels.SampleCount = 4;
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msQualityLevels.NumQualityLevels = 0;
	DX::ThrowIfFailed(_d3dDevice->CheckFeatureSupport(
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
		&msQualityLevels,
		sizeof(msQualityLevels)
	));

	_msaaQuality = msQualityLevels.NumQualityLevels;
	assert(_msaaQuality > 0 && "Unexpected MSAA quality level.");
}

void D3D::CreateCommand()
{
	D3D12_COMMAND_QUEUE_DESC desc = {};
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	
	DX::ThrowIfFailed(_d3dDevice->CreateCommandQueue(
		&desc, IID_PPV_ARGS(&_commandQueue)
	));

	DX::ThrowIfFailed(_d3dDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(_commandAllocator.GetAddressOf())		
	));

	DX::ThrowIfFailed(_d3dDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		_commandAllocator.Get(),
		nullptr,
		IID_PPV_ARGS(_commandList.GetAddressOf())
	));

}

void D3D::CreateSwapChain()
{
	_swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC desc;
	desc.BufferDesc.Width = Singleton<Window>()->GetDesc().Width;
	desc.BufferDesc.Height = Singleton<Window>()->GetDesc().Height;
	desc.BufferDesc.RefreshRate.Numerator = Singleton<Window>()->GetDesc().MaxFPS;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = _backBufferFormat;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.SampleDesc.Count = _msaaQuality ? 4 : 1;
	desc.SampleDesc.Quality = _msaaQuality ? (_msaaQuality - 1) : 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = SwapChainBufferCount;
	desc.OutputWindow = Singleton<Window>()->GetDesc().ghMainWnd;
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	DX::ThrowIfFailed(_dxgiFactory->CreateSwapChain(
		_commandQueue.Get(),
		&desc,
		_swapChain.GetAddressOf()
	));
}

void D3D::CreateDescriptorHeap()
{
	{
		//rtv
		D3D12_DESCRIPTOR_HEAP_DESC desc;
		desc.NumDescriptors = SwapChainBufferCount;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		desc.NodeMask = 0;
		DX::ThrowIfFailed(_d3dDevice->CreateDescriptorHeap(
			&desc,
			IID_PPV_ARGS(_rtvHeap.GetAddressOf())
		));
	}

	{
		//dsv
		D3D12_DESCRIPTOR_HEAP_DESC desc;
		desc.NumDescriptors = SwapChainBufferCount;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		desc.NodeMask = 0;
		DX::ThrowIfFailed(_d3dDevice->CreateDescriptorHeap(
			&desc,
			IID_PPV_ARGS(_dsvHeap.GetAddressOf())
		));
	}

}

void D3D::CreateRenderTargetView()
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(
		_rtvHeap->GetCPUDescriptorHandleForHeapStart()
	);
	for (UINT i = 0; i < SwapChainBufferCount; i++)
	{
		DX::ThrowIfFailed(_swapChain->GetBuffer(
			i, IID_PPV_ARGS(&_swapChainBuffer[i])
		));

		_d3dDevice->CreateRenderTargetView(_swapChainBuffer[i].Get(),
			nullptr, rtvHeapHandle);

		rtvHeapHandle.Offset(1, _rtvDescriptorSize);
	}
}

void D3D::CreateDepthStencilView()
{
	D3D12_RESOURCE_DESC desc;
	desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Alignment = 0;
	desc.Width = Singleton<Window>()->GetDesc().Width;
	desc.Height = Singleton<Window>()->GetDesc().Height;
	desc.DepthOrArraySize = 1;
	desc.MipLevels = 1;
	desc.Format = _depthStencilFormat;
	desc.SampleDesc.Count = _msaaQuality ? 4 : 1;
	desc.SampleDesc.Quality = _msaaQuality ? (_msaaQuality - 1) : 0;
	desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE value;
	value.Format = _depthStencilFormat;
	value.DepthStencil.Depth = 1.0f;
	value.DepthStencil.Stencil = 0;
	DX::ThrowIfFailed(_d3dDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_COMMON,
		&value,
		IID_PPV_ARGS(_depthStencilBuffer.GetAddressOf())
	));

	CD3DX12_CPU_DESCRIPTOR_HANDLE handle(
		_dsvHeap->GetCPUDescriptorHandleForHeapStart()
	);

	_d3dDevice->CreateDepthStencilView(
		_depthStencilBuffer.Get(),
		nullptr,
		handle
	);

	_commandList->ResourceBarrier(
		1,
		&CD3DX12_RESOURCE_BARRIER::Transition(
			_depthStencilBuffer.Get(),
			D3D12_RESOURCE_STATE_COMMON,
			D3D12_RESOURCE_STATE_DEPTH_WRITE
		)
	);
}

void D3D::SetViewport()
{
	D3D12_VIEWPORT viewport;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(Singleton<Window>()->GetDesc().Width);
	viewport.Height = static_cast<float>(Singleton<Window>()->GetDesc().Height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	_commandList->RSSetViewports(1, &viewport);
}

void D3D::SetScissorRectangle()
{
	_scissorRect = { 0, 0, 
		Singleton<Window>()->GetDesc().Width / 2, 
		Singleton<Window>()->GetDesc().Height / 2 };
	_commandList->RSSetScissorRects(1, &_scissorRect);
}

void D3D::FlushCommandQueue()
{
	UINT currentFence = 0;

	currentFence++;
	//DX::ThrowIfFailed();
}

D3D12_CPU_DESCRIPTOR_HANDLE D3D::GetCurrentBackBufferView() const
{
	
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(_rtvHeap->GetCPUDescriptorHandleForHeapStart(),
		_currentBackBuffer,
		_rtvDescriptorSize);
}

D3D12_CPU_DESCRIPTOR_HANDLE D3D::GetDepthStencilView() const
{
	return _dsvHeap->GetCPUDescriptorHandleForHeapStart();
}
