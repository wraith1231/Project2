#pragma once
class Terrain
{
public:
	Terrain();
	~Terrain();

	void Init();
	void Release();
	void Update();
	void Render();

private:
	vector<Vertex> _vertices;
	vector<UINT> _indices;
};

