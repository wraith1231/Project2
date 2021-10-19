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

    virtual ULONG Release() override;

    void PreDraw();
    void Draw();

    void Resize(UINT width = 1600, UINT height = 900);

    void LogAdapters();
    void LogAdapterOutputs(IDXGIAdapter* adapter);
    void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

    bool DeviceInit() { return _deviceInit; }

    D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView() const;
    D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const;
    ID3D12Resource* GetCurrentBackBuffer() const;

    void FlushCommandQueue();

    void ClearCommandList();
    void ResourceBarrior(ID3D12Resource* resource);
    void ClearRenderTargetView(D3D12_CPU_DESCRIPTOR_HANDLE rtv, const FLOAT* color = Colors::LightSteelBlue);
    void ClearDepthStencilView(D3D12_CPU_DESCRIPTOR_HANDLE dsv);
    void SetRenderTargetView(UINT num, D3D12_CPU_DESCRIPTOR_HANDLE* rtv, D3D12_CPU_DESCRIPTOR_HANDLE* dsv = nullptr);
    void CloseCommandList();
    void ExecuteCommandList();

    UINT RTVDescriptorSize() { return _rtvDescriptorSize; }

private:
    void CreateD3DDevice();
    void CreateFence();
    void MSAAQualityCheck();
    void CreateCommand();
    void CreateSwapChain(
        UINT width = 1600, UINT height = 900,
        DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
    void CreateDescriptorHeap();
    void CreateRenderTargetView();
    void CreateDepthStencilView(
        UINT width = 1600, UINT height = 900,
        DXGI_FORMAT format = DXGI_FORMAT_D24_UNORM_S8_UINT);
    void SetViewport(UINT width = 1600, UINT height = 900);
    void SetScissorRectangle(UINT width = 1600, UINT height = 900);

private:
    wrl::ComPtr<ID3D12Debug> _debugController;
    
    wrl::ComPtr<IDXGIFactory4> _dxgiFactory;
    wrl::ComPtr<IDXGIAdapter> _warpAdapter;
    wrl::ComPtr<ID3D12Device> _d3dDevice;
    wrl::ComPtr<ID3D12Fence> _fence;
    wrl::ComPtr<IDXGISwapChain1> _swapChain;
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
    D3D12_VIEWPORT _screenViewport;

    UINT64 _currentFence = 0;

    bool _deviceInit;
};

