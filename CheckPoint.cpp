#include "CheckPoint.h"

CheckPoint::CheckPoint(GameObject* parent)
	:Object(parent,"CheckPoint")
{
}

CheckPoint::~CheckPoint()
{
}

void CheckPoint::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Player_test.png");
	assert(hImage_ > 0);
}

void CheckPoint::Update()
{
}

void CheckPoint::Release()
{
}
