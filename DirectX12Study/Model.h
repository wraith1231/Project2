#pragma once
class Material;
class ModelNode;

class Model
{
public:
	Model();
	~Model();

	virtual void Init();
	virtual void PreMove(); //현재 world position을 pre world position으로, post를 현재 world로, 이동 후에 quad tree에 맞게 넣어주기도
	virtual void Update();	//여기서 각종 연산 처리를 해줘야하는데... 가급적 유한 상태기계로 하는게 좀 덜 더러울려나

	virtual void Render();
	virtual void Release();

protected:
	string _modelName;

	XMVECTOR _preWorldPosition;
	XMVECTOR _worldPosition;
	XMVECTOR _postWorldPosition;

	XMVECTOR _scale;
	XMVECTOR _rotate;

	XMVECTOR _direction;

	float _speed;
	const float* _gameSpeed;

	ModelNode* _coreNode;
};

