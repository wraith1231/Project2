#pragma once
class Shader
{
public:
	Shader();
	~Shader();


private:
	wrl::ComPtr<ID3D12Resource> _vertexBuffer;

};

