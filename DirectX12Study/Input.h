#pragma once
#include "Singletons.h"
class Input :
    public Singletons
{
public:
    Input();
    ~Input();

    // Singletons��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Delete() override;

    void Foo();

private:

};

