#pragma once
class PostProcess
{
private:
	PostProcess() {}
	~PostProcess() {}

	virtual void Draw() {}

protected:
	wrl::ComPtr<ID3D12Resource> _mainBuffer;
	UINT _ppDescriptorSize;

	DXGI_FORMAT _ppFormat;
	

};

