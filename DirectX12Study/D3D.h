#pragma once
#include "Singletons.h"

class D3D :
    public Singletons
{
public:
    D3D();
    ~D3D();

    // Singletons��(��) ���� ��ӵ�
    virtual void Init() override;

    virtual void Update() override;

    virtual void Delete() override;
private:


};

