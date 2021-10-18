#pragma once
#include "Singletons.h"

class PostProcess;

class RenderManager :
    public Singletons
{
public:
    RenderManager();
    ~RenderManager();

    // Singletons을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Delete() override;

private:
    map<string, PostProcess*> _postProcesses;
};

