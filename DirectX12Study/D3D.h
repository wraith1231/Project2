#pragma once
#include "Singletons.h"

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
    
    void CreateCommandList();
    void FlushCommandQueue();
private:
    wrl::ComPtr<ID3D12Debug> _debugController;
    wrl::ComPtr<IDXGIFactory> _mdxgiFactory;
    wrl::ComPtr<IDXGIAdapter> _pWarpAdapter;
    wrl::ComPtr<ID3D12Device> _md3dDevice;
    wrl::ComPtr<ID3D12Fence> _mFence;

    wrl::ComPtr<ID3D12CommandAllocator> _mCommandAllocator;
    wrl::ComPtr<ID3D12CommandQueue> _mCommandQueue;
    wrl::ComPtr<ID3D12CommandList> _mCommandList;
};

