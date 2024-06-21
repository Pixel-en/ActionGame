#include "Goal.h"

namespace {
	const int IMAGESIZE{ 64 };
}

Goal::Goal(GameObject* parent)
	:Object(parent,"Goal")
{
}

Goal::~Goal()
{
}

void Goal::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Goal_test.png");
	assert(hImage_ > 0);
}

void Goal::Update()
{
}

void Goal::Release()
{
}
