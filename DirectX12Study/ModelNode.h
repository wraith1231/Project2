#pragma once

class Material;

class ModelNode
{
public:
	ModelNode();
	~ModelNode();

	void Init();
	void Release();
	void PreMove();
	void Update();
	void Render();

	void AddVertex(Vertex vertex);

	//Vertex 자료형만 받음
	void AddVertex(int num, ...);
	//UINT 자료형만 받음
	void AddIndex(int num, ...);

	void SetViews();

	void CreateBuffer();

	ModelNode* GetChild(string name);

private:
	string _boneName;

	vector<Vertex> _vertices;
	vector<UINT> _indices;
	Material* _material;

	vector<D3D12_VERTEX_BUFFER_VIEW> _vertexBuffereViews;
	D3D12_INDEX_BUFFER_VIEW _indexBufferView;

	wrl::ComPtr<ID3D12Resource> _vertexBuffer;
	wrl::ComPtr<ID3D12Resource> _vertexUploadBuffer;
	wrl::ComPtr<ID3D12Resource> _indexBuffer;
	wrl::ComPtr<ID3D12Resource> _indexUploadBuffer;

	vector<ModelNode*> _childs;
};