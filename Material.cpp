#include "Material.h"

Material::Material(GameObject* parent)
	:Object(parent,"Material")
{
}

Material::~Material()
{
}

void Material::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Material_test.png");
	assert(hImage_ > 0);
}

void Material::Update()
{
}


void Material::Release()
{
}
