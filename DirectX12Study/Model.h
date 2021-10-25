#pragma once
class Material;

class Model
{
public:
	Model();
	~Model();

	virtual void Init();
	virtual void PreMove(); //���� world position�� pre world position����, post�� ���� world��, �̵� �Ŀ� quad tree�� �°� �־��ֱ⵵
	virtual void Update();	//���⼭ ���� ���� ó���� ������ϴµ�... ������ ���� ���±��� �ϴ°� �� �� ���������

	virtual void Render();
	virtual void Release();

protected:
	XMVECTOR _preWorldPosition;
	XMVECTOR _worldPosition;
	XMVECTOR _postWorldPosition;

	XMVECTOR _scale;
	XMVECTOR _rotate;

	XMVECTOR _direction;

	float _speed;
	const float* _gameSpeed;

	Material* _material;

	vector<Vertex> _vertices;
	vector<UINT> _indices;
};

