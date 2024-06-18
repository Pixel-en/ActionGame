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
	Mval_ = 0;
	Eval_ = 0;
	isFlag_ = false;
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

	if (g != nullptr){
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



}

void Clear::Draw()
{
}

void Clear::Release()
{
}
