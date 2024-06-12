#include "Field.h"

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

	csv = new CsvReader("Assets\\alphamap.csv");
}

void Field::Update()
{
}

void Field::Draw()
{
	for (int i = 0; i < csv->GetLines(); i++) {
		for (int j = 0; j < csv->GetColumns(0); j++) {
			if (csv->GetInt(i, j) == 1)
				DrawGraph(j * 64, i * 64, hImage_, true);
		}
	}

}

void Field::Release()
{
}
