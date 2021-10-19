#pragma once
class PostProcess
{
public:
	PostProcess();
	~PostProcess();

	virtual void Init();
	virtual ULONG Release();
	
	virtual void SetRenderTarget();
	virtual void Draw();

	virtual void Resize();

protected:
	wrl::ComPtr<ID3D12Resource> _mainBuffer;
	wrl::ComPtr<ID3D12DescriptorHeap> _heap;
	UINT _ppDescriptorSize;

	DXGI_FORMAT _ppFormat;
	

};

