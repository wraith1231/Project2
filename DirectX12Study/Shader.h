#pragma once
class Shader
{
public:
	Shader();
	~Shader();

	void Init();
	void Render(void* vertices, UINT64 vertexByte);
	void Release();

private:
	wrl::ComPtr<ID3D12Resource> _vertexBuffer;
	wrl::ComPtr<ID3D12Resource> _uploadBuffer;

};

