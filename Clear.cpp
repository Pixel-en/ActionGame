#include "Clear.h"
#include "Player.h"
#include "Goal.h"
#include "Material.h"
#include "Enemy.h"
#include "ImGui/imgui.h"

Clear::Clear(GameObject* parent)
	:GameObject(parent,"Clear")
{
	isgoal_ = false;
	isGetM_ = false;
	Mval_ = 0;
	Eval_ = 0;
	isFlag_ = false;
	cleartimer_ = 5.0f;
}

Clear::~Clear()
{
}

void Clear::Initialize()
{
}

void Clear::Update()
{
	Player* p = GetParent()->FindGameObject<Player>();
	Goal* g = GetParent()->FindGameObject<Goal>();
	std::list<Material*> m = GetParent()->FindGameObjects<Material>();

	if (!isgoal_||!isGetM_) {

		if (g != nullptr) {
			if (g->IsHitting())
			{
				isgoal_ = true;
				g->KillMe();
			}
		}
		for (Material* M : m) {
			if (M->IsHitting()) {
				M->KillMe();
				Mval_++;
			}
		}
		if (m.empty())
			isGetM_ = true;
	}
	else {
		cleartimer_ -= Time::DeltaTime();
		if (cleartimer_ < 0)
			isFlag_ = true;
	}
}

void Clear::Draw()
{
}

void Clear::Release()
{
}
