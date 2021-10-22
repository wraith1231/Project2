#include "stdafx.h"
#include "PostProcess.h"
#include "RenderManager.h"
#include "SingletonManager.h"
#include "Window.h"
#include "Time.h"
#include "D3D.h"

PostProcess::PostProcess()
{
	Init();
}

PostProcess::~PostProcess()
{
	Release();
}

void PostProcess::Init()
{
	D3D12_DESCRIPTOR_HEAP_DESC desc;
	desc.NumDescriptors = 1;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	desc.NodeMask = 0;

	ID3D12Device* device = Singleton<D3D>()->GetDevice();
	ThrowIfFailed(device->CreateDescriptorHeap(
		&desc,
		IID_PPV_ARGS(_heap.GetAddressOf())
	));

	CD3DX12_CPU_DESCRIPTOR_HANDLE heapHandle(_heap->GetCPUDescriptorHandleForHeapStart());

	device->CreateRenderTargetView(_mainBuffer.Get(),
		nullptr, heapHandle);
	heapHandle.Offset(1, Singleton<D3D>()->RTVDescriptorSize());
	/*
	* {
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
	*/
}

ULONG PostProcess::Release()
{
	return 0;
}

void PostProcess::SetRenderTarget()
{
}

void PostProcess::Draw()
{
}

void PostProcess::Resize()
{
}
