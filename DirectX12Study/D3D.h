#pragma once
#include "Singletons.h"

class D3D :
    public Singletons
{
public:
    D3D();
    ~D3D();

    // Singletons을(를) 통해 상속됨
    virtual void Init() override;

    virtual void Update() override;

    virtual void Delete() override;
private:


};

