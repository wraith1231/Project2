#pragma once

class Shader;

class Material
{
public:
	Material();
	~Material();

	void Init();
	void Release();
	void Render();

private:
	Shader* _shader;

};

