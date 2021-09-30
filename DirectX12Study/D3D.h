#pragma once
#include "Singletons.h"

const UINT SwapChainBufferCount = 2;
class D3D :
    public Singletons
{
public:
    D3D();
    ~D3D();

    // Singletons을(를) 통해 상속됨
    virtual void Init() override;

    virtual void Update() override;

    virtual void Delete() override;

    void LogAdapters();
    void LogAdapterOutputs(IDXGIAdapter* adapter);
    void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

private:
    void CreateD3DDevice();
    void CreateFence();
    void MSAAQualityCheck();
    void CreateCommand();
    void CreateSwapChain();
    void CreateDescriptorHeap();
    void CreateRenderTargetView();
    void CreateDepthStencilView();
    void SetViewport();
    void SetScissorRectangle();

    void FlushCommandQueue();

    D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView() const;
    D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const;

private:
    wrl::ComPtr<ID3D12Debug> _debugController;
    
    wrl::ComPtr<IDXGIFactory> _dxgiFactory;
    wrl::ComPtr<IDXGIAdapter> _warpAdapter;
    wrl::ComPtr<ID3D12Device> _d3dDevice;
    wrl::ComPtr<ID3D12Fence> _fence;
    wrl::ComPtr<IDXGISwapChain> _swapChain;
    wrl::ComPtr<ID3D12Resource> _swapChainBuffer[SwapChainBufferCount];

    wrl::ComPtr<ID3D12DescriptorHeap> _rtvHeap;
    wrl::ComPtr<ID3D12DescriptorHeap> _dsvHeap;

    wrl::ComPtr<ID3D12CommandAllocator> _commandAllocator;
    wrl::ComPtr<ID3D12CommandQueue> _commandQueue;
    wrl::ComPtr<ID3D12GraphicsCommandList> _commandList;

    wrl::ComPtr<ID3D12Resource> _depthStencilBuffer;

    UINT _rtvDescriptorSize;
    UINT _dsvDescriptorSize;
    UINT _cbvDescriptorSize;
    UINT _msaaQuality;
    //UINT _swapChainBufferCount;
    UINT _currentBackBuffer;

    DXGI_FORMAT _backBufferFormat;
    DXGI_FORMAT _depthStencilFormat;

    tagRECT _scissorRect;
};

