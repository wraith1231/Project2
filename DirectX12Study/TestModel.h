#pragma once
#include "Model.h"
class TestModel :
    public Model
{
public:
    TestModel();
    ~TestModel();

	virtual void Init() override;
	virtual void PreMove() override; //���� world position�� pre world position����, post�� ���� world��, �̵� �Ŀ� quad tree�� �°� �־��ֱ⵵
	virtual void Update() override;	//���⼭ ���� ���� ó���� ������ϴµ�... ������ ���� ���±��� �ϴ°� �� �� ���������

	virtual void Render() override;
	virtual void Release() override;

private:


};

