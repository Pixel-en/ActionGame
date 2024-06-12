#include "Field.h"
#include "Engine/CsvReader.h"

Field::Field(GameObject* parent)
	:GameObject(parent,"Field"),hImage_(-1)
{
}

Field::~Field()
{
}

void Field::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Ground_test.png");
	assert(hImage_ > 0);


}

void Field::Update()
{
}

void Field::Draw()
{


}

void Field::Release()
{
}
