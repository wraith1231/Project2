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

private:
	vector<Vertex> _vertices;
	vector<UINT> _indices;
	Material* _material;

	vector<ModelNode*> _childs;
};