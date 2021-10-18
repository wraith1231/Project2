#pragma once
#include "Singletons.h"

class PostProcess;

class RenderManager :
    public Singletons
{
public:
    RenderManager();
    ~RenderManager();

    // Singletons��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Delete() override;

private:
    map<string, PostProcess*> _postProcesses;
};

