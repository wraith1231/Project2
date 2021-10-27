#include "stdafx.h"
#include "D3D.h"
#include "SingletonManager.h"
#include "Window.h"

D3D::D3D()
{
	_rtvDescriptorSize = 0;
	_dsvDescriptorSize = 0;
	_cbvDescriptorSize = 0;
	_msaaQuality = 0;
	_currentBackBuffer = 0;

	_backBufferFormat = {};
	_depthStencilFormat = {};

	_scissorRect = {};
	_screenViewport = {};

	_currentFence = 0;

	_deviceInit = false;
	_backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	_depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	_currentBackBuffer = 0;
}

D3D::~D3D()
{
	Release();
}

void D3D::Init()
{
#if defined(DEBUG) || defined(_DEBUG)
	{
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&_debugController)));
		_debugController->EnableDebugLayer();
	}
#endif

	CreateD3DDevice();
	CreateFence();
	MSAAQualityCheck();

#ifdef _DEBUG
	LogAdapters();
#endif // _DEBUG

	CreateCommand();
	CreateSwapChain();
	CreateDescriptorHeap();
	Resize(Singleton<Window>()->GetDesc().Width,
		Singleton<Window>()->GetDesc().Height);

	_deviceInit = true;
}

void D3D::Update()
{
}

ULONG D3D::Release()
{
	_commandAllocator->Release();
	_commandQueue->Release();
	_commandList->Release();

	_swapChain->Release();
	for (int i = 0; i < SwapChainBufferCount; i++)
		_swapChainBuffer[i]->Release();
	_depthStencilBuffer->Release();

	_rtvHeap->Release();
	_dsvHeap->Release();

	_fence->Release();
	_dxgiFactory->Release();
	_d3dDevice->Release();
	
#ifdef _DEBUG
	_debugController->Release();
#endif // _DEBUG


	return 0;
}

void D3D::PreDraw()
{
	ClearCommandList();

	ResourceBarrior(GetCurrentBackBuffer());

	_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_commandList->RSSetViewports(1, &_screenViewport);
	_commandList->RSSetScissorRects(1, &_scissorRect);
	D3D12_CPU_DESCRIPTOR_HANDLE cbbv = GetCurrentBackBufferView();
	D3D12_CPU_DESCRIPTOR_HANDLE dsv = GetDepthStencilView();

	ClearRenderTargetView(cbbv);
	ClearDepthStencilView(dsv);

	SetRenderTargetView(1, &cbbv, &dsv);
}

void D3D::Draw()
{
	ResourceBarrior(GetCurrentBackBuffer());
	
	CloseCommandList();

	ExecuteCommandList();

	ThrowIfFailed(_swapChain->Present(0, 0));
	_currentBackBuffer = (_currentBackBuffer + 1) % SwapChainBufferCount;

	FlushCommandQueue();
}

void D3D::Resize(UINT width, UINT height)
{
	assert(_d3dDevice);
	assert(_swapChain);
	assert(_commandAllocator);

	FlushCommandQueue();

	ThrowIfFailed(_commandList->Reset(_commandAllocator.Get(), nullptr));

	for (int i = 0; i < SwapChainBufferCount; i++)
	{
		_swapChainBuffer[i].Reset();
	}
	_depthStencilBuffer.Reset();

	ThrowIfFailed(_swapChain->ResizeBuffers(
		SwapChainBufferCount,
		width, height,
		_backBufferFormat,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
	));

	_currentBackBuffer = 0;
	CreateRenderTargetView();
	CreateDepthStencilView(width, height);

	ThrowIfFailed(_commandList->Close());
	ID3D12CommandList* commandLists[] = { _commandList.Get() };
	_commandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

	FlushCommandQueue();

	SetViewport(width, height);
	SetScissorRectangle(width, height);
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

void D3D::SetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology)
{
	_commandList->IASetPrimitiveTopology(topology);
}

ID3D12Device* D3D::GetDevice()
{
	return _d3dDevice.Get();
}

wrl::ComPtr<ID3D12Resource> D3D::CreateDefaultBuffer(const void* initData, UINT64 byteSize, wrl::ComPtr<ID3D12Resource>& uploadBuffer)
{
	wrl::ComPtr<ID3D12Resource> retBuffer;
	auto temp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	auto temp2 = CD3DX12_RESOURCE_DESC::Buffer(byteSize);
	ThrowIfFailed(_d3dDevice->CreateCommittedResource(
		&temp, D3D12_HEAP_FLAG_NONE,
		&temp2, D3D12_RESOURCE_STATE_COMMON,
		nullptr,
		IID_PPV_ARGS(retBuffer.GetAddressOf())
	));

	temp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	ThrowIfFailed(_d3dDevice->CreateCommittedResource(
		&temp, D3D12_HEAP_FLAG_NONE,
		&temp2, D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(uploadBuffer.GetAddressOf())
	));

	D3D12_SUBRESOURCE_DATA data = {};
	data.pData = initData;
	data.RowPitch = byteSize;
	data.SlicePitch = data.RowPitch;

	auto temp3 = CD3DX12_RESOURCE_BARRIER::Transition(retBuffer.Get(), 
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_COPY_DEST);
	_commandList->ResourceBarrier( 1, &temp3);

	UpdateSubresources<1>(_commandList.Get(), retBuffer.Get(),
		uploadBuffer.Get(),
		0, 0, 1, &data);

	temp3 = CD3DX12_RESOURCE_BARRIER::Transition(retBuffer.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST,
		D3D12_RESOURCE_STATE_GENERIC_READ);
	_commandList->ResourceBarrier(1, &temp3);

	return retBuffer;
}

void D3D::CreateD3DDevice()
{
	DWORD dxgiFactoryFlag = 0;
#ifdef _DEBUG
	dxgiFactoryFlag = DXGI_CREATE_FACTORY_DEBUG;
#endif // _DEBUG


	HRESULT hr = CreateDXGIFactory2(dxgiFactoryFlag, IID_PPV_ARGS(&_dxgiFactory));
	if (FAILED(hr))
	{
		MessageBox(0, L"factory creation failed", L"Error", MB_OK);
	}

	HRESULT hardwareResult = D3D12CreateDevice(
		nullptr,
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&_d3dDevice)
	);

	if (FAILED(hardwareResult))
	{
		ThrowIfFailed(_dxgiFactory->EnumAdapters(0, &_warpAdapter));

		ThrowIfFailed(D3D12CreateDevice(
			_warpAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&_d3dDevice)
		));
	}
}

void D3D::CreateFence()
{
	ThrowIfFailed(_d3dDevice->CreateFence(
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
	ThrowIfFailed(_d3dDevice->CheckFeatureSupport(
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
	
	ThrowIfFailed(_d3dDevice->CreateCommandQueue(
		&desc, IID_PPV_ARGS(&_commandQueue)
	));

	ThrowIfFailed(_d3dDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(_commandAllocator.GetAddressOf())		
	));

	ThrowIfFailed(_d3dDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		_commandAllocator.Get(),
		nullptr,
		IID_PPV_ARGS(_commandList.GetAddressOf())
	));

	_commandList->Close();

}

void D3D::CreateSwapChain(UINT width, UINT height, DXGI_FORMAT format)
{
	_swapChain.Reset();
	_backBufferFormat = format;
	DXGI_SWAP_CHAIN_DESC1 desc;
	desc.Width = width;
	desc.Height = height;
	desc.Format = format;
	desc.Scaling = DXGI_SCALING_STRETCH;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	//desc.SampleDesc.Count = _msaaQuality ? 4 : 1;
	//desc.SampleDesc.Quality = _msaaQuality ? (_msaaQuality - 1) : 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = SwapChainBufferCount;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	desc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fs = {};
	fs.Windowed = true;

	HRESULT hr = _dxgiFactory->CreateSwapChainForHwnd(
		_commandQueue.Get(),
		Singleton<Window>()->GetDesc().ghMainWnd,
		&desc, &fs, nullptr, _swapChain.GetAddressOf()
	);
	//ThrowIfFailed(_dxgiFactory->CreateSwapChain(
	//	_commandQueue.Get(),
	//	&desc,
	//	_swapChain.GetAddressOf()
	//));

	if (FAILED(hr))
	{
		MessageBox(0, L"swapchain creation failed", L"Error", MB_OK);
	}
	
	int a = 0;
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
		ThrowIfFailed(_d3dDevice->CreateDescriptorHeap(
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
		ThrowIfFailed(_d3dDevice->CreateDescriptorHeap(
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
		ThrowIfFailed(_swapChain->GetBuffer(
			i, IID_PPV_ARGS(&_swapChainBuffer[i])
		));

		_d3dDevice->CreateRenderTargetView(_swapChainBuffer[i].Get(),
			nullptr, rtvHeapHandle);

		rtvHeapHandle.Offset(1, _rtvDescriptorSize);
	}
}

void D3D::CreateDepthStencilView(UINT width, UINT height, DXGI_FORMAT format)
{
	_depthStencilFormat = format;
	D3D12_RESOURCE_DESC desc;
	desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Alignment = 0;
	desc.Width = width;
	desc.Height = height;
	desc.DepthOrArraySize = 1;
	desc.MipLevels = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	//desc.SampleDesc.Count = _msaaQuality ? 4 : 1;
	//desc.SampleDesc.Quality = _msaaQuality ? (_msaaQuality - 1) : 0;
	desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE value = {};
	value.Format = _depthStencilFormat;
	value.DepthStencil.Depth = 1.0f;
	value.DepthStencil.Stencil = 0;

	auto temp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	ThrowIfFailed(_d3dDevice->CreateCommittedResource(
		&temp,
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

	auto temp2 = CD3DX12_RESOURCE_BARRIER::Transition(
		_depthStencilBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_DEPTH_WRITE
	);
	_commandList->ResourceBarrier(
		1,
		&temp2
	);
}

void D3D::SetViewport(UINT width, UINT height)
{
	_screenViewport.TopLeftX = 0.0f;
	_screenViewport.TopLeftY = 0.0f;
	_screenViewport.Width = static_cast<float>(width);
	_screenViewport.Height = static_cast<float>(height);
	_screenViewport.MinDepth = 0.0f;
	_screenViewport.MaxDepth = 1.0f;

	_commandList->RSSetViewports(1, &_screenViewport);
}

void D3D::SetScissorRectangle(UINT width, UINT height)
{
	_scissorRect = { 0, 0, 
		static_cast<long>(width / 2), 
		static_cast<long>(height / 2) };
	_commandList->RSSetScissorRects(1, &_scissorRect);
	
}

void D3D::FlushCommandQueue()
{
	_currentFence++;
	//ThrowIfFailed();

	ThrowIfFailed(_commandQueue->Signal(_fence.Get(), _currentFence));

	if (_fence->GetCompletedValue() < _currentFence)
	{
		HANDLE eventHandle = CreateEventEx(nullptr, L"", false, EVENT_ALL_ACCESS);

		ThrowIfFailed(_fence->SetEventOnCompletion(_currentFence, eventHandle));

		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}

void D3D::ClearCommandList()
{
	ThrowIfFailed(_commandAllocator->Reset());

	ThrowIfFailed(_commandList->Reset(_commandAllocator.Get(), nullptr));
}

void D3D::ResourceBarrior(ID3D12Resource* resource)
{
	auto temp = CD3DX12_RESOURCE_BARRIER::Transition(
		resource,
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET
	);
	_commandList->ResourceBarrier(1, &temp);
}

void D3D::ClearRenderTargetView(D3D12_CPU_DESCRIPTOR_HANDLE rtv, const FLOAT* color)
{
	_commandList->ClearRenderTargetView(rtv,
		color, 0, nullptr
	);
}

void D3D::ClearDepthStencilView(D3D12_CPU_DESCRIPTOR_HANDLE dsv)
{
	_commandList->ClearDepthStencilView(dsv,
		D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
		1.0f, 0, 0, nullptr
	);
}

void D3D::SetRenderTargetView(UINT num, D3D12_CPU_DESCRIPTOR_HANDLE* rtv, D3D12_CPU_DESCRIPTOR_HANDLE* dsv)
{
	_commandList->OMSetRenderTargets(num, rtv,
		true, dsv
	);
}

void D3D::CloseCommandList()
{
	ThrowIfFailed(_commandList->Close());
}

void D3D::ExecuteCommandList()
{
	ID3D12CommandList* lists[] = { _commandList.Get() };
	_commandQueue->ExecuteCommandLists(_countof(lists), lists);
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

ID3D12Resource* D3D::GetCurrentBackBuffer() const
{
	return _swapChainBuffer[_currentBackBuffer].Get();
}
