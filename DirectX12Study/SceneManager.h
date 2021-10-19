#pragma once

class RenderManager;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	ULONG Release();
	void Update();
	void Render();

private:
	wrl::ComPtr<RenderManager> _renderManager;
	
	vector<Model*> _objects;
};

