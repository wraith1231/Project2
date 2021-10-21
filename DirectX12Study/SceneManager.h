#pragma once

class RenderManager;
class Model;
class Camera;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	ULONG Release();
	void Update();
	void Render();

	void Resize(UINT width, UINT height);

	static SceneManager* Scene();

private:
	//wrl::ComPtr<RenderManager> _renderManager;
	//wrl::ComPtr<Camera> _camera;
	RenderManager* _renderManager;
	Camera* _camera;

	vector<Model*> _objects;
};

static SceneManager* h_sInstance = 0;