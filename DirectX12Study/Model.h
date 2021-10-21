#pragma once
class Model
{
public:
	Model();
	~Model();

	void Init();
	void PreMove(); //���� world position�� pre world position����, post�� ���� world��, �̵� �Ŀ� quad tree�� �°� �־��ֱ⵵
	void Update();	//���⼭ ���� ���� ó���� ������ϴµ�... ������ ���� ���±��� �ϴ°� �� �� ���������

	void Render();
	void Release();

private:
	XMVECTOR _preWorldPosition;
	XMVECTOR _worldPosition;
	XMVECTOR _postWorldPosition;

	XMVECTOR _scale;
	XMVECTOR _rotate;

	XMVECTOR _direction;

};

