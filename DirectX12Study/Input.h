#pragma once
#include "Singletons.h"
class Input :
    public Singletons
{
public:
    Input();
    ~Input();

    // Singletons을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Delete() override;

    void Foo();

private:

};

