#pragma once

class PostProcess;
class Model;

class RenderManager
{
public:
    RenderManager();
    ~RenderManager();

    void Init();
    void Update();
    ULONG Release();

    void AddPostProcess(string name);
    void DeletePostProcess(string name);
    void DeleteAllPostProcess();
    void Resize(UINT width, UINT height);

private:
    map<string, PostProcess*> _postProcesses;

    vector<Model*> _objects;
};

