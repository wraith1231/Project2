#include "Material.h"
#include "stdafx.h"
#include "Shader.h"

Material::Material()
{
	Init();
}

Material::~Material()
{
	Release();
}

void Material::Init()
{
	_shader = new Shader();
}

void Material::Release()
{
}

void Material::Render()
{
}
