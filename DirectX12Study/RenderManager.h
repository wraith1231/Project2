#pragma once
#include "Singletons.h"

class PostProcess;
class Model;

class RenderManager :
    public Singletons
{
public:
    RenderManager();
    ~RenderManager();

    // Singletons을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual ULONG Release() override;

    void AddPostProcess(string name);
    void DeletePostProcess(string name);
    void DeleteAllPostProcess();
    void Resize(UINT width, UINT height);

private:
    map<string, PostProcess*> _postProcesses;

    vector<Model*> _objects;
};

