#pragma once
class Model
{
public:
	Model();
	~Model();

private:
	XMVECTOR _preWorldPosition;
	XMVECTOR _worldPosition;
	XMVECTOR _postWorldPosition;

	XMVECTOR _scale;
	XMVECTOR _rotate;

	XMVECTOR _direction;

};

